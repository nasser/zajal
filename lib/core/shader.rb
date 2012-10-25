module Zajal
  module Graphics
    class Shader
      def initialize vertex, fragment
        @pointer = Native.ofshader_new
        Native.ofshader_setupShaderFromSource @pointer, Native::Vertex, vertex.to_s.to_ptr
        Native.ofshader_setupShaderFromSource @pointer, Native::Fragment, fragment.to_s.to_ptr
        Native.ofshader_linkProgram @pointer
      end

      def begin
        Native.ofshader_begin @pointer
      end

      def end
        Native.ofshader_end @pointer
      end

      def use
        self.begin
        yield
        self.end
      end

      def uniform name, *args
        if args.count == 1 and args.first.respond_to? :texture
            Native.ofshader_setUniformTexture @pointer, name.to_s, args.first.texture, 10
        else
            raise "uniform must have 1-4 arguments, given #{args.count}!" if args.count == 0 || args.count > 4
            raise "uniform arguments must all be integers or floats!" unless args.all? { |a| a.is_a? Fixnum } or args.all? { |a| a.is_a? Float }

            method = "ofshader_setUniform#{args.count}#{args.first.is_a?(Fixnum) ? 'i' : 'f'}"
            Native.send method.to_sym, @pointer, name.to_s, *args
        end
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/core/lib/libof.so"

        typedef :pointer, :ofTexture

        Fragment = 0x8B30
        Vertex = 0x8B31
        Geometry = 0x8DD9

        attach_constructor :ofShader, 64, []

        attach_method :ofShader, :load, [:stdstring, :stdstring, :stdstring], :bool

        # these are essential to call before linking the program with geometry shaders
        # attach_method :ofShader, :setGeometryInputType, [GLenum type] # type: GL_POINTS, GL_LINES, GL_LINES_ADJACENCY_EXT, GL_TRIANGLES, GL_TRIANGLES_ADJACENCY_E], :void
        # attach_method :ofShader, :setGeometryOutputType, [GLenum type] # type: GL_POINTS, GL_LINE_STRIP or GL_TRIANGLE_STR], :void
        # attach_method :ofShader, :setGeometryOutputCount, [:int] # set number of output vertic], :void

        attach_method :ofShader, :getGeometryMaxOutputCount, [], :int # returns maximum number of supported vertices
        attach_method :ofShader, :unload, [], :void

        attach_method :ofShader, :begin, [], :void
        attach_method :ofShader, :end, [], :void

        # set a texture reference
        attach_method :ofShader, :setUniformTexture, [:string, type(:ofTexture).reference, :int], :void

        # set a single uniform value
        attach_method :ofShader, :setUniform1i, [:string, :int], :void
        attach_method :ofShader, :setUniform2i, [:string, :int, :int], :void
        attach_method :ofShader, :setUniform3i, [:string, :int, :int, :int], :void
        attach_method :ofShader, :setUniform4i, [:string, :int, :int, :int, :int], :void

        attach_method :ofShader, :setUniform1f, [:string, :float], :void
        attach_method :ofShader, :setUniform2f, [:string, :float, :float], :void
        attach_method :ofShader, :setUniform3f, [:string, :float, :float, :float], :void
        attach_method :ofShader, :setUniform4f, [:string, :float, :float, :float, :float], :void

        # set an array of uniform values
        # attach_method :ofShader, :setUniform1iv, [:string, :int v, :int = 1], :void
        # attach_method :ofShader, :setUniform2iv, [:string, :int v, :int = 1], :void
        # attach_method :ofShader, :setUniform3iv, [:string, :int v, :int = 1], :void
        # attach_method :ofShader, :setUniform4iv, [:string, :int v, :int = 1], :void

        # attach_method :ofShader, :setUniform1fv, [:string, :float v, :int = 1], :void
        # attach_method :ofShader, :setUniform2fv, [:string, :float v, :int = 1], :void
        # attach_method :ofShader, :setUniform3fv, [:string, :float v, :int = 1], :void
        # attach_method :ofShader, :setUniform4fv, [:string, :float v, :int = 1], :void

        # attach_method :ofShader, :setUniformMatrix4f, [:string, const ofMatrix4x4 & m], :void

        # set attributes that vary per vertex (look up the location before glBegin)
        attach_method :ofShader, :getAttributeLocation, [:string], :int

        attach_method :ofShader, :setAttribute1s, [:int, :short], :void
        attach_method :ofShader, :setAttribute2s, [:int, :short, :short], :void
        attach_method :ofShader, :setAttribute3s, [:int, :short, :short, :short], :void
        attach_method :ofShader, :setAttribute4s, [:int, :short, :short, :short, :short], :void

        attach_method :ofShader, :setAttribute1f, [:int, :float], :void
        attach_method :ofShader, :setAttribute2f, [:int, :float, :float], :void
        attach_method :ofShader, :setAttribute3f, [:int, :float, :float, :float], :void
        attach_method :ofShader, :setAttribute4f, [:int, :float, :float, :float, :float], :void

        attach_method :ofShader, :setAttribute1d, [:int, :double], :void
        attach_method :ofShader, :setAttribute2d, [:int, :double, :double], :void
        attach_method :ofShader, :setAttribute3d, [:int, :double, :double, :double], :void
        attach_method :ofShader, :setAttribute4d, [:int, :double, :double, :double, :double], :void

        attach_method :ofShader, :printActiveUniforms, [], :void
        attach_method :ofShader, :printActiveAttributes, [], :void

        # advanced use
        # these methods create and compile a shader from source or file
        # type: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER_EXT etc.
        attach_method :ofShader, :setupShaderFromSource, [:uint, :stdstring], :bool
        attach_method :ofShader, :setupShaderFromFile, [:uint, :stdstring], :bool

        # links program with all compiled shaders
        attach_method :ofShader, :linkProgram, [], :bool
      end
    end
  end
end
