module Zajal
  module Frontends
    # The basic, command-line friendly frontend.
    # 
    # This is a replacement for the GLUT based windows that openFrameworks
    # uses. GLFW is much easier to work with than GLUT, and doesn't hog
    # the main loop.
    # 
    # @api internal
    class Glfw
      # The sketch to render
      # 
      # A sketch must be set before {#run} is called.
      attr_accessor :sketch

      # Create a new Glfw frontend, and open a window with size +(width,height)+
      # 
      # @param width [Numeric] width of the window
      # @param height [Numeric] height of the window
      # 
      # @todo Solve initial window size problem
      def initialize width, height
        @window = Native.glfwfrontend_new
        Zajal::Graphics::Native.ofSetupOpenGL @window, width, height, 0
      end

      # Run the sketch
      # 
      # Kicks off setup/update/draw loop for the attached sketch
      # 
      # @example
      #   glfw = Zajal::Frontends::Glfw.new 100, 100
      #   glfw.sketch = Zajal::Sketch.new "user.zj"
      #   glfw.run
      # 
      # @return [nil] Nothing
      def run
        @sketch.setup
        while true do
          Zajal::Graphics::Native.ofSetupScreen
          @sketch.update
          Zajal::Graphics::Native.ofClear 160.0, 37.0, 37.0, 255.0
          @sketch.draw
          Native.glfwSwapBuffers

          @sketch = @sketch.refresh_continue if @sketch.stale?
        end
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/frontends/glfw/lib/libglfw.dylib"
        attach_function :glfwSwapBuffers, [], :void
        attach_function :glfwSetWindowPos, [:int, :int], :void

        ffi_lib "lib/frontends/glfw/lib/GlfwFrontend.so"
        attach_constructor :GlfwFrontend, 16, []
        attach_method :GlfwFrontend, :setWindowShape, [:int, :int], :void
      end
    end
  end
end