module Zajal
  module Images
    class Image
      def initialize file
        @pointer = Native.ofimage_new
        load file
      end

      def load file
        Native.ofimage_loadImage @pointer, File.expand_path(file.to_s).to_ptr
      end

      def save path, quality=:best
        Native.ofimage_loadImage @pointer, File.expand_path(path.to_s).to_ptr, quality
      end

      def grab_screen x, y, w, h
        Native.ofimage_grabScreen @pointer, x.to_i, y.to_i, w.to_i, h.to_i
      end

      def width
        Native.ofimage_getWidth @pointer
      end

      def height
        Native.ofimage_getHeight @pointer
      end

      def draw x, y
        Native.ofimage_draw @pointer, x.to_f, y.to_f, 0.0, width, height
      end

      module Native
        extend FFI::Cpp::Library
        ffi_lib "lib/core/lib/libof.so"

        ofImage = type(:ofImage_).template(:unsigned_char).actually(:ofImage)

        enum :ofImageQualityType, [ :best, :high, :medium, :low, :worst ]

        attach_constructor ofImage, 152, []
        attach_method ofImage, :draw, [:float, :float, :float, :float, :float], :void
        attach_method ofImage, :loadImage, [:stdstring], :bool
        attach_method ofImage, :saveImage, [:stdstring, :ofImageQualityType], :bool

        attach_method ofImage, :getHeight, [], :float
        attach_method ofImage, :getWidth, [], :float

        attach_method ofImage, :grabScreen, [:int, :int, :int, :int], :void
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
    # @note In reality, this function reads the first parameter as the file
    #   to load and passes the rest of the arguments as is to {Image#draw}
    def image *args
      @cached_images ||= {}

      file = args.shift
      @cached_images[file] ||= Image.new file
      @cached_images[file].draw *args
    end
  end
end