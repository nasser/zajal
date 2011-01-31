# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The first two parameters for the bezier ) function specify the first point 
# the curve and the last two parameters specify the last point. The middle
# parameters set the control points that define the shape of the curve.

size 200, 200 
fill false
smoothing true

0.step(100, 20) do |i|
  bezier 90-(i/2.0), 20+i, 210, 10, 220, 150, 120-(i/8.0), 150+(i/4.0)
end
