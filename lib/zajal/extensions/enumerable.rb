module Enumerable
  def each_pair &blk
    each_cons(2, &blk)
  end
end