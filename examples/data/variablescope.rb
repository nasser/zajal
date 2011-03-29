# Original work (c) Ben Fry, Casey Reas and the Processing Project
# 
# Translated to Zajal by Ramsey Nasser
# ported from the processing examples at http://processing.org/learning/basics

# Variables may either have a global or local "scope". For example, variables 
# declared within either the setup or draw functions may be only used in these 
# functions. Global variables, variables declared outside of setup and loop, 
# may be used anywhere within the program. If a local variable is declared 
# with the same name as a global variable, the program will use the local 
# variable to make its calculations within the current scope. Variables may 
# be localized within classes, functions, and iterative statements.

a = 20  # Create a global variable "a"

setup do
  size 200, 200
end

draw do
  # Draw a line using the global variable "a"
  line a, 0, a, height
  
  # Create a new variable "a" local to the each block
  for a in 50..80
    line a, 0, a, height
  end
  # for a=50 a<80 a += 2) {
  #   line a, 0, a, height
  # }
  
  # Create a new variable "a" local to the loop ) method
  # a = 100
  # Draw a line using the new local variable "a"
  # line a, 0, a, height  
  
  # Make a call to the custom function draw_another_line
  draw_another_line 185
  
  # Make a call to the custom function draw_yet_another_line
  draw_yet_another_line
end

def draw_another_line a
  # Create a new variable "a" local to this method
  # Draw a line using the local variable "a"
  line a, 0, a, height
end

def draw_yet_another_line
  p a
  # Because no new local variable "a" is set, 
  # this lines draws using the original global
  # variable "a" which is set to the value 20.
  line a+2, 0, a+2, height
end
