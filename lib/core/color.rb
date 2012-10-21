# Color is a basic class that figures out the right subclass for a given set of
# parameters, and defers functionality to said subclass.
#
# For example, if you attempt to create a new color object with 3 or 4 numbers,
# Color will assume they're RGB or RGBA values and will save the object appropriately.
# Eventually, you can pass in a string (like "Steel Blue"), and it will be saved
# as requested. Two numbers will mean you're passing in grayscale and alpha values, and
# so on. This moves the color-guessing functionality out of the graphic wrappers to
# OpenFramework.
class Color
  Dir[File.join(File.dirname(__FILE__), 'color', '*.rb')].each {|file| require file }

  # Initializes a new Color subclass instance. It attempts to discern the color type
  # by the arguments supplied.
  # 
  # @param :type [Symbol] the type of color given
  # @param *args [Array]
  # 
  # @return [Color::___] a new instance of a child of the Color class
  def self.new(type, *args)
    type ||= "rgb"
    Color.const_get(type.to_s.camelize).new(*args)
  end
end
