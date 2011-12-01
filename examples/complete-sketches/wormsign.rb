# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011

setup do
  size 800
  background :black
  alpha_blending true
  fill false
end

draw do
  line_width 2
  
  for n in 0..170
    n *= 0.1
    x = n * 130 + sin(time * 0.001 + n) * 140
    y = height/2 + sin(time * 0.001 + n) * 140
    r = 200 + cos(n) * 40
    
    color :red, 128
    circle x, y, r
    
    color :green, 64
    circle x, y, r/2
    
    color :white, 64
    circle x, y, r/4
  end
end

