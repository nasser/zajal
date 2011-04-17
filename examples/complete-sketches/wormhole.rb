# Wormhole
# Ramsey Nasser - Feb 2011

x, y = 250, 250

setup do
  size 500
  title "Wormhole"
  background 255
  fill false
  alpha_blending true
  smoothing true
  circle_resolution 64
end

draw do
  alpha = 0..200
  radius = 100..500
  depth = 40
  
  depth.times do |n|
    t = n/depth.to_f
    
    color 0, alpha * t
    circle x, y + sin(time * 0.001 + n * 0.25) * 30, radius * t**2
  end
end

key_down do |key|
  x -= 10 if key == :left
  x += 10 if key == :right
end