# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# events are also used to respond to user input. here is the code from the
# first events example

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

# this is the mouse_pressed event. code between do and end will run every
# frame that the mouse is pressed. here, it is forcing circle_size to remain
# at 50, which stops the circle from animating as long as the mouse is held
# down
mouse_pressed do
  circle_size = 50
end