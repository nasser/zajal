# code loading logic

# require "ripper" # why doesn't this work?
require 'ripper/sexp'
require "joyofsexp"
require "pp"

class Ripper
  # Like SexpBuilderPP, but adds @end expression at the end of important blocks
  class TerminatedSexpBuilder < SexpBuilderPP
    private
    [:method_add_block, :def, :class, :module].each do |event|
      module_eval(<<-End, __FILE__, __LINE__ + 1)
        def on_#{event}(*args)
          [:#{event}, *args, [:@end, [lineno(), column()]]]
        end
      End
    end
  end
  
  def Ripper.terminated_sexp(src, filename = '-', lineno = 1)
    TerminatedSexpBuilder.new(src, filename, lineno).parse
  end
  
  # Like SexpBuilderPP, but leaves out line/column numbers
  class SimpleSexpBuilder < SexpBuilderPP
    private
    SCANNER_EVENTS.each do |event|
      module_eval("def on_#{event}(tok); [:@#{event}, tok]; end", __FILE__, __LINE__ + 1)
    end
  end
  
  def Ripper.sexp_simple(src, filename = '-', lineno = 1)
    SimpleSexpBuilder.new(src, filename, lineno).parse
  end
end

class Array
  alias :old_include? :include?
  # like standard include, but takes an enumerable and checks inclusion of each member
  def include? other
    if other.respond_to? :any? then
      other.any? do |obj|
        old_include? obj
      end
    else
      old_include? other
    end
  end
end

alias :old_proc :proc
def proc str=nil
  if not str.nil?
    eval "Proc.new { #{str} }"
  else
    old_proc
  end
end

# code loading logic

# syntax nodes that change the scope
$scope_changers = [:def, :method_add_block, :class, :module]
$event_blocks = %w(setup update draw exit window_resized key_pressed key_released mouse_moved mouse_dragged mouse_pressed mouse_released audio_requested audio_received)

# reduce to assigns, pull out assigns in top level scope of exp
$to_assigns = proc { |arr, exp|
  if exp.respond_to? :first and exp.first == :assign
    arr << exp[1][1][1]
  elsif exp.respond_to? :first and exp.first == :massign
    exp[1].each { |asn| arr << asn[1] }
  elsif exp.respond_to? :reduce and not $scope_changers.include? exp.first
    exp.reduce(arr, &$to_assigns)
  end

  arr
}

# reduce to methods, pull out method invocations from exp
$to_methods = proc { |arr, exp|
  if exp.respond_to? :first and exp.first == :method_add_block
    arr << exp[1][1][1][1]
  elsif exp.respond_to? :reduce
    exp.reduce(arr, &$to_methods)
  end
  
  arr
}

# Make all top level locals global. Implements Processing style syntax and
# avoids having to write $ signs everywhere
# 
# Issues
#   - Function defs CANNOT use globals as parameters. Code will not run.
# 
# code - The code to globalize as a string
# sigil - Optional, the sigil to insert before globalized variables
# 
# Returns the code with sigils inserted in the correct places
def globalize_code code, sigil="$"
  sexp = Ripper.sexp(code)[1]
  
  line_inserts = {}
  code_ary = code.each_line.to_a
  
  # globalize one identifier in the code
  globalize_one_ident = proc do |ident, exp|
    if exp.respond_to? :first and exp.first == :@ident and exp[1] == ident
      line, col = exp[2]
      line -= 1
      line_inserts[line] ||= []
      
      offset = line_inserts[line].reduce(0) { |val, ins| ins < col ? val + 1 : val }
      code_ary[line].insert col + offset, sigil
      
      line_inserts[line] << col
      line_inserts[line].sort!
    elsif exp.is_a? Array
      exp.each { |e| globalize_one_ident.call ident, e }
    end
  end
  
  # extract top level locals to be globalized
  top_level_locals = sexp.reduce([], &$to_assigns)
  
  # globalize each top level local
  top_level_locals.each { |l| globalize_one_ident.call l, sexp }
  
  code_ary.join
end

def valid? code
  not Ripper.sexp(code).nil?
end

# Compare two scripts as Zajal code and determine if a full reset it required
# 
# local_code - Code currently running
# other_code - Incoming code
# 
# Returns true if the code differs enough to warrant a full reset, false otherwise
def compare_code local_code, other_code
  local_sexp = Ripper.sexp_simple(local_code)[1]
  other_sexp = Ripper.sexp_simple(other_code)[1]
  
  # figure out what was added and removed
  removed = local_sexp - other_sexp
  added   = other_sexp - local_sexp
  
  modified_globals = removed.reduce([], &$to_assigns) | added.reduce([], &$to_assigns)
  modified_methods = removed.reduce([], &$to_methods) | added.reduce([], &$to_methods)
  
  modified_methods.include?("setup") or not modified_globals.empty?
end

def capture_state
  global_variables.reduce([]) do |state, gv|
    # ignore unsettable, unsupported globals
    state << [gv, eval(gv.to_s)] if not gv.to_s =~ /^\$([0-9].*|.*[^a-zA-Z0-9_].*|KCODE|FILENAME|LOAD_PATH|LOADED_FEATURES|_|SAFE|PROGRAM_NAME|VERBOSE|DEBUG|stderr|stdin|stdout)$/
    state
  end
end

# Determing if code is in reduced mode or not.
# Reduced mode is Zajal code that does not use any event blocks.
# 
# code - A ruby String containing the code to analyze
# 
# Returns true if code is in reduced mode, false otherwise
def reduced_mode? code
  not Ripper.sexp_simple(code)[1].reduce([], &$to_methods).include? $event_blocks
end

def live_load new_code, old_code
  new_code = globalize_code new_code
  
  # eval invalid code to generate syntax errors
  return {codeToRun:new_code, newCode:new_code} if not valid? new_code
  
  # eval new code if this is the first loading
  return {codeToRun:new_code, newCode:new_code} if old_code.nil?
  
  
  new_sexp = Ripper.sexp_simple(new_code)[1]
  old_sexp = Ripper.sexp_simple(old_code)[1]
  new_sexp_lines = Ripper.terminated_sexp(new_code)[1]
  
  removed = old_sexp - new_sexp
  added = new_sexp - old_sexp
  
  
  # get rid of deleted events
  removed.fetch("method_add_block/method_add_arg/fcall/@ident").each do |event|
    eval "Events::Internals.#{event}_proc = nil"
  end
  
  # get rid of deleted methods
  removed.fetch("def/@ident").each do |method|
    eval "undef :#{method}"
  end
  
  # get rid of deleted classes
  removed.fetch("class/const_ref/@const").each do |klass|
    Object.send(:remove_const, klass.to_sym)
  end
  
  # get rid of deleted modules
  removed.fetch("module/const_ref/@const").each do |modul|
    Object.send(:remove_const, modul.to_sym)
  end
  
  
  new_code_ary = new_code.lines.to_a
  final_code_ary = []
  
  # copy lines that need to be added to final_code_ary
  # looks at added sexp to determine what needs to be added
  # uses head and tail path to pull out event/method/class/module code
  copy_lines = proc do |head, tail|
    heads = new_sexp_lines.fetch(head).each_slice(2).to_a
    tails = new_sexp_lines.fetch tail
    added_things = added.fetch head
    
    heads.zip(tails).select { |e|
      added_things.include? e.first
    }.map { |e|
      e.flatten(2).values_at(0, 1, 3)
    }.each { |event, start, stop|
      final_code_ary[start-1..stop] = new_code_ary[start-1..stop]
    }
  end
    
  copy_lines.call "method_add_block/method_add_arg/fcall/@ident", "method_add_block/@end"
  copy_lines.call "def/@ident", "def/@end"
  copy_lines.call "class/const_ref/@const", "class/@end"
  copy_lines.call "module/const_ref/@const", "module/@end"
  
  # re-run setup if setup modified
  if added.fetch("method_add_block/method_add_arg/fcall/@ident").include? "setup"
    final_code_ary << "Events::Internals.setup_proc.call"
  end
  
  # puts final_code_ary.map { |e| e.to_s.rstrip }.join "\n"
  final_code = final_code_ary.map { |e| e.to_s.rstrip }.join "\n"
  
  return { codeToRun: final_code, newCode: new_code }
end
