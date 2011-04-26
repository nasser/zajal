# Ramsey Nasser - Apr 2011
# Inspired by the Processing examples
# Play around with the code to see how it changes

# curves are drawn with four points. the second and thrid points (b and c in
# the example) are the start and end points of the curve while the first and
# last points (a and d in the example) control the shape of the curve. try
# changing the values to see how it works.

# you can list the points out as x, y pairs, but this is tedious
fill false
curve 10, 10, 20, 20, 490, 20, 500, 200

# its often easier to create points instead. see the points example for more.
a = Point.new(50, 490)

b = Point.new(50, 300)
c = Point.new(150, 300)

d = Point.new(150, 100)

# uncomment the next two lines to tie the last control point to the mouse
# d.x = mouse_x
# d.y = mouse_y

a.draw
b.draw
c.draw
d.draw

fill false
curve a, b, c, d


# bezier curves are similar, except the first and last points (e and h in the
# example) are the start and end points and the second and third (f and g in
# the example) are the control points.
e = Point.new(250, 300)

f = Point.new(250, 490)
g = Point.new(450, 100)

h = Point.new(450, 300)

# uncomment the next two lines to tie he first control point to the mouse
# f.x = mouse_x
# f.y = mouse_y

e.draw
f.draw
g.draw
h.draw

bezier e, f, g, h