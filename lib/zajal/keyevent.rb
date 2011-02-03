class KeyEvent
  def initialize k
    @code = k
    warn "Unknown key code `#{k}'!" if unknown?
  end
  
  def printable?
    (32..126).cover? @code
  end
  
  def alpha?
    [65..90, 97..122].any? { |rng| rng.cover? @code }
  end
  
  def numeric?
    (48..57).cover? @code
  end
  
  def punctuation?
    [33..47, 58..64, 91..96, 123..126].any? { |rng| rng.cover? @code }
  end
  
  def special?
    [3, 8, 9, 13, 27, 127].include? @code or @code > 256
  end
  
  def unknown?
    not printable? and not special?
  end
  
  def to_s
    # TODO is this code-style acceptable?
    if    printable? then @code.chr 
    elsif special?   then to_sym.to_s
    elsif unknown?   then "?#{@code}?"
    end
  end
  
  def to_sym
    if printable?
      to_s.to_sym
      
    elsif special?
      case @code
      when   3 then :enter
      when   8 then :delete
      when   9 then :tab
      when  13 then :return
      when  27 then :escape
      when 127 then :backspace
      when 257 then :f1
      when 258 then :f2
      when 259 then :f3
      when 260 then :f4
      when 261 then :f5
      when 262 then :f6
      when 263 then :f7
      when 264 then :f8
      when 265 then :f9
      when 266 then :f10
      when 267 then :f11
      when 268 then :f12
      when 356 then :left
      when 357 then :up
      when 358 then :right
      when 359 then :down
      when 360 then :page_up
      when 361 then :page_down
      when 362 then :home
      when 363 then :end
      when 364 then :insert
      else          nil
      end
      
    end
  end
  
  def to_i
    # TODO is comparing by keycode more important than comparing numeric keys by number?
    # KeyEvent.new(65) == 65 >? KeyEvent.new(51) == 3
    # can the coesist? they only overlap on :enter, :delete and :tab
    @code
  end
  
  def =~ other
    to_s =~ other
  end
  
  def === other
    [to_i, to_s, to_sym].any? { |repr| repr == other } and not other.nil?
  end
  
  def == other
    # TODO this violates the transitivity of equality, but allows for nice if-then syntax. remove?
    self === other
  end
end

# Reversing the polarity of case-when statements
# 
# We want something like this to work:
# 
# key_pressed do |key|
#   case key
#   when "A"
#     # react to 'A' key
#   when :left
#     # react to left arrow key
#   when 9
#     # react to '9' key, (this is being considered)
#   when /[a-z]/
#     # react to lowercase keys
#   end
# end
# 
# The way case-when is implemented is it calls the #=== method on each object
# in the when clause, so the above turns into this
# 
# key_pressed do |key|
#   if "A" === key then
#     # react to 'A' Key
#   elsif :left === key then
#     # react to left arrow key
#   elsif 9 === key then
#     # react to '9' key
#   elsif /[a-z]/ === key then
#     # react to lowercase keys
#   end
# end
# 
# Which sucks, because to implement the desired syntax, #=== has to be
# implemented on *each potential recieving class*, Fixnum, String, Regexp etc
# as opposed to a single KeyEvent#=== if Ruby placed the case object on the 
# left hand side and the when objects on the right.
# 
# This hack accomplishes that syntax



# Rewrite a class's #=== method to deal with KeyEvent in the way we want
# 
# code - A string of ruby code implementing the KeyEvent#=== comparison. The
#        receiving obect is bound to `self` and the KeyEvent to `other`
# 
# Examples
# 
#   class String
#     trequals %{ other.printable? and self == other.to_s }
#   end
# 
# Returns nothing
def trequals code
  # http://split-s.blogspot.com/2006/01/replacing-methods.html
  # http://blog.jayfields.com/2006/12/ruby-alias-method-alternative.html
  old_trequals = instance_method(:===)
  
  define_method(:===) do |other|
    if other.is_a? KeyEvent
      # TODO string based evals aren't the best, is there a way to do this
      # with blocks/procs and not resolve self correctly?
      eval code, binding
    else
      old_trequals.bind(self).call(other)
    end
  end
end

class String
  trequals %{ other.printable? and self == other.to_s }
end

class Symbol
  trequals %{ self == other.to_sym }
end

class Regexp
  trequals %{ other.printable? and other.to_s =~ self }
end

class Fixnum
  trequals %{ self == other.to_i }
end
