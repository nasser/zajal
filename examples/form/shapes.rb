# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The basic shape primitive methods are triangle, rectangle, square,
# circle and ellipse. Each of these functions requires a number of parameters
# to determine the shape's position and size.


size 200, 200
smoothing true
background 0
color 226

triangle 10, 10, 10, 200, 45, 200
rectangle 45, 45, 35, 35
ellipse 140, 80, 40, 40
triangle 160, 10, 195, 200, 160, 200

shape {
  vertex 80, 120
  vertex 70, 140
  vertex 80, 160
  vertex 70, 180

  vertex 120, 180
  vertex 130, 160
  vertex 120, 140
  vertex 130, 120
}
