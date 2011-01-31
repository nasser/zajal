# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# The draw block creates a structure in which to write programs that
# change with time.

# The statements in the setup block
# execute once when the program begins
setup do
  size 200, 200
  
  # Set line drawing color to white
  color 255      
  framerate 30
  background 0
end

y = 100

# The statements in draw are executed until the 
# program is stopped. Each statement is executed in 
# sequence and after the last line is read, the first 
# line is executed again.
draw do
  y = y - 1
  y = height if y < 0
  
  line 0, y, width, y  
end