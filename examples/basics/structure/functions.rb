# Ramsey Nasser - Apr 2011
# Inspired by the Processing examples
# Play around with the code to see how it changes

# functions are defined with the 'def' keyword, followed by the function name
# and arguments
def jet x, y, z=1, size=20
  color (32..240) * 1/z
  triangle x, y, size, 80
  triangle x, y, size *1.5, 30
end

# functions can then be called like any other method in zajal
jet width/2, height/2, 1, 100

# and can be used in any way
seed_random 9000
50.times do
  jet random_width, random_height, random(8), random(10, 30)
end

