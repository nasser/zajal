# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

horizontal 10

line_width 2
horizontal 20

line_width 3
horizontal 30

line_width 4
horizontal 40

line_width 5
horizontal 50

line_width 6
horizontal 60

line_width 1
square 10, 100, 100

fill false
square 120, 100, 100
fill true
square 230, 100, 100
fill false
square 340, 100, 100

rectangle_mode :center
square 60, 300, 100
rectangle_mode :corner
square 60, 300, 100

fill true
circle 250, 300, 20
circle_resolution 16
circle 300, 300, 20
circle_resolution 8
circle 350, 300, 20
circle_resolution 5
circle 400, 300, 20
circle_resolution 3
circle 450, 300, 20