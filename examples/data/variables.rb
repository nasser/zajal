# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Variables are used for storing values. In this example, changing the values 
# of variables 'a' and 'b' significantly change the composition.

size 200, 200

a = 20
b = 50

c = a*8
d = a*9
e = b-a
f = b*2
g = f+e

line a, f, b, g
line b, e, b, g
line b, e, d, c
line a, e, d-e, c