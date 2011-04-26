# Ramsey Nasser - Apr 2011
# Inspired by the Processing examples
# Play around with the code to see how it changes

# traditional looping in zajal is available, although for many purposes
# iteration is prefered. see the iteration example for more.

# zajal has a while loop like most other languages. it executes its code as
# long as its condition is true
j = 0
while j < 19
  circle 20 + j * 25, 150, 10 + j
  j += 1
end

# the opposite is the until loop. it executes its code as long as its
# condition is false
k = 20
until k < 0
  square 500 - k * 25, 250, k
  k -= 1
end

# for loops are also available, although
for i in (0..10)
  triangle 20 + i * 40, 350, i * 2
end