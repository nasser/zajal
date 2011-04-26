# iteration deals with looping through a collection (like an array) using
# blocks, so make sure to check out the array and blocks examples before
# diving into this

cities = ["hsain", "beirut", "tripoli", "sidon", "jbeil", "amcheet"]

# it might be tempting to loop through the array like this, as you would in
# other languages
for i in (0..cities.size-1)
  text cities[i]
end

text "==="

# while this works, iterating using the "each" method is much cleaner
cities.each do |city|
  text city
end

# the "each" method of arrays runs the given block once on each item in the
# array, passing that item to the block as a parameter

# it is possible to do for-loop style iteration as well. integers have a 
# "times" method that run the given block a number of times equal to the
# receiving integer, e.g. 5.times will run the given block five times
color 64
20.times do |i|
  horizontal 18 + i * 13
end

# like all blocks, you can ignore the parameter
color :white
5.times do
  text "Hello"
end