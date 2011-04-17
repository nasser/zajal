# Wormsign
# Ramsey Nasser - Nov 2010

t = 0

setup do
  size 500
  # smoothing true
  alpha_blending true
  circle_resolution 64
  background 0
  title "Wormsign"
  framerate 60
end

def disc x, y, r, res
  res.times do |n|
    p = n/res.to_f
    q = 1-p
    
    color 0, 40*p
    circle x, y, (r*1.5)*q
  end
  
  color 230, 25, 25
  circle x, y, r
end

draw do
  color 255
  text framerate.round
  t += 0.02
  
  80.times do |n|
    n *= 0.1
    disc 100+n*30+sin(t+n)*40, 240+sin(t+n)*40, 40+cos(n)*10, 5
  end
end

