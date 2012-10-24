module Zajal
  module Graphics
    class Pixels
      def initialize
        @pointer = Native.ofpixels_new
      end

      def to_ptr
        @pointer
      end

      def << other
        case other
        when Fbo
          other.read_to_pixels self
        end
      end

      def save path, quality=:best
        Dir.chdir do
          Native.ofSaveImage @pointer, File.expand_path(path.to_s).to_ptr, quality
        end
      end

      # @api internal
      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/core/lib/libof.so"

        enum :ofImageQualityType, [ :best, :high, :medium, :low, :worst ]
        ofPixels = type(:ofPixels_).template(:unsigned_char).actually(:ofPixels)
        typedef :pointer, :ofPixels

        attach_constructor ofPixels, 24, []

        attach_function :ofSaveImage, [ofPixels.reference, :stdstring, :ofImageQualityType], :void
      end
    end
  end
end
