# Color::HSV stores colors by their Hue, Saturation, and Value separations, and the
# transparency (alpha) level for display.
class Color::HSV
  attr_accessor :h, :s, :v, :a

  # Create a new Color object. 
  # 
  # @param h [Numeric] the degree of hue, 0..1
  # @param s [Numeric] the amount of saturation, 0..1
  # @param v [Numeric] the amount of value, 0..1
  # @param a [Numeric] the amount of alpha, 0..255
  # 
  # @return [Color::RGB] a new Color::RGB instance
  def initialize(h=0, s=0, v=0, a=255)
    @h = h
    @s = s
    @v = v
    @a = a
  end

  # Returns the HSVa values in an array.
  # 
  # @return [Array]
  def to_a
    [@h, @s, @v, @a]
  end

  # Returns the HSVa values in a hash.
  # 
  # @return [Hash]
  def to_hash
    {h: @h, s: @s, v: @v, a: @a}
  end

  # Returns a Color::RGB instance in this shade of gray.
  # 
  # @return [Color::RGB]
  def to_rgb
    h, s, v = @h / 255.0, @s / 255.0, @v / 255.0
    i = (h * 6.0).floor
    f = h * 6 - i
    p = v * (1 - s)
    q = v * (1 - f * s)
    t = v * (1 - (1 - f) * s)

    case(i % 6)
    when 0 then r, g, b = v, t, p
    when 1 then r, g, b = q, v, p
    when 2 then r, g, b = p, v, t
    when 3 then r, g, b = p, q, v
    when 4 then r, g, b = t, p, v
    when 5 then r, g, b = v, p, q
    end

    Color::RGB.new(r * 255, g * 255, b * 255, @a)
  end
end
