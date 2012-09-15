module Zajal
	module Graphics
		def alpha_blending(on)
			on ? Native.ofEnableAlphaBlending : Native.ofDisableAlphaBlending
		end

		def circle x, y, z_or_r, r=nil
			if r.nil?
				Native.ofCircle x.to_f, y.to_f, 0.0, z_or_r.to_f
			else
				Native.ofCircle x.to_f, y.to_f, z_or_r.to_f, r.to_f
			end
		end

		def rectangle x, y, w, h
			Native.ofRect x.to_f, y.to_f, w.to_f, h.to_f
		end

		def square x, y, s
			Native.ofRect x.to_f, y.to_f, s.to_f, s.to_f
		end

		def translate x, y, z=0.0
			Native.ofTranslate x.to_f, y.to_f, z.to_f
		end

		def text s, x, y
			Native.ofDrawBitmapString s, x, y
		end

		module Native
			extend FFI::Cpp::Library

			# TODO move me!
			ffi_lib "/System/Library/Frameworks/OpenGL.framework/Libraries/libGL.dylib"
			%w[PocoFoundation PocoNet PocoXML PocoUtil glew tess freeimage freetype].each do |libname|
				ffi_lib "lib/core/lib/#{libname}.so"
			end

			ffi_lib "lib/core/lib/libof.so"

			typedef :pointer, :ofAppBaseWindow

			attach_function :ofSetupOpenGL, [:ofAppBaseWindow, :int, :int, :int], :void
			attach_function :ofSetupScreen, [], :void
			attach_function :ofEnableAlphaBlending, [], :void
			attach_function :ofDisableAlphaBlending, [], :void
			attach_function :ofCircle, [:float, :float, :float, :float], :void
			attach_function :ofClear, [:float, :float, :float, :float], :void
			attach_function :ofRect, [:float, :float, :float, :float], :void
			attach_function :ofTranslate, [:float, :float, :float], :void
			attach_function :ofDrawBitmapCharacterStart, [:int], :void
			attach_function :ofDrawBitmapCharacterEnd, [], :void
			attach_function :ofDrawBitmapCharacter, [:int, :int, :int], :void
		end
	end
end