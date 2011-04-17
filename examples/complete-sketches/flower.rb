# Polygonal Flower
# Ramsey Nasser - Dec 2010

class Particle
  attr_accessor :x, :y
  
  def initialize x, y
    @x, @y = x, y
    
    @lifespan = 255
    
    @history = []
    
    a = random 0, TWO_PI
    k = 5
    @fx = k * cos(a)
    @fy = k * sin(a)
  end
  
  def update
    @x += @fx
    @y += @fy
    
    @lifespan -= 2
    
    history << self.clone
    history.shift if history.length > 200
    
    @fx *= 0.99
    @fy *= 0.99
  end
end

particles = []

setup do
  size 800
  # smoothing true
  line_width 4
  alpha_blending true
  title "Polygonal Flower"
  particles << Particle.new(width/2, height/2)
  particles << Particle.new(width/2, height/2)
  background 0
  framerate 60
end

update do
  once_every 2 do
    particles << Particle.new(width/2, height/2)
  end
  particles.each do |p|
    p.update
  end
  
  particles = particles.reject { |p| p.lifespan < 5 }
end

draw do
  particles.each_cons(2) do |a, b|
    min_history = [a.history.length, b.history.length].min
    for i in 0..min_history-1
      k = 240
      p = i / min_history.to_f
      color k, k*p, k, a.lifespan*p
      line a.history[i].x, a.history[i].y, b.history[i].x, b.history[i].y
    end
  end
end
