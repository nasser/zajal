module Zajal
  module Frontends
    # Windowless renderer
    # 
    # @api internal
    class Headless < Frontend
      class Sketch < Zajal::Sketch; end

      def initialize w, h
        @pointer = Native.headlessfrontend_new
        Zajal::Graphics::Native.ofSetupOpenGL @pointer, w, h, 0 # TODO move this
      end

      def run
        # fbo images are flipped
        @sketch.class.before_event :draw do
          translate width/2, height/2
          scale 1, -1, 1
          translate -width/2, -height/2
        end

        fbo = Native.offbo_new
        Native.offbo_allocate fbo, 100, 100, 0x1908, 0

        Native.offbo_begin fbo, true
        @sketch.setup
        @sketch.update
        @sketch.draw
        Native.offbo_end fbo

        pix = Native.ofpixels_new
        Native.offbo_readToPixels fbo, pix, 0
        Native.ofSaveImage pix, File.expand_path("~/Desktop/screen.png").to_ptr, :best
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/core/lib/libof.so"

        ofPixels = type(:ofPixels_).template(:unsigned_char).actually(:ofPixels)
        typedef :pointer, :ofGLRenderer
        typedef :pointer, :ofPixels
        enum :ofImageQualityType, [ :best, :high, :medium, :low, :worst ]

        attach_constructor :ofFbo, 232, []
        attach_method :ofFbo, :begin, [:bool], :void
        attach_method :ofFbo, :end, [], :void
        attach_method :ofFbo, :allocate, [:int, :int, :int, :int], :void
        attach_method :ofFbo, :readToPixels, [ofPixels.reference, :int], :void

        attach_constructor ofPixels, 24, []

        attach_function :ofSaveImage, [ofPixels.reference, :stdstring, :ofImageQualityType], :void

        ffi_lib "lib/frontends/headless/lib/HeadlessFrontend.so"
        attach_constructor :HeadlessFrontend, 16, []
      end
    end
  end
end
