module Zajal
  # {Zajal::Typography::Font} mostly a wrapper for ofTrueTypeFont in openFrameworks.
  # 
  # @see http://www.openframeworks.cc/documentation/graphics/ofTrueTypeFont.html
  module Typography
    # A font
    class Font
      # @param file [#to_s] the file to load
      # @param size [Numeric] the size of the font
      # @param options [Hash] additional options
      # @option options [Boolean] :antialiased Smooth font edges?
      # @option options [Boolean] :full_character_set Load all glyphs?
      # @option options [Boolean] :full_character_set Prepare font for vector rendering?
      # @option options [Float] :simplify
      # @option options [Fixnum] :dpi
      def initialize file, size, options={}
        options.merge({ antialiased:true, full_character_set:false, contours:false, simplify:0.3, dpi:0 })
        
        @pointer = Native.oftruetypefont_new
        Native.oftruetypefont_loadFont @pointer, File.expand_path(file).to_s.to_ptr, size.to_i, options[:antialiased], options[:full_character_set], options[:contours], options[:simplify].to_f, options[:dpi].to_i
      end

      # Draw text using this font's glyphs
      # 
      # @param text [#to_s] the text to draw
      # @param x [Numeric] x coordinate of to start drawing text at
      # @param y [Numeric] y coordinate of to start drawing text at
      # 
      # @return [nil] Nothing
      def draw text, x, y
        Native.oftruetypefont_drawString @pointer, text.to_s.to_ptr, x.to_f, y.to_f
      end

      def size
        Native.oftruetypefont_getSize @pointer
      end

      def line_height
        Native.oftruetypefont_getLineHeight @pointer
      end

      # @api internal
      def to_ptr
        @pointer
      end
    end

    # Draw text
    # 
    # @param message [#to_s] the text to write
    # @param x [Numeric] the x coordinate to start writing text at
    # @param y [Numeric] the y coordinate to start writing text at
    # 
    # @return [nil] Nothing
    # 
    # @todo Use the same font rendering path as {Font}, not
    #   ofDrawBitmapString. Ship Zajal with a monospace font and use that.
    def text message, x, y
      Native.ofDrawBitmapString message.to_s.to_ptr, x.to_f, y.to_f
    end

    module Native
      extend FFI::Cpp::Library
      
      ffi_lib "lib/core/lib/libof.so"

      attach_constructor :ofTrueTypeFont, 344, []
      attach_method :ofTrueTypeFont, :drawString, [:stdstring, :float, :float], :void
      attach_method :ofTrueTypeFont, :loadFont, [:stdstring, :int, :bool, :bool, :bool, :float, :int], :void
      attach_method :ofTrueTypeFont, :getSize, [], :int
      attach_method :ofTrueTypeFont, :getLineHeight, [], :float

      attach_function :ofDrawBitmapString, [:stdstring, :float, :float], :void
    end
  end
end