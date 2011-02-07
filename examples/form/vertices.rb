# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The shape method begins recording vertices for a shape until its block is
# closed. A vertex is a location in space specified by X, Y, and sometimes Z
# coordinates. After calling the shape method, a series of vertex method calls
# must follow inside the block.

size 200, 200
fill false

color 102
shape do 
  curve_vertex 168, 182
  curve_vertex 168, 182
  curve_vertex 136, 38
  curve_vertex 42, 34
  curve_vertex 64, 200
  curve_vertex 64, 200
end 

color 126
shape do 
  vertex 60, 40
  bezier_vertex 160, 10, 170, 150, 60, 150
end