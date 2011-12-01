# This code is running live. You are invited to edit anything below. Hit save 
# to see the sketch window update to match your changes.

# By Ramsey Nasser, May 2011

class NebulaSection
  attr_accessor :x, :y, :w, :h, :r, :g, :b, :a
end

nebula = []
max_r = 250
max_size = 500

nx = 0
ny = 0

setup do
  size 800
  alpha_blending true
  smoothing true
  background :black
end

update do
  new_section = NebulaSection.new
  # uncomment these lines for random motion
  # new_section.x = noise(time * 0.00003) * width
  # new_section.y = noise(time * 0.00003 + 1) * height
  nx = (nx..mouse_x) * 0.01
  ny = (ny..mouse_y) * 0.01
  new_section.x = nx
  new_section.y = ny
  new_section.w = max_r*noise(time * 0.0003)
  new_section.h = max_r*noise(time * 0.0003 + 1)
  
  t = noise(new_section.x, new_section.y)
  new_section.r = (0..255) * t
  new_section.g = (255..64) * t
  new_section.b = (200..255) * t
  new_section.a = (8..32) * t
  nebula << new_section
  
  while nebula.size > max_size
    nebula.shift
  end
end

draw do
  nebula.every do |section, i|
    fill false
    color section.r, section.g, section.b, section.a * i/nebula.size.to_f
    ellipse section.x, section.y, section.w, section.h 
  end
end