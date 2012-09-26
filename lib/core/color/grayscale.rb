# Color::Grayscale stores colors by its brightness level, and the
# transparency (alpha) level for display.
class Color::Grayscale
  attr_accessor :level, :a

  # Create a new Color::Grayscale object. 
  # 
  # @param level [Numeric] the shade of gray from black to white, 0..255
  # 
  # @return [Color::Grayscale] a new Color::Grayscale instance
  def initialize(level=0, a=0)
    @level = level
    @a = a
  end

  # Returns a Color::RGB instance in this shade of gray.
  # 
  # @return [Color::RGB]
  def to_rgb
    Color::RGB.new(@level, @level, @level, @a)
  end
end
