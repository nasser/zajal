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
