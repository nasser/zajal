# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# gradients can be drawn by drawing differently colored lines
for i in 0..height
  # as i increases from 0 to 100, i/100 increases from 0.0 to 1.0 and
  # i/100 increases from 0 to 255, meaning the color of each line is ramped
  # from black to white. this is called 'linear interpolation'.
  color i/height * 255
  horizontal i, 0, 99
end

# zajal provides a Range object which can be used to deal with linear
# interpolation easily.
for i in 0..height
  gray_range = 0..255
  color i/height * gray_range
  horizontal i, 100, 199
end

# this allows for much more readable code than would have been possible
# otherwise. it puts the important data in one place. try changing the values
# of the r, g and b ranges bellow.
for i in 0..height
  r = 128..64
  g = 128..0
  b = 0..255
  
  t = i/height
  color r * t, g * t, b * t 
  horizontal i, 200, 299
end

# you can also change the shape of the gradient by raising i/height to a power
# using the ** operator
for i in 0..height
  color (0..255) * (i/height)**0.5
  horizontal i, 300, 399
end

for i in 0..height
  color (0..255) * (i/height)**2
  horizontal i, 400, 500
end
