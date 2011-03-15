# all important syntax sugar

# lerp across ranges
class Range
  def * t
    self.begin * (1.0 - t) + self.end * (t)
  end
end

class Float 
  alias :old_mult :*
  def * other
    if other.is_a? Range then
      other * self
    else
      self.old_mult(other)
    end
  end
end


# add sugar to some each* methods
class Array
  alias :each_consecutive :each_cons 
  def each_pair &block
    each_cons 2, &block
  end
end

# implement pattern rejection
class String
  def reject pattern
    gsub pattern, ""
  end
  
  def reject! pattern
    gsub! pattern, ""
  end
end

def min *args
  args.min
end

def max *args
  args.max
end

def avg *args
  args.reduce(:+) / args.size.to_f
end
  
# run a block once every f frames, return true every f frames
def once_every f
  yield if block_given? and frame % f == 0
  return frame % f == 0
end

def horizontal y, x1=nil, x2=nil
  if x1 and x2
    line x1, y, x2, y
  else
    line 0, y, width, y
  end
end

def vertical x, y1=nil, y2=nil
  if y1 and y2
    line x, y1, x, y2
  else
    line x, 0, x, height
  end
end