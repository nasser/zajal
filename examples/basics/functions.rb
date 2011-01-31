# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The drawTarget() function makes it easy to draw many distinct targets. Each
# call to drawTarget() specifies the position, size, and number of rings for
# each target.

setup do
  size 200, 200
  background 51
  smoothing true
end

draw do
  draw_target 68, 34, 200, 10
  draw_target 152, 16, 100, 3
  draw_target 100, 144, 80, 5
end

def draw_target xloc, yloc, size, num
  grayvalues = 255/num;
  steps = size/num;
  
  num.times do |i|
    color i*grayvalues
    ellipse xloc, yloc, size-i*steps, size-i*steps
  end
end