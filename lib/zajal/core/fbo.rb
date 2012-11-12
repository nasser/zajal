module Zajal
  module Graphics
    class Fbo
      def initialize width, height, samples=0
        @pointer = Native.offbo_new
        Native.offbo_allocate @pointer, width.to_i, height.to_i, 0x1908, samples # GL_RGBA=0x1908
      end

      def to_ptr
        @pointer
      end

      def to_pixels
        pix = Zajal::Graphics::Pixels.new
        pix << self
        pix
      end

      def begin setup_screen=true
        Native.offbo_begin @pointer, setup_screen.to_bool
      end

      def end
        Native.offbo_end @pointer
      end

      def use
        self.begin
        yield
        self.end
      end

      def width
        Native.offbo_getWidth @pointer
      end

      def height
        Native.offbo_getHeight @pointer
      end

      def allocated?
        Native.offbo_isAllocated @pointer
      end

      def draw x, y, w=nil, h=nil
        w = width unless w.present?
        h = height unless h.present?

        Native.offbo_draw @pointer, x.to_f, y.to_f, w.to_f, h.to_f
      end

      def anchor x, y
        Native.offbo_setAnchor @pointer, x.to_f, y.to_f
      end

      def anchor_percent x, y
        Native.offbo_setAnchorPercent @pointer, x.to_f, y.to_f
      end

      def reset_anchor
        Native.offbo_resetAnchor @pointer
      end

      def read_to_pixels pix, attachment=0
        Native.offbo_readToPixels @pointer, pix.to_ptr, attachment
      end

      def texture
        Native.offbo_getTextureReference @pointer
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/zajal/core/lib/libof.so"

        attach_constructor :ofFbo, 232, []
        attach_method :ofFbo, :allocate, [:int, :int, :int, :int], :void
        attach_method :ofFbo, :begin, [:bool], :void
        attach_method :ofFbo, :end, [], :void
        attach_method :ofFbo, :getTextureReference, [], :pointer
        attach_method :ofFbo, :isAllocated, [], :bool
        attach_method :ofFbo, :draw, [:float, :float, :float, :float], :void
        attach_method :ofFbo, :setAnchorPercent, [:float, :float], :void
        attach_method :ofFbo, :setAnchorPoint, [:float, :float], :void
        attach_method :ofFbo, :resetAnchor, [], :void
        attach_method :ofFbo, :getWidth, [], :float
        attach_method :ofFbo, :getHeight, [], :float

        ofPixels = type(:ofPixels_).template(:unsigned_char).actually(:ofPixels)
        typedef :pointer, :ofPixels
        attach_method :ofFbo, :readToPixels, [ofPixels.reference, :int], :void
      end
    end
  end
end