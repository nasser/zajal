module Zajal
  # {Zajal::Typography::Font} mostly a wrapper for ofTrueTypeFont in openFrameworks.
  # 
  # @see http://www.openframeworks.cc/documentation/graphics/ofTrueTypeFont.html
  # @api zajal
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

        files = file.is_a?(Array) ? file : [file]

        files.map! do |f|
          if File.exists? File.expand_path(f.to_s)
            f
          else
            [ "/Library/Fonts/#{f}", "/Library/Fonts/#{f}.ttf", "/Library/Fonts/#{f}.otf",
              "/System/Library/Fonts/#{f}", "/System/Library/Fonts/#{f}.ttf", "/System/Library/Fonts/#{f}.otf",
              "~/Library/Fonts/#{f}", "~/Library/Fonts/#{f}.ttf", "~/Library/Fonts/#{f}.otf" ]
          end
        end

        files.flatten.each do |f|
          f = File.expand_path(f.to_s)
          next unless File.exists? f

          @name = File.basename(f)
          @pointer = Native.oftruetypefont_new
          Native.oftruetypefont_loadFont @pointer, f.to_s.to_ptr, size.to_i, options[:antialiased].to_bool, options[:full_character_set].to_bool, options[:contours].to_bool, options[:simplify].to_f, options[:dpi].to_i
          break
        end

        raise "Font not found!" unless @pointer
      end

      # Draw text using this font's glyphs
      # @demo
      #   fnt = Font.new 'Georgia', 16
      #   fnt.draw "Nice serifs!", 10, 60
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

    # Render text using Zajal's built in font.
    # 
    # @overload text message
    #   Draw `message` in top left corner. Calling this method multiple times will
    #   stack the text, making {#text} useful for quick debugging.
    #   @demo
    #     text "Hello, world!"
    #   @demo
    #     text "Hello, world!"
    #     text "This text..."
    #     text "...can stack!"
    #   @param message [#to_s] the text to write
    # 
    # @overload text message, x, y
    #   Draw `message` at a specific location on screen. The first letter will be placed
    #   at `x`,`y` and the text will continue to the left.
    #   @demo
    #     text "Hello, world!", 10, 50
    #   @param message [#to_s] the text to write
    #   @param x [Numeric] the x coordinate to start writing text at
    #   @param y [Numeric] the y coordinate to start writing text at
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

    # @api internal
    def self.included sketch
      sketch.before_event :draw do
        @stacked_text_x = 1.0
        @stacked_text_y = 10.0
      end
    end

    # @api internal
    module Native
      extend FFI::Cpp::Library
      
      File.expand_path("lib/libof.so", File.dirname(__FILE__))

      attach_constructor :ofTrueTypeFont, 344, []
      attach_method :ofTrueTypeFont, :drawString, [:stdstring, :float, :float], :void
      attach_method :ofTrueTypeFont, :loadFont, [:stdstring, :int, :bool, :bool, :bool, :float, :int], :void
      attach_method :ofTrueTypeFont, :getSize, [], :int
      attach_method :ofTrueTypeFont, :getLineHeight, [], :float
    end
  end
end