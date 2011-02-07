# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Integers and floats are two different kinds of numerical data. An integer is
# a number without a decimal point. A float is a floating-point number, which 
# means it is a number that has a decimal place. Floats are used when more 
# precision is needed.

a, b = 0, 0

setup do
  size 200, 200
end

draw do
  a = a + 1     # add an integer to a number
  b = b + 0.2   # add a float to a number
  
  line a, 0, a, height/2
  line b, height/2, b, height
  
  a = 0 if a > width
  b = 0 if b > width
end
