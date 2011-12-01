# This code is running live. You are invited to edit anything below. Hit save 
# to see the projection on the wall update to match your changes.

# By Ramsey Nasser, May 2011
# Ported from Kyle McDonald's Empathy sketch
# http://www.openprocessing.org/visuals/?visualID=1182

n = 1000 # number of cells
bd = 200 # base line length
sp = 0.04 # rotation speed step
sl = 0.3 # slow down rate

ppx = 0
ppy = 0

px = 0
py = 0

all = []
 
class Cell
  def initialize x, y, r
    @r = r
    @x = x
    @y = y
    @s = 0 # spin velocity
    @c = 0 # current angle
  end
  
  def sense
    if ppx != 0 or ppy != 0
      @s += sp * det(x, y, ppx, ppy, px, py) / (Point.new(x, y).distance(Point.new(ppx, ppy)) + 1);
    end
    
    @s *= sl
    @c += s
    d = bd * s + 0.001
    
    color :white, r/500.0 * (0..128)
    line x, y, x + d * cos(c), y + d * sin(c)
  end
end
 
setup do
  size 900
  background :black
  alpha_blending true
  color :white, 20
  
  for i in 0..n
    a = i + random(0, PI / 9)
    r = ((i / n.to_f) * (1000 / 2) * (((n-i) / n.to_f) * 3.3)) + random(-130, 130) + 3
    all[i] = Cell.new((r*cos(a)).to_i + (width/2), (r*sin(a)).to_i + (height/2), r)
  end
end
 
draw do
  # uncomment these lines for random motion
  # px = noise(time * 0.0005) * width
  # py = noise(time * 0.0005 + 1) * height
  px = (px..mouse_x) * 0.05
  py = (py..mouse_y) * 0.05
  color :white, 32
  circle px, py, 10
  
  all.each do |cell|
    cell.sense
  end
  
  ppx = px
  ppy = py
end
 
mouse_pressed do
  all.each do |cell|
    cell.c = 0
  end
end
 
def det x1, y1, x2, y2, x3, y3
  return ((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1)).to_f
end
