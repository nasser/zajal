class Object
  def blank?
    respond_to?(:empty?) ? empty? : self.nil?
  end

  def present?
    !blank?
  end
end