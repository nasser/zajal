class Object
  def blank?
    respond_to?(:empty?) ? empty? : self.nil?
  end

  def present?
    not blank?
  end

  def to_bool
    self ? true : false
  end
end