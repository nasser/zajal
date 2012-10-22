module Zajal
  module Frontends
    # Windowless renderer
    # 
    # @api internal
    class Headless < Frontend
      class Sketch < Zajal::Sketch; end
      
      attr_reader :fbo

      def initialize w, h
        @pointer = Native.minimalfrontend_new
        Zajal::Graphics::Native.ofSetupOpenGL @pointer, w.to_i, h.to_i, 0 # TODO move this
        
        @fbo = Zajal::Graphics::Fbo.new w, h
      end

      def run
        # fbo images are flipped otherwise
        @sketch.class.before_event :draw do
          Zajal::Graphics::Native.ofSetupScreenPerspective width.to_f, height.to_f, :default, false, 60.0, 0.0, 0.0
        end

        @fbo.capture do
          @sketch.setup
          @sketch.update
          @sketch.draw
        end
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/frontends/minimal/lib/MinimalFrontend.so"
        attach_constructor :MinimalFrontend, 16, []
      end
    end
  end
end
