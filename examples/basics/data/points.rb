# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# a point represents a point in space, often a two dimentional point on the
# sketch window. they are useful to store and manipulate positions.

# to create a point, do this
a = Point.new(200, 300)

# points can be drawn right away. try changing the coordinates in the previous
# line to see how the point moves
a.draw

# points have x and y values that are very useful for drawing other shapes
b = Point.new(100, 50)
fill false
circle b.x, b.y, 10

# many graphics methods take points as an alternative to x and y coordinates.
# instead of typing `line a.x, a.y, b.y, b.y` you can type
line a, b