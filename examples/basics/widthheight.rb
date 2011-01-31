# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The 'width' and 'height' variables contain the width and height of the display
# window as defined in the size() function.

size 200, 200
background 127

0.step height, 20 do |i|
  color 0
  rectangle 0, i, width, 10
  color 255
  rectangle i, 0, 10, height
end