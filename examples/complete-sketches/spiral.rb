# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011

setup do
  size 800
  
  background :black
  smoothing true
  line_width 5
end

draw do
  a = 0
  r = 10
  x, y = width/2, height/2
  
  k = sin(time * 0.00005)
  
  for i in 20..450
    t = i/400.0
    color (8..255) * t
    line x + cos(a) * r, y + sin(a) * r,
         x + cos(a+k) * r*1.01, y + sin(a+k) * r*1.01
    a += k
    r *= 1.01 if i < 400
  end
end