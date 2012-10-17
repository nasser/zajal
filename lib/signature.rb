# Method signature matcher
# 
# used in case...when statements to match arguments. Symbols
# match with respond_to? and anything else matches with ===
# 
# @example
#   def initialize *args
#     case args
#     when Signature[:to_s]
#       load args.first
#     when Signature[:to_f, :to_f]
#       resize *args
#     when Signature[:to_s, Fixnum, Boolean]
#       file, quality, texture = args
#       load file, quality
#       use_texture texture
#     else
#       raise ArgumentError, args.inspect
#     end
#   end
class Signature
  # Alias for Signature.new
  # 
  # @example
  #   Signature[:to_s, Fixnum] # matches "hello", 90
  def self.[] *sig
    Signature.new sig
  end

  def initialize sig
    @signature = sig
  end

  # Match argument list
  def === other
    return false if other.length != @signature.length
    
    @signature.zip(other).map { |match, argument|
      case match
      when Symbol; argument.respond_to? match
      else; match === argument
      end
    }.all?
  end
end