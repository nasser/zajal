$: << "/Users/nasser/Workspace/zajal/lib/ruby/stdlib"

require "ripper"
require "pp"

# remove line/column info from sexp output
# we don't need it and it messes up code comparison
class Ripper
  class SexpBuilderPP < ::Ripper   #:nodoc:
    private
    SCANNER_EVENTS.each do |event|
      module_eval("def on_#{event}(tok); [:@#{event}, tok]; end", __FILE__, __LINE__ + 1)
    end
  end
end

# record "typical state"
$typical_globals = global_variables
$typical_methods = private_methods

# syntax nodes that change the scope
$scope_changers = [:def, :method_add_block, :class, :module]

# reduce to assigns, pull out assigns in top level scope of exp
to_assigns = proc { |arr, exp|
  if exp.respond_to? :first and exp.first == :assign
    arr << exp[1][1][1]
  elsif exp.respond_to? :reduce and not $scope_changers.include? exp.first
    exp.reduce(arr, &to_assigns)
  end
  
  arr
}

# reduce to methods, pull out method invocations from exp
to_methods = proc { |arr, exp|
  if exp.respond_to? :first and exp.first == :method_add_block
    arr << exp[1][1][1][1]
  elsif exp.respond_to? :reduce
    exp.reduce(arr, &to_methods)
  end
  
  arr
}

# load code
local_code = open("scratch/flower-1.rb").read
other_code = open("scratch/flower-2.rb").read

# parse code
local_sexp = Ripper.sexp(local_code)[1]
other_sexp = Ripper.sexp(other_code)[1]

p local_sexp.reduce([], &to_assigns)
p local_sexp.reduce([], &to_methods)

# extract globals from code
globals = local_sexp.reduce([], &to_assigns)

# globalize
globalized_code = other_code.clone
globals.each { |g| globalized_code.gsub! /\b#{g}\b/, "$#{g}"}

# figure out what was added and removed
removed = local_sexp - other_sexp
added   = other_sexp - local_sexp

modified_globals = removed.reduce([], &to_assigns) | added.reduce([], &to_assigns)
modified_methods = removed.reduce([], &to_methods) | added.reduce([], &to_methods)

must_reset = (modified_methods.include?("setup") or not modified_globals.empty?)

# pp local_sexp

if must_reset
  # eval globalized_code, run setup();
  
else
  # eval globalized_code, restore globals variables
  
end

# p private_methods
# p global_variables

# class Class
#   def undefine!
#     # sym = name.to_sym
#     # Object.instance_eval { remove_const sym }
#     instance_methods(false).each { |m| remove_method m }
#   end
# end







# run a block once every f frames, return true every f frame
def once_every f
  yield if block_given? and frame % f == 0
  return frame % f == 0
end

def point x, y
  circle x, y, 1
end

class Point
  attr_accessor :x, :y
  
  def initialize x, y
    @x = x
    @y = y
  end
  
  def clamp! x1, x2, y1, y2
    @x = @x.clamp x1, x2
    @y = @y.clamp y1, y2
  end
  
  def self.rand amt
    Point.new(random(-amt, amt), random(-amt, amt))
  end
  
  def + other
    if other.respond_to? :x and other.respond_to? :y
      Point.new(@x + other.x, @y + other.y)
    else
      Point.new(@x + other, @y + other)
    end
  end
end

class ZajalCode
  attr_reader :code, :globalized_code, :silent_code
  @@block_labels = %w[top_level setup update draw exit key_pressed key_released mouse_moved mouse_dragged mouse_pressed mouse_released audio_requested audio_received def class module proc lambda loop]
  
  def initialize code, labels=@@block_labels
    # store code
    @code = code
    
    # store labels and range => label mapping
    @labels = labels
    @range_labels = {}
    @labels.each do |label|
      @code.scan(/^(#{label}.*?^end|\})/m) do
        @range_labels[$~.begin(1)...$~.end(1)] = label.to_sym
      end
    end
    
    # collect method names
    @methods = []
    @code.scan(/def\s+([^\s]*)/) do
      if label($~.begin(0)) == :def
        @methods << $~[1]
      end
    end
    
    # globalize the code, collect global variables
    @globals = []
    @globalized_code = @code.clone
    @code.scan(/\b([a-z_][a-zA-Z0-9_]*)\s*=[^=]/m) do
      if label($~.begin(0)) == :top_level
        var_name = $~.captures.first
        @globals << var_name
        @globalized_code.gsub! /\b#{var_name}\b/, "$#{var_name}"
      end
    end
    
    # make a silent version of the code
    @silent_code = @globalized_code.clone
    offset = 0
    @globals.each do |global|
      @globalized_code.scan(/\$(#{global})\s*=[^=]/m) do
        if label($~.begin(0)) == :top_level
          @silent_code.insert $~.begin(0)+offset, "#"
          offset += 1
        end
      end
    end
    
  end
  
  def [] idx
    if idx.is_a? Symbol or idx.is_a? String
      block idx.to_sym
    else
      label idx
    end
  end
  
  def block label
    if label == :top_level
      top_level_block = @code.clone
      
      i = j = 0
      loop do
        if label(j) != :top_level
          top_level_block[i] = ""
        else
          i += 1
        end
        j += 1
        break if j > code.length
      end
      
      return top_level_block
    else
      @range_labels.each do |rng, lbl|
        return @code[rng] if lbl == label
      end
      
      return nil
    end
  end
  
  def label idx
    @range_labels.each do |rng, label|
      if idx.respond_to? :first and idx.respond_to? :last then
        return label if rng.include? idx.first and rng.include? idx.last
        return :multiple if rng.include? idx.first and not rng.include? idx.last or not rng.include? idx.first and rng.include? idx.last
      else
        return label.to_sym if rng.include? idx
      end
    end

    return :top_level
  end
  
  def diff other
    diff_blocks = []
    @@block_labels.each do |label|
      if self[label] != other[label]
        diff_blocks << label.to_sym
      end
    end
    
    diff_blocks
  end
  
end