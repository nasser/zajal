# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Boolean data is one bit of information. True or false. It is common to use 
# Booleans with control statements to determine the flow of a program. In this 
# example, when the boolean value "x" is true, vertical black lines are drawn 
# and when the boolean value "x" is false, horizontal gray lines are drawn.

x = false

size 200, 200

1.step(width, 2) do |i|
  if i < width/2 then
    x = true
  else
    x = false
  end
  
  if x then
    color 255
    line i, 1, i, height-1
  end
  
  if not x then
    color 126
    line width/2, i, width-2, i
  end
end
