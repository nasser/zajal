# This code is running live. You are invited to edit anything below. Hit save 
# to see the projection on the wall update to match your changes.

# By Ramsey Nasser, May 2011
# Inspired by bitcraft's pantons dream sketch
# http://www.openprocessing.org/visuals/?visualID=4575

j = 0
p = Point.new(width/2, height/2)

setup do
  smoothing true
  alpha_blending true
  background :black
end

draw do
  p.x = noise(time * 0.1).remap 0, 1, -width/2, width/2
  p.y = noise(time * 0.1 + 1).remap 0, 1, -150, height+150
  
  color noise(time * 0.5 + 2) * (128..255),
        noise(time * 0.5 + 3) * (128..255),
        noise(time * 0.5 + 4) * (128..255),
        32
  
  j = j * 0.9 + (width/2 - p.x);
  y = (height/2 - p.y)*2
    
  translate width/2, height/2
  for i in 0..60
    scale y / (width/1.75)
    circle 0, 125, 200
    rotate PI / width * j
  end
end