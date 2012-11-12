module Zajal
  module Frontends
    # The basic, command-line friendly frontend.
    # 
    # This is a replacement for the GLUT based windows that openFrameworks
    # uses. GLFW is much easier to work with than GLUT, and doesn't hog
    # the main loop.
    # 
    # @api internal
    class Glfw < Frontend
      class Sketch < Zajal::Sketch
        support_event :mouse_down, :mouse_pressed, :mouse_up, :mouse_moved
        support_event :key_down, :key_pressed, :key_up

        def time
          @bare ? 0.0 : super
        end

        def frame
          @bare ? 0 : super
        end

        def smoothing s=nil
          if s.present? and not @smoothing == s
            @smoothing = s
            case @smoothing
            when TrueClass
              @frontend.set_smoothing 8
            when FalseClass
              @frontend.set_smoothing 0
            when 0..8
              @frontend.set_smoothing @smoothing
            else
              raise ArgumentError, s
            end
          end
        end

        @smoothing
      end

      # Create a new Glfw frontend, and open a window with size +(width,height)+
      # 
      # @param width [Numeric] width of the window
      # @param height [Numeric] height of the window
      # 
      # @todo Solve initial window size problem
      def initialize width, height
        @pointer = Native.glfwfrontend_new
        Zajal::Graphics::Native.ofSetupOpenGL @pointer, width, height, 0 # TODO move this

        @mousePositionCallback = Proc.new { |x, y| @sketch.mouse_moved x, y if @sketch }
        Native.glfwSetMousePosCallback @mousePositionCallback

        @mouseButtonCallback = Proc.new { |button, action| action == Native::GLFW_RELEASE ? @sketch.mouse_up(button) : @sketch.mouse_down(button) if @sketch }
        Native.glfwSetMouseButtonCallback @mouseButtonCallback

        @keyButtonCallback = Proc.new { |button, action| action == Native::GLFW_RELEASE ? @sketch.key_up(button) : @sketch.key_down(button) if @sketch }
        Native.glfwSetKeyCallback @keyButtonCallback

        @fbo = Zajal::Graphics::Fbo.new width, height, 0
      end

      def set_smoothing s
        @fbo = Zajal::Graphics::Fbo.new @fbo.width, @fbo.height, s
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
        @sketch.frontend = self # hack
        @sketch.setup
        @fbo.use { @sketch.draw } if @sketch.bare

        while true do
          @fbo.use { @sketch.update; @sketch.draw } unless @sketch.bare
          @sketch.style do
            @sketch.color :white
            @fbo.draw 0, 0
          end

          Native.glfwSwapBuffers
          Native.glfwfrontend_incrementFrameNum @pointer

          # TODO this should be taken care of by Sketch
          if @sketch.stale?
            @sketch = @sketch.refresh_restart 
            @sketch.frontend = self # hack
            @sketch.setup
            @fbo.use { @sketch.draw } if @sketch.bare

            Native.glfwfrontend_setFrameNum @pointer, 0
          end
        end
      end

      module Native
        extend FFI::Cpp::Library

        GLFW_RELEASE          = 0
        GLFW_PRESS            = 1

        GLFW_KEY_UNKNOWN      = -1
        GLFW_KEY_SPACE        = 32
        GLFW_KEY_SPECIAL      = 256
        GLFW_KEY_ESC          = GLFW_KEY_SPECIAL + 1
        GLFW_KEY_F1           = GLFW_KEY_SPECIAL + 2
        GLFW_KEY_F2           = GLFW_KEY_SPECIAL + 3
        GLFW_KEY_F3           = GLFW_KEY_SPECIAL + 4
        GLFW_KEY_F4           = GLFW_KEY_SPECIAL + 5
        GLFW_KEY_F5           = GLFW_KEY_SPECIAL + 6
        GLFW_KEY_F6           = GLFW_KEY_SPECIAL + 7
        GLFW_KEY_F7           = GLFW_KEY_SPECIAL + 8
        GLFW_KEY_F8           = GLFW_KEY_SPECIAL + 9
        GLFW_KEY_F9           = GLFW_KEY_SPECIAL + 10
        GLFW_KEY_F10          = GLFW_KEY_SPECIAL + 11
        GLFW_KEY_F11          = GLFW_KEY_SPECIAL + 12
        GLFW_KEY_F12          = GLFW_KEY_SPECIAL + 13
        GLFW_KEY_F13          = GLFW_KEY_SPECIAL + 14
        GLFW_KEY_F14          = GLFW_KEY_SPECIAL + 15
        GLFW_KEY_F15          = GLFW_KEY_SPECIAL + 16
        GLFW_KEY_F16          = GLFW_KEY_SPECIAL + 17
        GLFW_KEY_F17          = GLFW_KEY_SPECIAL + 18
        GLFW_KEY_F18          = GLFW_KEY_SPECIAL + 19
        GLFW_KEY_F19          = GLFW_KEY_SPECIAL + 20
        GLFW_KEY_F20          = GLFW_KEY_SPECIAL + 21
        GLFW_KEY_F21          = GLFW_KEY_SPECIAL + 22
        GLFW_KEY_F22          = GLFW_KEY_SPECIAL + 23
        GLFW_KEY_F23          = GLFW_KEY_SPECIAL + 24
        GLFW_KEY_F24          = GLFW_KEY_SPECIAL + 25
        GLFW_KEY_F25          = GLFW_KEY_SPECIAL + 26
        GLFW_KEY_UP           = GLFW_KEY_SPECIAL + 27
        GLFW_KEY_DOWN         = GLFW_KEY_SPECIAL + 28
        GLFW_KEY_LEFT         = GLFW_KEY_SPECIAL + 29
        GLFW_KEY_RIGHT        = GLFW_KEY_SPECIAL + 30
        GLFW_KEY_LSHIFT       = GLFW_KEY_SPECIAL + 31
        GLFW_KEY_RSHIFT       = GLFW_KEY_SPECIAL + 32
        GLFW_KEY_LCTRL        = GLFW_KEY_SPECIAL + 33
        GLFW_KEY_RCTRL        = GLFW_KEY_SPECIAL + 34
        GLFW_KEY_LALT         = GLFW_KEY_SPECIAL + 35
        GLFW_KEY_RALT         = GLFW_KEY_SPECIAL + 36
        GLFW_KEY_TAB          = GLFW_KEY_SPECIAL + 37
        GLFW_KEY_ENTER        = GLFW_KEY_SPECIAL + 38
        GLFW_KEY_BACKSPACE    = GLFW_KEY_SPECIAL + 39
        GLFW_KEY_INSERT       = GLFW_KEY_SPECIAL + 40
        GLFW_KEY_DEL          = GLFW_KEY_SPECIAL + 41
        GLFW_KEY_PAGEUP       = GLFW_KEY_SPECIAL + 42
        GLFW_KEY_PAGEDOWN     = GLFW_KEY_SPECIAL + 43
        GLFW_KEY_HOME         = GLFW_KEY_SPECIAL + 44
        GLFW_KEY_END          = GLFW_KEY_SPECIAL + 45
        GLFW_KEY_KP_0         = GLFW_KEY_SPECIAL + 46
        GLFW_KEY_KP_1         = GLFW_KEY_SPECIAL + 47
        GLFW_KEY_KP_2         = GLFW_KEY_SPECIAL + 48
        GLFW_KEY_KP_3         = GLFW_KEY_SPECIAL + 49
        GLFW_KEY_KP_4         = GLFW_KEY_SPECIAL + 50
        GLFW_KEY_KP_5         = GLFW_KEY_SPECIAL + 51
        GLFW_KEY_KP_6         = GLFW_KEY_SPECIAL + 52
        GLFW_KEY_KP_7         = GLFW_KEY_SPECIAL + 53
        GLFW_KEY_KP_8         = GLFW_KEY_SPECIAL + 54
        GLFW_KEY_KP_9         = GLFW_KEY_SPECIAL + 55
        GLFW_KEY_KP_DIVIDE    = GLFW_KEY_SPECIAL + 56
        GLFW_KEY_KP_MULTIPLY  = GLFW_KEY_SPECIAL + 57
        GLFW_KEY_KP_SUBTRACT  = GLFW_KEY_SPECIAL + 58
        GLFW_KEY_KP_ADD       = GLFW_KEY_SPECIAL + 59
        GLFW_KEY_KP_DECIMAL   = GLFW_KEY_SPECIAL + 60
        GLFW_KEY_KP_EQUAL     = GLFW_KEY_SPECIAL + 61
        GLFW_KEY_KP_ENTER     = GLFW_KEY_SPECIAL + 62
        GLFW_KEY_KP_NUM_LOCK  = GLFW_KEY_SPECIAL + 63
        GLFW_KEY_CAPS_LOCK    = GLFW_KEY_SPECIAL + 64
        GLFW_KEY_SCROLL_LOCK  = GLFW_KEY_SPECIAL + 65
        GLFW_KEY_PAUSE        = GLFW_KEY_SPECIAL + 66
        GLFW_KEY_LSUPER       = GLFW_KEY_SPECIAL + 67
        GLFW_KEY_RSUPER       = GLFW_KEY_SPECIAL + 68
        GLFW_KEY_MENU         = GLFW_KEY_SPECIAL + 69

        GLFW_MOUSE_BUTTON_1   = 0
        GLFW_MOUSE_BUTTON_2   = 1
        GLFW_MOUSE_BUTTON_3   = 2
        GLFW_MOUSE_BUTTON_4   = 3
        GLFW_MOUSE_BUTTON_5   = 4
        GLFW_MOUSE_BUTTON_6   = 5
        GLFW_MOUSE_BUTTON_7   = 6
        GLFW_MOUSE_BUTTON_8   = 7

        ffi_lib File.expand_path("glfw/lib/libglfw.dylib", File.dirname(__FILE__))
        attach_function :glfwSwapBuffers, [], :void
        attach_function :glfwPollEvents, [], :void

        callback :GLFWkeyfun, [:int, :int], :void
        attach_function :glfwSetKeyCallback, [:GLFWkeyfun], :void

        callback :GLFWmousebuttonfun, [:int, :int], :void
        attach_function :glfwSetMouseButtonCallback, [:GLFWmousebuttonfun], :void

        callback :GLFWmouseposfun, [:int, :int], :void
        attach_function :glfwSetMousePosCallback, [:GLFWmouseposfun], :void

        attach_function :glfwSetWindowPos, [:int, :int], :void

        ffi_lib File.expand_path("glfw/lib/GlfwFrontend.so", File.dirname(__FILE__))
        attach_constructor :GlfwFrontend, 16, []
        attach_method :GlfwFrontend, :setWindowShape, [:int, :int], :void
        attach_method :GlfwFrontend, :incrementFrameNum, [], :void
        attach_method :GlfwFrontend, :setFrameNum, [:int], :void
      end
    end
  end
end