# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011

setup do
  size 800
  
  alpha_blending true
  background :black
  line_width 5
end

draw do
  translate width/2, height/2
  
  a = 0
  r = 50
  s = 1
  
  50.times do |i|
    x, y = sin(a) * r, cos(a) * r
    r *= 1.067
    s *= 1.1
    a += time * 0.00005
    
    color :white, (1-i/50.0) * 255
    line sin(a) * r, cos(a) * r, x, y
  end
  
end