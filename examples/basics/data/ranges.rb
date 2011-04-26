# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# a range represents a linear span of objects, usually numbers. to create one
# do this

rng = (40..100)

# you can check if a something is inside a range
color :red
text rng.include? 30
text rng.include? 45

# you can multiply a range by a number between zero and one to perform linear
# interpolation. multiplying by zero returns the first number, multiplying by
# one returns the last number and multiplying by anything in between returns
# a number that "slides" betwen the first and last number.
color :green
text rng * 0.0
text rng * 0.25
text rng * 0.5
text rng * 0.75
text rng * 1.0

# this is useful for doing gradients. try playing with the values that define
# the range above to see how the gradient changes.
for i in 0..15
  color rng * (i/15.0)
  circle 100 + i * 20, 20, 10
end