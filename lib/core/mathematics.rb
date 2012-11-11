module Zajal
  module Mathematics
    def noise x=nil, y=0.0, z=0.0, w=0.0
      x = time unless x.present?
      Native.ofNoise x.to_f, y.to_f, z.to_f, w.to_f
    end
    
    def signed_noise x=nil, y=0.0, z=0.0, w=0.0
      x = time unless x.present?
      Native.ofSignedNoise x.to_f, y.to_f, z.to_f, w.to_f
    end
    
    def random *args
      rand *args
    end

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