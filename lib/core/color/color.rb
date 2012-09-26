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
  # Initializes a new Color subclass instance. It attempts to discern the color type
  # by the arguments supplied.
  # 
  # @param *args [Array]
  # 
  # @return [Color::RGB] a new Color::RGB instance
  def self.new(*args)
    Color::RGB.new(args)
  end
end
