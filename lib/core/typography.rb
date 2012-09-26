module Zajal
  # {Zajal::Typography::Font} mostly a wrapper for ofTrueTypeFont in openFrameworks.
  # 
  # @see http://www.openframeworks.cc/documentation/graphics/ofTrueTypeFont.html
  module Typography
    # A font
    class Font
      # @param file [#to_s] the file to load
      # @param size [Numeric] the size of the font
      # 
      # @todo Expose additional options that ofTrueTypeFont supports (e.g.
      #   antialiased, full character sets, contours)
      def initialize file, size
        @pointer = Native.oftruetypefont_new
        Native.oftruetypefont_loadFont @pointer, file.to_s.to_ptr, size.to_i, true, false, false, 0.3, 0
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

      attach_function :ofDrawBitmapString, [:stdstring, :float, :float], :void
    end
  end
end