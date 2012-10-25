class Object
  # An object is blank if it's nil, empty, or a whitespace string.
  def blank?
    respond_to?(:empty?) ? empty? : self.nil?
  end

  # An object is present if it's not `blank?`.
  def present?
    not blank?
  end

  # Convert object into actual true or false object
  def to_bool
    self ? true : false
  end
end