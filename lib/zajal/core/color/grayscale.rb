# Color::Grayscale stores colors by its brightness level, and the
# transparency (alpha) level for display.
class Color::Grayscale
  attr_accessor :level, :a

  # Create a new Color::Grayscale object. 
  # 
  # @param level [Numeric] the shade of gray from black to white, 0..255
  # 
  # @return [Color::Grayscale] a new Color::Grayscale instance
  def initialize(level, a=255)
    @level = level
    @a = a
  end

  # Returns a Color::Rgb instance in this shade of gray.
  # 
  # @return [Color::Rgb]
  def to_rgb
    Color::Rgb.new(@level, @level, @level, @a)
  end

  def to_hsv
    to_rgb.to_hsv
  end
end
