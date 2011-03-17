# point drawing and class
require "matrix"

module Mathematics
  module Internals
    # TODO should this just be a constant, EPSILON like PI?
    @epsilon = 0.01
    
    def self.scan_for_vectors dim, *args
      raise ArgumentError, "can't mix Vectors and non-Vectors!" if args.any? { |v| v.is_a? Vector } and args.any? { |v| not v.is_a? Vector } 
      
      args.all? { |v| v.is_a? Vector } ? args : args.each_slice(dim).map { |coords| Vector.new coords }
    end
    
  end
  
  def point x, y
    circle x, y, 1
  end
  
  class Vector < ::Vector
    class << self
      def new *args
        super args.first.is_a?(Array) ? args.first : args
      end
      
      # TODO confines to a square of size amount*2, is this good? circle?
      def rand dim, amount
        new dim.times.map { random(-amount,amount) }
      end
      
      # TODO 3 dimentions, is this arbitrary?
      def zero;     new [0, 0,  0] end
    
      def right;    new [ 1, 0, 0] end
      def left;     new [-1, 0, 0] end
    
      def up;       new [0,  1, 0] end
      def down;     new [0, -1, 0] end
    
      def forward;  new [0, 0,  1] end
      def backward; new [0, 0, -1] end
    end
    
    # named components
    def x; self[0] end
    def x=(k); self[0] = k end
  
    def y; self[1] end
    def y=(k); self[1] = k end
  
    def z; self[2] end
    def z=(k); self[2] = k end
  
    def w; self[3] end
    def w=(k); self[3] = k end
    
    alias :dimentions :size
    alias :length :r
    
    include ExceptionForMatrix
    
    # true if the other vector is, within tolerances, equal to self
    # TODO is this the best syntax?
    def =~ other
      Vector.Raise ErrDimensionMismatch if size != other.size
      (self - other).all? { |c| c.abs < Internals.epsilon }
    end
    
    def aligned_with? other
      Vector.Raise ErrDimensionMismatch if size != other.size
      (self.angle - other.angle).abs < Internals.epsilon
    end
    
    def scale s
      if length > 0
        map { |e| (e/length) * s }
      else
        self
      end
    end
    
    def scale! s
      @elements.map! { |e| (e/length) * s } if length > 0
      nil
    end
    
    # this is nonsensical, and in place just so that (a..b) * k will work for vectors
    def <=> other; 0 end
    
    def distance_squared other
      Vector.Raise ErrDimensionMismatch if size != other.size
      zip(other).reduce(0) { |memo, elts| a, b = elts; memo + (a-b)**2 }
    end
    
    def distance other
      sqrt distance(other)
    end
    
    def normalize
      scale 1.0
    end
    
    def normalize!
      scale! 1.0
    end
    
    def limit max
      if length > max and length > 0
        map { |e| e*(max/length) }
      else
        self
      end
    end
    
    def limit! max
      @elements.map! { |e| e*(max/length) } if length > max and length > 0
      nil
    end
      
    def draw
      point x, y
    end
    
    # TODO better name?
    def draw_ray *coords
      p, = Internals.scan_for_vectors 2, *coords
      line x, y, x + p.x, y + p.y
    end
    
  end
  
  # aliasing
  class Point < Vector; end
  
  # yoink!
  class Matrix < ::Matrix; end

end

Object.send(:remove_const, :Vector)
Object.send(:remove_const, :Matrix)