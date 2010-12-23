# point drawing and class

def point x, y
  circle x, y, 1
end

# should wrap ofxVec2f
class Point
  def initialize x, y
    @x = x
    @y = y
  end
  
  def clamp! x1, x2, y1, y2
    @x = @x.clamp x1, x2
    @y = @y.clamp y1, y2
  end
  
  def self.rand amt
    Point.new(random(-amt, amt), random(-amt, amt))
  end
  
  def + other
    if other.respond_to? :x and other.respond_to? :y
      Point.new(@x + other.x, @y + other.y)
    else
      Point.new(@x + other, @y + other)
    end
  end
  
  def * other
    if other.respond_to? :x and other.respond_to? :y
      Point.new(@x * other.x, @y * other.y)
    else
      Point.new(@x * other, @y * other)
    end
  end
end