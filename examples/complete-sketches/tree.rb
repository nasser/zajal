# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011
# Inspired by dotlassie's Shortest tree generator sketch
# http://www.openprocessing.org/visuals/?visualID=3609

i = 0.0
t = 0

setup do
  size 800
  background :black
  color :white
end

draw do
  t = time * 0.1
  
  # try changing the number 4 below to something larger
  draw_branch 4, 1
end

def draw_branch k, s
  t = time * 0.0001 + i
  m = k - k.to_i
  n = k.to_i
  
  if i <= n
    m = 1.0
  end
  
  if i < 1
    translate width/2, height/2 + 180
  end
  
  line_width 10-i*2
  line 0, 0, 0, -180 * m if i >= 1
  
  if(i > n)
    return
  end
  
  matrix do
    translate 0, -180 * m
    scale noise(t, i, 1).remap(0, 1, 0.5, 1.25) * s
    i += 1
    rotate (PI*noise(t, i, 2)).to_deg
    draw_branch k, s
    
    rotate (-(TWO_PI*noise(t, i, 4))/i).to_deg
    draw_branch k, s
    i -= 1
  end
end