module Zajal
  # @api zajal
  module Images
    # Draw an image
    # 
    # This is shorthand for the {Image} class. It creates an image object,
    # caches it for future use, and draws that image right away. If width and
    # height are not given, the dimentions of the loaded image are used.
    # 
    # @overload image file, x, y
    #   @param [#to_s] file The image file to load
    #   @param [Numeric] x the x coordinate to draw the image at
    #   @param [Numeric] y the y coordinate to draw the image at
    # 
    #   @demo Drawing one image
    #     image "docs/actual_zajal.jpg", 10, 10
    #   @demo Drawing multiple images
    #     image "docs/actual_zajal.jpg", 0, 0
    #     image "docs/actual_zajal.jpg", 50, 50
    #     image "docs/actual_zajal.jpg", -50, 70
    #     image "docs/actual_zajal.jpg", 80, -40
    # 
    # @overload image file, x, y, width, height
    #   @param [#to_s] file The image file to load
    #   @param [Numeric] x the x coordinate to draw the image at
    #   @param [Numeric] y the y coordinate to draw the image at
    #   @param [Numeric] width the width to draw the image at
    #   @param [Numeric] height the height to draw the image at
    # 
    #   @demo Drawing one smaller image
    #     image "docs/actual_zajal.jpg", 20, 20, 25, 25
    #   @demo Drawing one larger image
    #     image "docs/actual_zajal.jpg", -150, -40, 250, 250
    #   @demo Drawing many smaller images
    #     4.times do |i|
    #       image "docs/actual_zajal.jpg", i * 25, 0, 25, 25 * (i+1)
    #     end
    # 
    # @note In reality, this function reads the first parameter as the file
    #   to load and passes the rest of the arguments as is to {Image#draw}
    def image *args
      @cached_images ||= {}

      file = args.shift
      @cached_images[file] ||= Image.new file
      @cached_images[file].draw *args
    end

    # @overload grab_screen x, y, width, height
    #   Take a screenshot of the sketch
    #   
    #   @param [Numeric] x
    #   @param [Numeric] y
    #   @param [Numeric] width
    #   @param [Numeric] height
    #   @example Taking a screenshot on mouse click
    #     draw do
    #       fill false
    #       circle 50 + sin(time) * 50, 50, 20
    #     end
    #     
    #     mouse_down do
    #       grab_screen.save "~/Desktop/moving-circle.png"
    #     end
    #   
    #   @return [Image] screenshot of the sketch
    def grab_screen *args
      i = Image.new
      i.grab_screen *args
      i
    end

    # An image
    # 
    # {Image} can represents an image file loaded off the disk and a drawing
    # surface.
    class Image
      # Create a new image object
      # 
      # @overload initialize
      # @overload initialize filename
      #   @param filename [#to_s] name of the file to load
      #   @demo Loading an image
      #     img = Image.new "docs/actual_zajal.jpg"
      #     img.draw 13, 13
      # 
      # @overload initialize width, height
      #   @param width [Numeric] width of the new image
      #   @param width [Numeric] height of the new image
      def initialize *args
        @pointer = Native.ofimage_new

        case args
        when Signature[]
        when Signature[:to_s]
          load args.first
        when Signature[:to_i, :to_i]
          resize *args
        else
          raise ArgumentError, args.inspect
        end
      end

      # Load an image off the disk
      # 
      # This will resize the image to `filename`'s size and load `filename`'s
      # pixels
      # 
      # @param filename [#to_s] name of the file to load
      # 
      # @todo fix cwd bug in ofImage::loadImage!!
      def load filename
        path = File.expand_path(filename.to_s)
        Native.ofimage_loadImage @pointer, path.to_ptr
      end

      # Save the image to the disk
      # 
      # @param path [#to_s] location on disk to save file
      # @param quality [Symbol] location on disk to save file
      def save path, quality=:best
        Native.ofimage_saveImage @pointer, File.expand_path(path.to_s).to_ptr, quality
      end

      # @overload grab_screen
      # @overload grab_screen x, y
      # @overload grab_screen x, y, width, height
      def grab_screen *args
        x, y = 0, 0
        w, h = Sketch.current.width, Sketch.current.height

        case args
        when Signature[:to_i, :to_i] # x, y
          x, y = *args
        when Signature[:to_i, :to_i, :to_i, :to_i] # x, y, w, h
          x, y, w, h = *args
        end

        raise "Requested screenshot bigger than sketch!" if x + w > Sketch.current.width or y + h > Sketch.current.height

        Native.ofimage_grabScreen @pointer, x.to_i, y.to_i, w.to_i, h.to_i
      end

      # Resize the image
      # 
      # @overload resize size
      #   @param [Numeric] size new width and height of the image
      # 
      #   @demo Resizing an image
      #     img = Image.new "docs/actual_zajal.jpg"
      #     img.resize 20
      #     img.draw 10, 10
      # 
      # @overload resize width, height
      #   @param [Numeric] width new width of the image
      #   @param [Numeric] height new height of the image
      # 
      #   @demo Resizing an image
      #     img = Image.new "docs/actual_zajal.jpg"
      #     img.resize 100, 50
      #     img.draw 0, 0
      def resize w, h=nil
        h = w unless h.present?
        Native.ofimage_resize @pointer, w.to_i, h.to_i
      end

      # @return [Float] current image width
      def width
        Native.ofimage_getWidth @pointer
      end

      # @return [Float] current image height
      def height
        Native.ofimage_getHeight @pointer
      end

      # Draw the image
      # 
      # @overload draw x, y
      #   @param x [Numeric] distance from the left to start drawing
      #   @param y [Numeric] distance from the top to start drawing
      # 
      # @overload draw x, y, size
      #   @param x [Numeric] distance from the left to start drawing
      #   @param y [Numeric] distance from the top to start drawing
      #   @param size [Numeric] proportional scale of the drawn image
      # 
      # @overload draw x, y, width, height
      #   @param x [Numeric] distance from the left to start drawing
      #   @param y [Numeric] distance from the top to start drawing
      #   @param width [Numeric] width of the drawn image
      #   @param height [Numeric] height of the drawn image
      def draw x, y, w=nil, h=nil
        if not w.present?
          w = width
          h = height
        elsif not h.present?
          w = width * w
          h = height * w
        end

        Native.ofimage_draw @pointer, x.to_f, y.to_f, 0.0, w.to_f, h.to_f
      end

      def crop x, y, w, h
        Native.ofimage_crop @pointer, x.to_i, y.to_i, w.to_i, h.to_i
      end

      # Rotate the image by 90 degrees
      # 
      # @overload rotate
      # @overload rotate times
      def rotate times=1
        Native.ofimage_rotate90 @pointer, times.to_i
      end

      # Mirror the image
      # 
      # @overload mirror
      # @overload mirror direction
      def mirror direction=:horizontal
        d = {
          horizontal: [false, true],
          vertical:[true, false],
          diagonal:[true, true]
        }[direction]
        raise ArgumentError unless d

        Native.ofimage_mirror @pointer, *d
      end

      # @api internal
      module Native
        extend FFI::Cpp::Library
        File.expand_path("lib/libof.so", File.dirname(__FILE__))

        ofImage = type(:ofImage_).template(:unsigned_char).actually(:ofImage)

        enum :ofImageQualityType, [ :best, :high, :medium, :low, :worst ]

        attach_constructor ofImage, 152, []
        attach_method ofImage, :draw, [:float, :float, :float, :float, :float], :void
        attach_method ofImage, :loadImage, [:stdstring], :bool
        attach_method ofImage, :saveImage, [:stdstring, :ofImageQualityType], :bool

        attach_method ofImage, :resize, [:int, :int], :void
        attach_method ofImage, :getHeight, [], :float
        attach_method ofImage, :getWidth, [], :float

        attach_method ofImage, :grabScreen, [:int, :int, :int, :int], :void
        attach_method ofImage, :crop, [:int, :int, :int, :int], :void
        attach_method ofImage, :rotate90, [:int], :void
        attach_method ofImage, :mirror, [:bool, :bool], :void
      end
    end

    # Draw an image
    # 
    # 
    # @overload image file x, y
    #   This is shorthand for the {Image} class. It creates an image object,
    #   caches it for future use, and draws that image right away. If width and
    #   height are not given, the 
    #   @param [#to_s] file The image file to load
    #   @param [Numeric] x the x coordinate to draw the image at
    #   @param [Numeric] y the y coordinate to draw the image at
    # 
    # @overload image file x, y, width, height
    #   @param [#to_s] file The image file to load
    #   @param [Numeric] x the x coordinate to draw the image at
    #   @param [Numeric] y the y coordinate to draw the image at
    #   @param [Numeric] width the width to draw the image at
    #   @param [Numeric] height the height to draw the image at
    # 
    # @return [nil] Nothing
    # 
    # @note In reality, this function reads the first parameter as the file
    #   to load and passes the rest of the arguments as is to {Image#draw}
    def image *args
      @cached_images ||= {}

      file = args.shift
      @cached_images[file] ||= Image.new file
      @cached_images[file].draw *args

      @cached_images[file]
    end

    # @overload grab_screen
    # @overload grab_screen x, y
    # @overload grab_screen x, y, width, height
    def grab_screen *args
      img = Image.new
      img.grab_screen *args

      img
    end
  end
end