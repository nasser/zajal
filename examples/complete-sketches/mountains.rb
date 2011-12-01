# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011
# Inspired by antiplastik's Mountains sketch
# http://www.openprocessing.org/visuals/?visualID=3559

rail_x = 200

setup do
  size 900
  smoothing true
  background 228, 140, 131
  alpha_blending true
  vertical_sync true
end
  
draw do
  color 127, 128, 148
  # try changing 0.25 to -2.0
  draw_mountains 150, 0.25, 200, 100
  
  color 72, 96, 133
  draw_mountains 300, 0.5, 300, 80
  
  color 45, 69, 106
  draw_mountains 600, 1, 400, 80
  
  color 27, 48, 74
  draw_mountains 800, 2, 700, 80
  
  color 16, 26, 46
  rectangle 0, 850, width, 100
  
  color 16, 26, 46
  rectangle rail_x, 800, 100, 300
  
  rail_x -= 150
  rail_x = width + 1000 if rail_x < -1000
end

def draw_mountains y, speed, spacing, size
  # try changing k to something higher (like 40) and see how the quality of
  # the mountains changes
  k = 2
  shape do
    for i in 0..width/k
      vertex i*k, y + signed_noise(time * 0.001 * speed + (i*k) * (1.0/spacing)) * size
    end
    vertex width, height
    vertex 0, height
  end
end