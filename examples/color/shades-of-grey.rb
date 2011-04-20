# in zajal, there is always a "current color" that everything is drawn in.
# by default, the current color is set to almost-white, so when you draw a
# square draw a square, that's the color its drawn in
square 10, 10, 100

# the 'color' method command changes the current color. until the color method
# is called again, everything will be drawn with the current color.
color 128
square 120, 10, 100

# the second square is a darker shade of gray because of line 7. how does the
# number 128 turn into gray? there are a few ways to describe a color in
# zajal. the simplest way, seen above, is to just use a number between 0 and
# 255. this sets the current color to a shade of gray, where lower numbers are
# darker and higher numbers are lighter.

# remember, colors stay in effect until the color method is called again. this
# row is half-dark half-light
color 200
square 10, 120, 100
square 120, 120, 100
color 20
square 230, 120, 100
square 340, 120, 100

# try playing around with these values to see what you get
color 60
square 10, 230, 100
color 40
square 120, 230, 100
color 20
square 230, 230, 100
color 0
square 340, 230, 100

# remember, colors affect everything drawn
color 0
circle 60, 400, 50
color 64
triangle 170, 400, 50
color 128
ellipse 280, 400, 25, 60
color 255
rectangle 340, 375, 100, 40
