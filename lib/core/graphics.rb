module Zajal
  # This module contains methods that draw basic geometric primitives.
  # Methods either draw directly to the screen (e.g. {#circle},
  # {#square}) or affect subsequent drawing (e.g. {#translate}).
  # 
  # {Zajal::Graphics} mostly a wrapper for ofGraphics in openFrameworks.
  # 
  # @see http://www.openframeworks.cc/documentation/graphics/ofGraphics.html
  module Graphics
    # Draw a circle
    # 
    # @example Single circle
    #   circle 50, 50, 25
    # 
    # @example Four circles
    #   circle 25, 25, 20
    #   circle 75, 25, 20
    #   circle 75, 75, 20
    #   circle 25, 75, 20
    # 
    # @overload circle x, y, radius
    # @overload circle x, y, z, radius
    # 
    # @param x [Numeric] x coordinate of circle's center
    # @param y [Numeric] y coordinate of circle's center
    # @param z [Numeric] z coordinate of circle's center
    # @param radius [Numeric] radius of the circle
    # 
    # @return [nil] Nothing
    def circle x, y, z_or_radius, radius=nil
      if radius.nil?
        Native.ofCircle x.to_f, y.to_f, 0.0, z_or_radius.to_f
      else
        Native.ofCircle x.to_f, y.to_f, z_or_radius.to_f, r.to_f
      end
    end

    # Enable or disable alpha blending
    # 
    # Alpha blending allows for transparent colors in colors and images, but can
    # slow down your sketch. You can enable and disable it as needed.
    # 
    # @param on [Boolean], +true+ to enable alpha blending, +false+ to disable
    # 
    # @return [Boolean] the new alpha blending value
    def alpha_blending on
      on ? Native.ofEnableAlphaBlending : Native.ofDisableAlphaBlending
    end

    # Set the background color and clear the screen to that color 
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # @param a [Numeric] the amount of alpha, 0..255
    # 
    # @return [nil] Nothing
    def background r, g, b, a=255
      Native.ofClear r.to_f, g.to_f, b.to_f, a.to_f
    end

    # Draw a rectangle
    # 
    # @example Single thin rectangle
    #   rectangle 45, 10, 10, 80
    # 
    # @example Single wide rectangle
    #   rectangle 25, 10, 50, 80
    # 
    # @example Carefully placed rectangles
    #   rectangle 10, 10, 1, 80
    #   rectangle 12, 10, 2, 80
    #   rectangle 15, 10, 3, 80
    #   rectangle 19, 10, 4, 80
    #   rectangle 24, 10, 5, 80
    #   rectangle 30, 10, 6, 80
    #   rectangle 37, 10, 7, 80
    #   rectangle 45, 10, 8, 80
    #   rectangle 54, 10, 9, 80
    #   rectangle 64, 10, 10, 80
    #   rectangle 75, 10, 11, 80
    # 
    # @param x [Numeric] x coordinate of top left corner
    # @param y [Numeric] y coordinate of top left corner
    # @param width [Numeric] width of rectangle
    # @param height [Numeric] height of rectangle
    # 
    # @return [nil] Nothing
    # 
    # @see #square
    def rectangle x, y, width, height
      Native.ofRect x.to_f, y.to_f, width.to_f, height.to_f
    end

    # Draw a line between two points
    # 
    # #param x1 [Numeric] the x coordinate of the first point 
    # #param y1 [Numeric] the y coordinate of the first point 
    # #param x2 [Numeric] the x coordinate of the second point 
    # #param y2 [Numeric] the y coordinate of the second point 
    # 
    # @return [nil] Nothing
    def line x1, y1, x2, y2
      Native.ofLine x1.to_f, y1.to_f, x2.to_f, y2.to_f
    end

    # Set the width of subsequent lines
    # 
    # @param width [Numeric] the width of the lines
    # 
    # @return [nil] Nothing
    def line_width width
      Native.ofSetLineWidth width.to_f
    end

    # Draw a square
    # 
    # @example Single square
    #   square 10, 10, 80
    #
    # @example Corner to corner
    #   square 10, 10, 10
    #   square 20, 20, 20
    #   square 40, 40, 40
    # 
    # @example Carefully placed squares
    #   square 10, 50, 1
    #   square 12, 50, 2
    #   square 15, 50, 3
    #   square 19, 50, 4
    #   square 24, 50, 5
    #   square 30, 50, 6
    #   square 37, 50, 7
    #   square 45, 50, 8
    #   square 54, 50, 9
    #   square 64, 50, 10
    #   square 75, 50, 11
    # 
    # @param x [Numeric] x coordinate of the top left corner
    # @param y [Numeric] y coordinate of the top left corner
    # @param size [Numeric] the width and height of the square
    # 
    # @return [nil] Nothing
    # 
    # @see #rectangle
    def square x, y, size
      Native.ofRect x.to_f, y.to_f, size.to_f, size.to_f
    end

    # Move all subsequent drawing
    # 
    # @example Same circle shifted
    #   circle 20, 50, 10
    #   translate 60, 0
    #   circle 20, 50, 10
    # 
    # @param x [Numeric] amount to move horizontally
    # @param y [Numeric] amount to move vertically
    # @param z [Numeric] amount to move in depth
    # 
    # @return [nil] Nothing
    def translate x, y, z=0.0
      Native.ofTranslate x.to_f, y.to_f, z.to_f
    end

    # Set the color that subsequent drawing will be done in
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # @param a [Numeric] the amount of alpha, 0..255
    # 
    # @return [nil] Nothing
    def color r, g, b, a=255
      Native.ofSetColor r.to_i, g.to_i, b.to_i, a.to_i
    end

    # Clear the canvas to a color
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # @param a [Numeric] the amount of alpha, 0..255
    # 
    # @return [nil] Nothing
    def clear r, g, b, a=255.0
      Native.ofClear r.to_f, g.to_f, b.to_f, a.to_f
    end

    # @api internal
    def self.included sketch
      sketch.before_event :draw do
        Native.ofSetupScreen
        clear 160, 37, 37
      end
    end

    # FFI hooks to compiled openFrameworks functionality.
    # 
    # The methods in here do the actual work by invoking compiled C++
    # functions in +libof.so+.
    module Native
      extend FFI::Cpp::Library
      ffi_lib "lib/core/lib/libof.so"

      typedef :pointer, :ofAppBaseWindow

      attach_function :ofSetupOpenGL, [:ofAppBaseWindow, :int, :int, :int], :void
      attach_function :ofSetupScreen, [], :void
      attach_function :ofEnableAlphaBlending, [], :void
      attach_function :ofDisableAlphaBlending, [], :void
      attach_function :ofCircle, [:float, :float, :float, :float], :void
      attach_function :ofClear, [:float, :float, :float, :float], :void
      attach_function :ofLine, [:float, :float, :float, :float], :void
      attach_function :ofRect, [:float, :float, :float, :float], :void
      attach_function :ofSetLineWidth, [:float], :void
      attach_function :ofTranslate, [:float, :float, :float], :void
      attach_function :ofSetColor, [:int, :int, :int, :int], :void
    end
  end
end