# Color::Rgb stores colors by their Red, Green, and Blue separations, and the
# transparency (alpha) level for display.
class Color::Rgb
  attr_accessor :r, :g, :b, :a

  # Create a new Color object. 
  # 
  # @param r [Numeric] the amount of red, 0..255
  # @param g [Numeric] the amount of green, 0..255
  # @param b [Numeric] the amount of blue, 0..255
  # @param a [Numeric] the amount of alpha, 0..255
  # 
  # @return [Color::Rgb] a new Color::Rgb instance
  def initialize(r, g, b, a=255)
    @r, @g, @b, @a = r, g, b, a
  end

  # Returns the RGBa values in an array.
  # 
  # @return [Array]
  def to_a
    [@r, @g, @b, @a]
  end

  # Returns the RGBa values in a hash.
  # 
  # @return [Hash]
  def to_hash
    {r: @r, g: @g, b: @b, a: @a}
  end

  def to_rgb
    self
  end

  # Returns a Color::Hsv instance that should closely match
  # an instance's RGB values.
  # 
  # @return [Color::Hsv]
  def to_hsv
    r, g, b = @r / 255, @g / 255, @b / 255
    max, min = [r, g, b].max, [r, g, b].min
    h, s, v = max, max, max

    d = max - min
    s = max == 0 ? 0 : d / max

    if max == min
      h = 0 # achromatic
    else
      case max
      when r then h = (g - b) / d + (g < b ? 6 : 0)
      when g then h = (b - r) / d + 2
      when b then h = (r - g) / d + 4
      end
      h = h / 6
    end

    Color::Hsv.new(h * 255, s * 255, v * 255, @a)
  end
end
