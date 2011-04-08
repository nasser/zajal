class Fixnum
  def to_ref
    ObjectSpace._id2ref self
  end
end