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
        options = { antialiased:true, full_character_set:false, contours:false, simplify:0.3, dpi:0 }.merge options

        @name = File.basename(file)
        
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

      def inspect
        "<#{@name} #{size}pt>"
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
    def text message, x=nil, y=nil
      @basic_font ||= Font.new File.join(File.dirname(__FILE__), "bin", "gohu.ttf"), 8, antialiased:false

      if x.present?
        x, y = x.to_f, y.to_f
      else
        @stacked_text_x ||= 1.0
        @stacked_text_y ||= 10.0
        
        x, y = @stacked_text_x, @stacked_text_y

        @stacked_text_y += 10.0
      end

      @basic_font.draw message.to_s, x, y
    end

    def self.included sketch
      sketch.before_event :draw do
        @stacked_text_x = 1.0
        @stacked_text_y = 10.0
      end
    end

    module Native
      extend FFI::Cpp::Library
      
      ffi_lib "lib/core/lib/libof.so"

      attach_constructor :ofTrueTypeFont, 344, []
      attach_method :ofTrueTypeFont, :drawString, [:stdstring, :float, :float], :void
      attach_method :ofTrueTypeFont, :loadFont, [:stdstring, :int, :bool, :bool, :bool, :float, :int], :void
      attach_method :ofTrueTypeFont, :getSize, [], :int
      attach_method :ofTrueTypeFont, :getLineHeight, [], :float
    end
  end
end