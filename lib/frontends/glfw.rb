module Zajal
	module Frontends
		class Glfw
			attr_accessor :sketch

			def initialize w, h
				@window = Native.glfwfrontend_new
				@w, @h = w, h
				Zajal::Graphics::Native.ofSetupOpenGL @window, w, h, 0
			end

			def run
				sketch.setup
				while true do
					Zajal::Graphics::Native.ofSetupScreen
					sketch.update
					Zajal::Graphics::Native.ofClear 160.0, 37.0, 37.0, 255.0
					sketch.draw
					Native.glfwSwapBuffers
				end
			end

			module Native
				extend FFI::Cpp::Library
				ffi_lib "lib/frontends/glfw/lib/libglfw.dylib"
				attach_function :glfwSwapBuffers, [], :void

				ffi_lib "lib/frontends/glfw/lib/GlfwFrontend.so"
				attach_constructor :GlfwFrontend, 16, []
			end
		end
	end
end


