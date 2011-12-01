# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# This particular sketch calculates a de Jong attractor in real time and is, 
# as a result, SLOW.

# By Ramsey Nasser, May 2011
# Inspired by Thor Frolich's de Jong Attractor sketch
# http://www.openprocessing.org/visuals/?visualID=2097
# and the following resources
# http://paulbourke.net/fractals/peterdejong/
# http://nodebox.net/code/index.php/shared_2008-02-29-18-05-38

s = 500
x0, y0 = 0.0, 0.0

setup do
  size 800
  alpha_blending true
  background :black
  color :white, 100
end

draw do
  n = 10000
  
  a = 2
  b = -2.53
  c = 1.61
  d = -0.33

  # these are some interesting parameters. delete the comment symbol infront
  # of the lines you want to use.
  # a = 2
  # b = 1
  # c = 1.5
  # d = 0.1
  
  # a = -2
  # b = -2
  # c = -1.2
  # d = 2
  
  # a = -2.24
  # b = 0.43
  # c = -0.65
  # d = -2.43
  
  # a = 1.4
  # b = -2.3
  # c = 2.4
  # d = -2.1
  
  
  translate width/2, height/2 - 200
  scale 0.35
  for i in 0..n
    x1 = sin(a*y0) - cos(b*x0)
    y1 = sin(c*x0) - cos(d*y0)
  
    point x1*s, y1*-s
    x0, y0 = x1, y1
  end
end