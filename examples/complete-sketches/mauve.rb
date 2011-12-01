# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, December 2011

vf = nil
particles = []

setup do
  size 800
  title "Mauve"
  alpha_blending true
  background 32, 0, 32
  
  vf = VectorField.new width, height
  vf.randomize!
end

update do
  once_every(30) { vf.randomize! 100 }
  
  particles << Point.new(width/2, random_height)
  
  particles.shift if particles.size > 5000
  particles.reject! { |p| p.x < 0 or p.x > width or p.y < 0 or p.y > height }
  
  particles.each do |p|
    return unless vf[p.x, p.y]
    dx, dy = vf[p.x, p.y].x, vf[p.x, p.y].y
    p.x = p.x * 0.99 + (p.x + dx*20) * 0.01
    p.y = p.y * 0.99 + (p.y + dy*5) * 0.01
  end
end

draw do
  matrix do
    translate width/4, -height/3
    rotate 30
  
    particles.each_with_index do |p, i|
      dy = 1 - (p.y - height/2).abs / (height/2)
    
      q = i/particles.size.to_f
      r = 1 - q
    
      color 255 * q, 255 * r, 128, 8 * q * dy
      circle p.x, p.y, 125 * q
    end
  end
end

class VectorField
  def initialize w, h, res=10
    @res = res
    @ext_w, @ext_h = w.to_f, h.to_f
    @int_w, @int_h = @ext_w/res, @ext_h/res
    
    @vectors = Hash.new()
    
    for x in 0..@int_w
      for y in 0..@int_h
        @vectors[[x, y]] = Point.new(0, 0)
      end
    end
  end
  
  def [] x, y
    x_pct, y_pct = x/@ext_w, y/@ext_h
    # puts "#{x}/#{@ext_w}, #{y}/#{@ext_h}"
    return nil if not x_pct.between?(0, 1) or not y_pct.between?(0, 1)
    
    field_x = (x_pct * @int_w).to_i
    field_y = (y_pct * @int_h).to_i
    
    return @vectors[[field_x, field_y]]
  end
  
  def randomize! amt=120
    for x in 0..self.int_w
      for y in 0..self.int_h
        @vectors[[x, y]].x = random -amt, amt
        @vectors[[x, y]].y = random -amt, amt
      end
    end
  end
  
  def draw
    for x in 0..vf.int_w
      for y in 0..vf.int_h
        x1, y1 = x * @res, y * @res
        x2, y2 = x1 + self[x1, y1].x, y1 + self[x1, y1].y
        
        line x1, y1, x2, y2
      end
    end
  end
  
  def inspect
    "VectorField[#{object_id}]"
  end
  
end