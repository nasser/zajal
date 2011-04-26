# Ramsey Nasser - Apr 2011
# Inspired by the Processing examples
# Play around with the code to see how it changes

# TODO fix variable name bug
draw do
  # in zajal, variables do not need to be declared. they "spring into existence"
  # when you assign something to them

  my_name = "Ramsey"
  # the variable 'my_name' now exists and has the value "Ramsey" you can use is
  # anywhere.
  text my_name

  # variables also don't have any type, so you can store any value in them you
  # want. think of them as labels on data that you can manipulate freely.
  my_name = 5
  # my_name is now equal to 5
  text my_name
end