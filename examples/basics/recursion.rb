# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# A demonstration of recursion, which means functions call themselves. Notice
# how the draw_circle function calls itself at the end of its block. It
# continues to do this until the variable "level" is equal to 1.

setup do
  size 200, 200
  smoothing true
end

draw do
  draw_circle 126, 170, 6
end

def draw_circle x, radius, level
  tt = 126 * level/4.0;
  color tt
  ellipse x, 100, radius*2, radius*2
  
  if level > 1 then
    level = level - 1;
    draw_circle x - radius/2, radius/2, level
    draw_circle x + radius/2, radius/2, level
  end
end