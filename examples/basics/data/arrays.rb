# arrays are lists of data. they are created using square brackets '[]'
empty_ary = []

# to create an array with data in it, you can list the data out seperated by
# commas inside the square brackets
number_ary = [150, 190, 220]

# arrays don't care what kind of data you put in them
other_ary = ["hello", 45, Point.new(100, 200), :world]

# arrays can be printed to quickly see their content
color :cyan
text empty_ary
text number_ary
text other_ary

# the array supports many different methods. here are a few of the more
# interesting ones

# append to an array
color :green
number_ary << 300
number_ary << 340
text number_ary

# get an array's size
color :red
text number_ary.size

# reverse its contents
color :orange
text number_ary.reverse

# reject some items
color :purple
number_ary.reject! { |x| x < 200 }
text number_ary

# check out http://www.ruby-doc.org/core/classes/Array.html for more

# they can also be iterated over. see the iteration example for more.
color :yellow
number_ary.each do |y|
  horizontal y
end