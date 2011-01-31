# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Simple curves are drawn with simple equations. By using numbers with values
# between 0 and 1 in the equations, a series of elegant curves are created. 
# The numbers are then scaled to fill the screen.

setup do
  size 200, 200
  fill false
end

draw do
  
  color 102
  shape do
    0.upto(width) do |i|
     vertex i, singraph(i/width)*height
    end
  end 
  
  color 140
  shape do 
    0.upto(width) do |i|
     vertex i, quad(i/width)*height
    end
  end 
  
  color 178
  shape do 
    0.upto(width) do |i|
     vertex i, quad_hump(i/width)*height
    end
  end 
  
  color 216
  shape do 
    0.upto(width) do |i|
     vertex i, hump(i/width)*height
   end
  end 
  
  color 255
  shape do 
    0.upto(width) do |i|
     vertex i, squared(i/width)*height
    end
  end 
end

def singraph sa
  sa =  (sa - 0.5) * 1.0 # scale from -1 to 1
  sa = sin(sa*Pi)/2 + 0.5
  
  return sa
end

def quad sa
  return sa**4
end

def quad_hump sa
  sa =  sa - 0.5 # scale from -2 to 2
  sa = sa**4 * 16
  
  return sa
end

def hump sa
  sa =  (sa - 0.5) * 2 # scale from -2 to 2
  sa = sa**2
  sa = 1 if sa > 1
  
  return 1 - sa
end

def squared sa
  sa = sa**2
  
  return sa
end