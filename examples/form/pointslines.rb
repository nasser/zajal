# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Constructing a simple dimensional form with lines and rectangles. Changing
# the value of the variable 'd' scales the image. The four variables set the
# positions based on the value of 'd'.

d = 40
p1 = d
p2 = p1+d
p3 = p2+d
p4 = p3+d

size 200, 200
background 0

# Draw gray box
color 153
line p3, p3, p2, p3
line p2, p3, p2, p2
line p2, p2, p3, p2
line p3, p2, p3, p3

# Draw white points
color 255
point p1, p1
point p1, p3 
point p2, p4
point p3, p1 
point p4, p2
point p4, p4