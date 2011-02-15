# code loading logic

# require "ripper" # why doesn't this work?
require 'ripper/sexp'
require "joyofsexp"
require "pp"

include ObjectSpace

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
    eval "Proc.new { #{str} \n}"
  else
    old_proc
  end
end

# code loading logic

# syntax nodes that change the scope
ScopeChangers = [:def, :method_add_block, :class, :module]

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
  
  # reduce to assigns, pull out assigns in top level scope of exp
  to_assigns = proc { |arr, exp|
    if exp.respond_to? :first and exp.first == :assign
      arr << exp[1][1][1]
    elsif exp.respond_to? :first and exp.first == :massign
      exp[1].each { |asn| arr << asn[1] }
    elsif exp.respond_to? :reduce and not ScopeChangers.include? exp.first
      exp.reduce(arr, &to_assigns)
    end

    arr
  }

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
  top_level_locals = sexp.reduce([], &to_assigns)
  
  # globalize each top level local
  top_level_locals.each { |l| globalize_one_ident.call l, sexp }
  
  code_ary.join
end

def valid? code
  not Ripper.sexp(code).nil?
end

def capture_state
  global_variables.reduce([[],[]]) do |state, gv|
    # ignore unsettable, unsupported globals
    if not gv.to_s =~ /^\$([0-9].*|.*[^a-zA-Z0-9_].*|KCODE|FILENAME|LOAD_PATH|LOADED_FEATURES|_|SAFE|PROGRAM_NAME|VERBOSE|DEBUG|stderr|stdin|stdout)$/
      val = eval(gv.to_s)
      
      if [Fixnum, Symbol, TrueClass, FalseClass, NilClass].include? val.class
        state.first << [gv, val]
      else
        state.last << [gv, val.object_id]
      end
    end
    
    state
  end
end

def live_load new_code
  return eval new_code if not valid? new_code
  
  # stay out of the way, you
  GC.disable
  
  new_code = globalize_code new_code
  old_code = App::Internals.current_code
  
  App::Internals.current_code = new_code
  
  new_sexp = Ripper.sexp_simple(new_code)[1]
  new_sexp_lines = Ripper.terminated_sexp(new_code)[1]
  
  old_sexp = Ripper.sexp_simple(old_code)[1]
  
  removed = old_sexp - new_sexp
  added = new_sexp - old_sexp
  
  old_state = capture_state
  
  # get rid of deleted events
  old_sexp.fetch("/method_add_block/method_add_arg/fcall/@ident").each do |event|
    eval "Events::Internals.#{event}_proc = nil unless Events::Internals.#{event}_proc.nil?"
  end
  
  # get rid of old globals
  old_sexp.fetch("/assign/var_field/@gvar").each do |gv|
    eval "#{gv} = nil"
  end
  
  old_sexp.fetch("/def/@ident").each do |method|
    eval "undef :#{method}"
  end
  
  # get rid of old classes
  old_sexp.fetch("/class/const_ref/@const").each do |klass|
    Object.send(:remove_const, klass.to_sym)
  end
  
  # get rid of old modules
  old_sexp.fetch("/module/const_ref/@const").each do |modul|
    Object.send(:remove_const, modul.to_sym)
  end
  
  
  # run the code
  begin
    if new_sexp.fetch("/method_add_block/method_add_arg/fcall/@ident").empty?
      # no blocks are used, we're in reduced mode
      Events::Internals.defaults_proc.call
      Events::Internals.draw_proc = proc new_code
      Events::Internals.draw_proc.call
    else
      # blocks are used, we're in complete mode
      eval new_code
      # kind of a kludge!
      Typography::Internals.stacked_text_x = Typography::Internals.stacked_text_initial_x
      Typography::Internals.stacked_text_y = Typography::Internals.stacked_text_initial_y
      Events::Internals.update_proc.call unless Events::Internals.update_proc.nil?
      Events::Internals.draw_proc.call unless Events::Internals.draw_proc.nil?
    end
  ensure
    # dont want to leave this off!
    GC.enable
  end
  
  
  # TODO support global assigns burried under if/while/etc blocks
  if added.fetch("/method_add_block/method_add_arg/fcall/@ident").include? "setup" or not added.fetch("/assign/var_field/@gvar").empty?
    # re-run setup if setup modified
    Events::Internals.defaults_proc.call
    Events::Internals.setup_proc.call unless Events::Internals.setup_proc.nil?
  else
    # recreate state otherwise
    immediate_state, ref_state = old_state
    immediate_state.each { |gv, val| eval "#{gv.to_s} = #{val.inspect}" }
    ref_state.each { |gv, val| eval "#{gv.to_s} = ObjectSpace._id2ref(#{val})" }
  end
  
  # as you were
  GC.enable
  ObjectSpace.garbage_collect
end
