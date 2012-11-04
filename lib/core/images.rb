module Zajal
  # @api zajal
  module Images
    # An image
    # 
    # {Image} can represents an image file loaded off the disk and a drawing
    # surface.
    class Image
      # Create a new image object
      # 
      # @overload image
      # @overload image filename
      # @overload image width, height
      # 
      # @param filename [#to_s] name of the file to load
      # @param width [Numeric] width of the new image
      # @param width [Numeric] height of the new image
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
      # This will resize the image to {filename}'s size and load {filename}'s
      # pixels
      # 
      # @param filename [#to_s] name of the file to load
      # 
      # @return [nil] nothing
      def load filename
        Native.ofimage_loadImage @pointer, File.expand_path(filename.to_s).to_ptr
      end

      # Save the image to the disk
      # 
      # @param path [#to_s] location on disk to save file
      # @param quality [#to_s] location on disk to save file
      # 
      # @return [nil] nothing
      def save path, quality=:best
        Native.ofimage_saveImage @pointer, File.expand_path(path.to_s).to_ptr, quality
      end

      def grab_screen x, y, w, h
        Native.ofimage_grabScreen @pointer, x.to_i, y.to_i, w.to_i, h.to_i
      end

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
      # @overload draw x, y, size
      # @overload draw x, y, width, height
      # 
      # @param x [Numeric] distance from the left to start drawing
      # @param y [Numeric] distance from the top to start drawing
      # @param size [Numeric] proportional scale of the drawn image
      # @param width [Numeric] width of the drawn image
      # @param height [Numeric] height of the drawn image
      # 
      # @return [nil] nothing
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

      def rotate times=1
        Native.ofimage_rotate90 @pointer, times.to_i
      end

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
        ffi_lib "lib/core/lib/libof.so"

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
    # This is shorthand for the {Image} class. It creates an image object,
    # caches it for future use, and draws that image right away. If width and
    # height are not given, the 
    # 
    # @overload image file x, y
    # @overload image file x, y, width, height
    # 
    # @param file [#to_s] The image file to load
    # @param x [Numeric] the x coordinate to draw the image at
    # @param y [Numeric] the y coordinate to draw the image at
    # @param width [Numeric] the width to draw the image at
    # @param height [Numeric] the height to draw the image at
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
    end

    def grab_screen *args
      i = Image.new
      i.grab_screen *args
      i
    end
  end
end