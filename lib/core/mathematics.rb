module Zajal
  # @api zajal
  module Mathematics
    # @overload noise
    #   @return [0.0..1.0] noise over time
    # @overload noise x
    #   @return [0.0..1.0] noise at (x)
    # @overload noise x, y
    #   @return [0.0..1.0] noise at (x, y)
    # @overload noise x, y, z, 
    #   @return [0.0..1.0] noise at (x, y, z, )
    # @overload noise x, y, z, w
    #   @return [0.0..1.0] noise at (x, y, z, w)
    def noise x=nil, y=0.0, z=0.0, w=0.0
      x = time unless x.present?
      Native.ofNoise x.to_f, y.to_f, z.to_f, w.to_f
    end
    
    # @overload signed_noise
    #   @return [-1.0..1.0] signed noise over time
    # @overload signed_noise x
    #   @return [-1.0..1.0] signed noise at (x)
    # @overload signed_noise x, y
    #   @return [-1.0..1.0] signed noise at (x, y)
    # @overload signed_noise x, y, z
    #   @return [-1.0..1.0] signed noise at (x, y, z, )
    # @overload signed_noise x, y, z, w
    #   @return [-1.0..1.0] signed noise at (x, y, z, w)
    def signed_noise x=nil?, y=0.0, z=0.0, w=0.0
      x = time unless x.present?
      Native.ofSignedNoise x.to_f, y.to_f, z.to_f, w.to_f
    end
    
    # @api internal
    def random *args
      rand *args
    end

    # @api internal
    module Native
      extend FFI::Cpp::Library

      ffi_lib "lib/core/lib/libof.so"

      attach_function :ofDegToRad, [:float], :float
      attach_function :ofRadToDeg, [:float], :float

      attach_function :ofNoise, [:float, :float, :float, :float], :float
      attach_function :ofSignedNoise, [:float, :float, :float, :float], :float
    end
  end
end

class Numeric
  def to_deg
    Zajal::Mathematics::Native.ofRadToDeg self.to_f
  end

  def to_rad
    Zajal::Mathematics::Native.ofDegToRad self.to_f
  end
end