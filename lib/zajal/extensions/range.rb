class Range
  def * t
    first * t + last * (1-t)
  end
end