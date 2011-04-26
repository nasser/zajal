# the "times" method is useful for setting up arrays
seed_random 9003
pts = []
10.times do
  pts << Point.new(random_width, random_height)
end

# an alternative to "each" is "every". think of it as a super charged "each"
# method. by default, it behaves just like "each".
smoothing true

pts.every do |a|
  circle a.x, a.y, 10
end

# but it also passes in an optional parameter that indicates ...
pts.every do |a, i|
  color i.to_f/pts.size * 240
  circle a.x, a.y, 5
end

color :white
line_width 5
pts.every 2 do |a, b|
  line a, b
end


line_width 3
pts.every 2 do |a, b, i|
  color i.to_f/pts.size * (64..255)
  line a, b
end