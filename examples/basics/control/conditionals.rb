# Ramsey Nasser - Apr 2011
# Inspired by the Processing examples
# Play around with the code to see how it changes

setup do
  size 500
end

draw do
  text [mouse_x, mouse_y]
  
  # basic if statment syntax
  color :red
  if mouse_x > 250 then
    circle 375, 250, 30
  end
  
  # the 'then' is optional
  color :blue
  if mouse_x > 375
    circle 435, 250, 15
  end 
  
  # else statment syntax
  color :green
  rectangle_mode :center
  if mouse_y > 250
    square 250, 375, 30
  else
    square 250, 125, 30
  end
  
  # conditions can be joined with and, or, not
  color :white
  if mouse_x < 30 and mouse_y > 30
    text "corner!"
  end
  
  # ifs can be chained with elsif (else if)
  color :yellow
  rectangle_mode :corner
  if mouse_x > 0 and mouse_x < 10
    rectangle 0, 0, 10, 500
  elsif mouse_x > 10 and mouse_x < 20
    rectangle 10, 0, 10, 500
  elsif mouse_x > 20 and mouse_x < 30
    rectangle 20, 0, 10, 500
  elsif mouse_x > 30 and mouse_x < 40
    rectangle 30, 0, 10, 500
  elsif mouse_x > 40 and mouse_x < 50
    rectangle 40, 0, 10, 500
  end
  
  # some objects have methods that end in '?'. these return true or false. in
  # other languages, this might be written as mouse_x.isEven().
  if mouse_x.even? then
    color :black
  else
    color :white
  end
  
  vertical mouse_x
  
  # one liners can be condensed like this
  color :white
  text "mouse on right side of screen" if mouse_x > 250
  
  # the opposite of if is unless. it is equivalent to "if not"
  color :white
  unless mouse_y < 450
    text "bottom"
  end
  
  # it can also be condensed
  text "really, the bottom!" unless mouse_y < 450
end