class Color::RGB
  attr_accessor :r, :g, :b, :a

  # Create a new Color object. 
  # 
  # @param r [Numeric] the amount of red, 0..255
  # @param g [Numeric] the amount of green, 0..255
  # @param b [Numeric] the amount of blue, 0..255
  # @param a [Numeric] the amount of alpha, 0..255
  # 
  # @return [Color::RGB] a new Color::RGB instance
  def initialize(r=0, g=0, b=0, a=0)
    @r = r
    @g = g
    @b = b
    @a = a
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
end
