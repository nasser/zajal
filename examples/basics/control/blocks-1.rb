draw do
  # blocks are an important and often misunderstood feature in zajal and ruby.
  # a block is an anonymous function, delimited by "do" and "end" you define on
  # the spot and then pass to a method to control how it behaves.

  # for example, integers have a "times" method that runs the given block the
  # amount of times represented by the integer.

  # this will print "I am in a block" ten times.
  color :red
  10.times do
    text "I am in a block"
  end

  # what's happening is that the code between the "do" and "end" is being passed
  # to the times method as a parameter, just like the symbol :red gets passed
  # to the color method above as a parameter. the method is free to do whatever
  # it wants with the block, just as it can do whatever it wants with any other
  # parameter
  
  # the once_every method takes an integer and a block and runs that block
  # once for every given number of frames that pass. this code prints out
  # "Hi there" once every 20 frames
  once_every 20 do
    color :cyan
    text "Hi there"
  end
  # what a method does with its block is part of its documentation
end