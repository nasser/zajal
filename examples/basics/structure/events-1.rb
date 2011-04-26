# Ramsey Nasser - Apr 2011
# Play around with the code to see how it changes

# you can write code to run at specific times by using events. this is similar
# to the setup/update/draw loop that processing and openframeworks hackers
# will know

# code outside of an event will be run once at the start of a sketch. any
# variables defined here will be available anywhere in the code

circle_size = 50

# this is the setup event. the code between do and end will be run once at
# the start of a sketch. any variables defined here will only be available in
# the setup event.
setup do
  k = 20
  circle_size = k
end

# this is the update event. the code between do and end will be run once at
# the start of each frame. any variables defined here will only be available
# in the update event.
update do
  i = sin(time * 0.001) * 2
  circle_size = circle_size += i
end

# this is the draw event. the code between do and end will be run once each
# frame directly after the update event. any variables defined here will only
# be available in the draw event. any drawing methods used here will draw to
# the sketch window.
draw do
  circle width/2, height/2, circle_size
end