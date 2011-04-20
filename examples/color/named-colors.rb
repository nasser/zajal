# zajal supports colors with descriptive names
color :orange
square 10, 10, 100
color :red
square 120, 10, 100

# the list of built in colors is based on the CSS3 specification. the full
# list is here: http://www.w3.org/TR/2003/CR-css3-color-20030514/#svg-color
# although zajal spells them a little differently (aliceblue becomes
# alice_blue). some of them are are crazy specific!
color :medium_violet_red
square 10, 120, 100
color :lemon_chiffon
square 120, 120, 100

# additionally, zajal defines two colors that are not in the CSS3
# specification, :light and :dark which correspond to the default foreground
# and background colors
color :light
square 10, 230, 100
color :dark
square 20, 240, 80

# you can also define your own named color with the 'named_color' method and
# use the color normally
named_color :my_awesome_blue, 100, 200, 300
color :my_awesome_blue
square 10, 340, 100