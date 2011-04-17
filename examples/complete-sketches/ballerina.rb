t = 0
v = 0

setup do
  title "Ballerina"
  smoothing true
  framerate 60
end

update do
  v += 0.005
  t = sin(v)*100
end

def trig w, n
  sin(2*n+w*0.05)*40*sin(n/50.0)
end

draw do
  color 240
  text "%0.2f"%framerate, width - 50, height - 10
  
  near = []
  far = []
  
  # determine x's
  158.times do |n|
    x = trig(t, n)
    nx = trig(t+1, n)
    p = x.abs/(40*sin(n/50.0))
    p = 0.0 if p.nan?
    
    # determine color and size
    if nx > x
      # far
      c = 64 * (1-p) + 200*p
      r = 0.5 + 0.5 * p
      
      far << [x, n-160/2, r, c]
    else
      # near
      c = 240 * (1-p) + 200*p
      r = 1.5 - 0.5 * p
      
      near << [x, n-160/2, r, c]
    end
  end
  
  # draw points
  matrix do
    translate width/2, height/2
    scale width/180.0, height/180.0
    rotate 15
    
    far.each do |point|
      x, y, r, c = point
      color c
      circle x, y, r
    end
    near.each do |point|
      x, y, r, c = point
      color c
      circle x, y, r
    end
  end
  
end
