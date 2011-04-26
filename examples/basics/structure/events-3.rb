# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# some events pass in parameters that you can use. event parameters are always
# optional, and you can ignore them when not using them. here is the code from
# the second events example

circle_size = 50

setup do
  k = 20
  circle_size = k
end

update do
  i = sin(time * 0.001) * 2
  circle_size = circle_size += i
end

draw do
  circle width/2, height/2, circle_size
end

# here, we've decided to use the three parameters that mouse_pressed passes
# us. depending on which button is pressed, the circle will be set to a
# different size. different events pass different parameters, and this is
# discussed in the event's documentation.
mouse_pressed do |x, y, btn|
  circle_size = 50 if btn == :left
  circle_size = 150 if btn == :right
end