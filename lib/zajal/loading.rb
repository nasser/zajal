# code loading logic

# require "ripper" # why doesn't this work?
require 'ripper/sexp'

class Ripper
  # return a sexp without line/column numbers. useful for code comparison
  def Ripper.sexp_simple(src, filename = '-', lineno = 1)
    SexpBuilderPPSimple.new(src, filename, lineno).parse
  end
  
  class SexpBuilderPPSimple < SexpBuilderPP
    private
    SCANNER_EVENTS.each do |event|
      module_eval("def on_#{event}(tok); [:@#{event}, tok]; end", __FILE__, __LINE__ + 1)
    end
  end
end

# code loading logic

# syntax nodes that change the scope
$scope_changers = [:def, :method_add_block, :class, :module]

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