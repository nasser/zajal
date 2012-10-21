# Color::Hsv stores colors by their Hue, Saturation, and Value separations, and the
# transparency (alpha) level for display.
class Color::Hsv
  attr_accessor :h, :s, :v, :a

  # Create a new Color object. 
  # 
  # @param h [Numeric] the degree of hue, 0..1
  # @param s [Numeric] the amount of saturation, 0..1
  # @param v [Numeric] the amount of value, 0..1
  # @param a [Numeric] the amount of alpha, 0..255
  # 
  # @return [Color::Hsv] a new Color::Hsv instance
  def initialize(*args)
    @h, @s, @v, @a = 255, 255, 255, 255

    case args
    when Signature[:to_i]
      @h = args.first
    when Signature[:to_i, :to_i]
      @h, @a = args.first, args.last
    when Signature[:to_i, :to_i, :to_i]
      @h, @s, @v = *args
    when Signature[:to_i, :to_i, :to_i, :to_i]
      @h, @s, @v, @a = *args
    when Signature[Symbol]
      # TODO: .new().to_rgb.to_hsv is pretty terrible. Is there a better way to handle this?
      @h, @s, @v, @a = Color::NamedColor.new(args.first).to_rgb.to_hsv
    when Signature[Symbol, :to_i]
      @h, @s, @v, @a = Color::NamedColor.new(args.first, args.last).to_rgb.to_hsv
    else
      raise ArgumentError, args
    end
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

  # Returns a Color::Rgb instance that should closely match
  # an instance's HSV values.
  # 
  # @return [Color::Rgb]
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

    Color::Rgb.new(r * 255, g * 255, b * 255, @a)
  end
end
