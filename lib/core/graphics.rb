module Zajal
  # This module contains methods that draw basic geometric primitives.
  # Methods either draw directly to the screen (e.g. {#circle},
  # {#square}) or affect subsequent drawing (e.g. {#translate}).
  # 
  # {Zajal::Graphics} mostly a wrapper for ofGraphics in openFrameworks.
  # 
  # @see http://www.openframeworks.cc/documentation/graphics/ofGraphics.html
  # 
  # @api zajal
  module Graphics

    # Draw a circle
    # 
    # @screenshot Single circle
    #   circle 50, 50, 25
    # 
    # @screenshot Four circles
    #   circle 25, 25, 20
    #   circle 75, 25, 20
    #   circle 75, 75, 20
    #   circle 25, 75, 20
    # 
    # @screenshot Point object
    #   p = OpenStruct.new
    #   p.x = 80
    #   p.y = 20
    # 
    #   circle p, 10
    # 
    # @syntax circle x, y, radius
    # @syntax circle x, y, z, radius
    # @syntax circle point, radius
    # 
    # @param x [Numeric] x coordinate of circle's center
    # @param y [Numeric] y coordinate of circle's center
    # @param z [Numeric] z coordinate of circle's center
    # @param radius [Numeric] radius of the circle
    # @param point [#x,#y] the circle's center
    # 
    # @see #circle_resolution
    def circle *args
      x = y = z = r = 0

      case args
      when Signature[[:x, :y], :to_f]
        x, y = args.first.x, args.first.y
        r = args.last

      when Signature[[:x, :y, :z], :to_f]
        x, y, z = args.first.x, args.first.y, args.first.z
        r = args.last

      when Signature[:to_f, :to_f, :to_f]
        x, y, r = *args

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, z, r = *args
      end

      Native.ofCircle x.to_f, y.to_f, z.to_f, r.to_f
    end

    # Enable or disable alpha blending
    # 
    # Alpha blending allows for transparent colors in colors and images, but can
    # slow down your sketch. You can enable and disable it as needed.
    # 
    # @screenshot With and without blending
    #   alpha_blending false
    #   color :white, 128
    #   circle 40, 25, 20
    #   circle 60, 25, 20
    #   
    #   alpha_blending true
    #   color :white, 128
    #   circle 40, 75, 20
    #   circle 60, 75, 20
    # 
    # @syntax alpha_blending -> blending
    # @syntax alpha_blending on
    # 
    # @param on [Boolean] true to enable alpha blending, false to disable
    # @return blending [Boolean] the new alpha blending value
    def alpha_blending on=nil
      @alpha_blending ||= false

      if on.present?
        @alpha_blending = on.to_bool
        @alpha_blending ? Native.ofEnableAlphaBlending : Native.ofDisableAlphaBlending
      end
      
      @alpha_blending
    end

    # Set the background color and clear the screen to that color 
    # 
    # @screenshot Blue background
    #   background :blue
    #   circle 50, 50, 30
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # @param a [Numeric] the amount of alpha, 0..255
    # 
    # @return [nil] Nothing
    def background *args
      unless args.empty?
        @background = Color.new(color_mode, *args)
        r, g, b, a = @background.to_rgb.to_a
        Native.ofClear r.to_f, g.to_f, b.to_f, a.to_f
      end

      @background
    end

    # Draw a rectangle
    # 
    # @screenshot Single thin rectangle
    #   rectangle 45, 10, 10, 80
    # 
    # @screenshot Single wide rectangle
    #   rectangle 25, 10, 50, 80
    # 
    # @screenshot Carefully placed rectangles
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
    def rectangle *args
      x, y, z, w, h = 0

      case args
      when Signature[[:x,:y], [:width,:height]]
        corner, dim = *args
        x, y = corner.x, corner.y
        z = corner.z if corner.respond_to? :z
        w, h = dim.width, dim.height

      when Signature[[:x,:y], :to_f, :to_f]
        corner, w, h = *args
        x, y = corner.x, corner.y
        z = corner.z if corner.respond_to? :z

      when Signature[:to_f, :to_f, [:width, :height]]
        x, y, dim = *args
        w, h = dim.width, dim.height

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, w, h = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f]
        x, y, z, w, h = *args
      end

      Native.ofRect x.to_f, y.to_f, z.to_f, w.to_f, h.to_f
    end

    # Draw a line between two points
    # 
    # @screenshot Single line
    #   line 10, 10, 90, 90
    # 
    # @screenshot Multiple lines
    #   line 10, 0, 90, 80
    #   line 10, 10, 90, 90
    #   line 10, 20, 90, 100
    # 
    # @screenshot Mesh
    #   10.times do |i|
    #     line i*10, 100, 100, 100-i*10
    #   end
    # 
    # @screenshot Point objects
    #   a = OpenStruct.new
    #   b = OpenStruct.new
    # 
    #   a.x = 10
    #   a.y = 20
    #   b.x = 90
    #   b.y = 70
    # 
    #   line a, b
    # 
    # @param x1 [Numeric] the x coordinate of the first point 
    # @param y1 [Numeric] the y coordinate of the first point 
    # @param x2 [Numeric] the x coordinate of the second point 
    # @param y2 [Numeric] the y coordinate of the second point 
    # 
    # @return [nil] Nothing
    def line *args
      x1 = y1 = z1 = x2 = y2 = z2 = 0

      case args
      when Signature[[:x,:y] ,[:x,:y]]
        x1, y1 = args.first.x, args.first.y
        x2, y2 = args.last.x, args.last.y

      when Signature[[:x,:y,:z] ,[:x,:y,:z]]
        x1, y1, z1 = args.first.x, args.first.y, args.first.z
        x2, y2, z2 = args.last.x, args.last.y, args.last.z

      when Signature[:to_f ,:to_f ,:to_f ,:to_f]
        x1, y1, x2, y2 = *args

      when Signature[:to_f ,:to_f ,:to_f ,:to_f ,:to_f ,:to_f]
        x1, y1, z1, x2, y2, z2 = *args
      end

      Native.ofLine x1.to_f, y1.to_f, z1.to_f, x2.to_f, y2.to_f, z2.to_f
    end

    # Set the width of subsequent lines
    # 
    # @screenshot Two lines
    #   line_width 1
    #   line 10, 5, 90, 85
    # 
    #   line_width 5
    #   line 10, 15, 90, 95
    # 
    # @screenshot Thicker lines
    #   line_width 1
    #   line 0, 10, 100, 10
    # 
    #   line_width 2
    #   line 0, 20, 100, 20
    # 
    #   line_width 3
    #   line 0, 30, 100, 30
    # 
    #   line_width 4
    #   line 0, 40, 100, 40
    # 
    #   line_width 5
    #   line 0, 50, 100, 50
    # 
    #   line_width 6
    #   line 0, 60, 100, 60
    # 
    #   line_width 7
    #   line 0, 70, 100, 70
    # 
    #   line_width 8
    #   line 0, 80, 100, 80
    # 
    #   line_width 9
    #   line 0, 90, 100, 90
    # 
    # @overload line_width
    #   @return [Numeric] the current line width
    # 
    # @overload line_width new_width
    #   @param new_width [Numeric] the width of the lines
    #   @return [nil] Nothing
    def line_width new_width=nil
      @line_width ||= 1

      if new_width.present?
        @line_width = new_width.to_f
        Native.ofSetLineWidth @line_width
      else
        @line_width
      end
    end

    # Draw a square
    # 
    # @overload square x, y, size
    # 
    # @screenshot Single square
    #   square 10, 10, 80
    #
    # @screenshot Corner to corner
    #   square 10, 10, 10
    #   square 20, 20, 20
    #   square 40, 40, 40
    # 
    # @screenshot Carefully placed squares
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
    def square *args
      x = y = z = s = 0

      case args
      when Signature[[:x,:y,:z], :to_f]
        pos, s = *args
        x, y, z = pos.x, pos.y, pos.z

      when Signature[[:x,:y], :to_f]
        pos, s = *args
        x, y = pos.x, pos.y

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, z, s = *args

      when Signature[:to_f, :to_f, :to_f]
        x, y, s = *args
      end

      rectangle x, y, z, s, s
    end

    # Move all subsequent drawing
    # 
    # @screenshot Same circle shifted
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

    # Scale all subsequent drawing
    # 
    # Scaling is centered at the top left corner
    # 
    # @screenshot Same circle scaled
    #   fill false
    # 
    #   scale 1
    #   circle 10, 10, 10
    # 
    #   scale 1.5
    #   circle 10, 10, 10
    # 
    #   scale 2
    #   circle 10, 10, 10
    # 
    #   scale 2.5
    #   circle 10, 10, 10
    # 
    #   scale 3
    #   circle 10, 10, 10
    # 
    # @syntax scale s
    # @syntax scale x, y
    # @syntax scale x, y, z
    # 
    # @param s [Numeric] amount to scale in all directions
    # @param x [Numeric] amount to scale in x
    # @param y [Numeric] amount to scale in y
    # @param z [Numeric] amount to scale in z
    def scale x, y=nil, z=1.0
      y = x unless y.present?
      Native.ofScale x.to_f, y.to_f, z.to_f
    end

    # Rotate all subsequent drawing
    # 
    # Rotating is centered at the top left corner
    # 
    # @screenshot Same square rotated
    #   fill false
    #   rotate 0
    #   square 50, 10, 20
    # 
    #   rotate 5
    #   square 50, 10, 20
    # 
    #   rotate 10
    #   square 50, 10, 20
    # 
    #   rotate 15
    #   square 50, 10, 20
    # 
    #   rotate 20
    #   square 50, 10, 20
    # 
    #   rotate 25
    #   square 50, 10, 20
    def rotate *args
      degrees = x = y = z = 0

      case args
      when Signature[:to_f]
        degrees = args.first
        z = 1

      when Signature[:to_f, [:x,:y,:z]]
        degrees, v = *args
        x, y, z = v.x, v.y, v.z

      when Signature[:to_f, [:x,:y]]
        degrees, v = *args
        x, y = v.x, v.y

      when Signature[:to_f, :to_f, :to_f, :to_f]
        degrees, x, y, z = *args
      end

      Native.ofRotate degrees.to_f, x.to_f, y.to_f, z.to_f
    end

    # Set the color that subsequent drawing will be done in
    # 
    # @screenshot Named colors
    #   color :yellow
    #   circle 20, 50, 15
    #   color :lime_green
    #   circle 80, 50, 15
    # 
    # @screenshot RGB colors
    #   color_mode :rgb
    #   color 200, 128, 64
    #   circle 20, 50, 15
    # 
    #   color 30, 128, 200
    #   circle 80, 50, 15
    # 
    # @screenshot HSV colors
    #   color_mode :hsv
    #   background :white
    # 
    #   color 0, 200, 200
    #   circle 20, 50, 15
    # 
    #   color 200, 200, 200
    #   circle 80, 50, 15
    # 
    # @screenshot Splatter
    #   translate width/2, height/2
    #   
    #   color_mode :hsv
    #   clear :black
    #   
    #   128.times do |i|
    #     color i*2, 255, 255
    #     line 0, 0, cos(i/128.0 * PI)*50, sin(i)*50
    #   end
    # 
    # @screenshot Esotetic colors
    #   color :light_goldenrod_yellow
    #   circle 20, 20, 15
    # 
    #   color :medium_aquamarine
    #   circle 80, 20, 15
    # 
    #   color :cornflower_blue
    #   circle 20, 80, 15
    # 
    #   color :light_slate_gray
    #   circle 80, 80, 15
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # @param a [Numeric] the amount of alpha, 0..255
    # 
    # @return [nil] Nothing
    def color *args
      unless args.empty?
        @color = Color.new(color_mode, *args)
        r, g, b, a = @color.to_rgb.to_a
        Native.ofSetColor r.to_i, g.to_i, b.to_i, a.to_i
      end

      @color
    end

    # Set the way subsequent colors will be interpreted
    # 
    # @screenshot Splatter
    #   translate width/2, height/2
    #   
    #   color_mode :hsv
    #   clear :black
    #   
    #   128.times do |i|
    #     color i*2, 255, 255
    #     line 0, 0, cos(i/128.0 * PI)*50, sin(i)*50
    #   end
    # 
    # You can set the color mode to anything defined as a subclass of Color, including HSV or RGB.
    # 
    # @param mode [Symbol]
    # 
    # @return [Symbol] the new alpha blending value
    def color_mode mode=nil
      @color_mode ||= :rgb

      @color_mode = mode.to_sym if mode.present?
      @color_mode
    end

    # Clear the canvas to a color
    # 
    # @param r [Numeric] the amount of red, 0..255
    # @param g [Numeric] the amount of green, 0..255
    # @param b [Numeric] the amount of blue, 0..255
    # 
    # @return [nil] Nothing
    def clear *args
      r, g, b, a = Color.new(color_mode, *args).to_rgb.to_a
      Native.ofClear r.to_f, g.to_f, b.to_f, a.to_f
    end

    def push_matrix
        Native.ofPushMatrix
    end

    def pop_matrix
        Native.ofPushMatrix
    end

    def matrix
        push_matrix
        yield
        pop_matrix
    end

    # @screenshot Rectangle modes
    #   rectangle_mode :corner
    #   color :white
    #   square 50, 50, 20
    # 
    #   rectangle_mode :center
    #   color :black
    #   square 50, 50, 20
    def rectangle_mode mode=nil
      if mode.present?
        Native.ofSetRectMode mode
      else
        Native.ofGetRectMode
      end
    end

    # @screenshot Low resolution circle
    #   circle_resolution 10
    #   circle 50, 50, 45
    # 
    # @screenshot Medium resolution circle
    #   circle_resolution 20
    #   circle 50, 50, 45
    # 
    # @screenshot High resolution circle
    #   circle_resolution 60
    #   circle 50, 50, 45
    def circle_resolution new_resolution=nil
      @circle_resolution ||= 22 # TODO what is the default resolution

      if new_resolution.present?
        @circle_resolution = new_resolution.to_i
        Native.ofSetCircleResolution @circle_resolution
      else
        @circle_resolution
      end
    end

    def curve_resolution new_resolution=nil
      @curve_resolution ||= 22 # TODO what is the default resolution

      if new_resolution.present?
        @curve_resolution = new_resolution.to_i
        Native.ofSetCurveResolution @curve_resolution
      else
        @curve_resolution
      end
    end

    # @screenshot Low resolution sphere
    #   fill false
    #   sphere_resolution 5
    #   sphere 50, 50, 40
    # 
    # @screenshot Medium resolution sphere
    #   fill false
    #   sphere_resolution 12
    #   sphere 50, 50, 40
    # 
    # @screenshot High resolution sphere
    #   fill false
    #   sphere_resolution 16
    #   sphere 50, 50, 40
    def sphere_resolution new_resolution=nil
      @sphere_resolution ||= 22 # TODO what is the default resolution

      if new_resolution.present?
        @sphere_resolution = new_resolution.to_i
        Native.ofSetSphereResolution @sphere_resolution
      else
        @sphere_resolution
      end
    end

    # @screenshot Filled and unfilled circles
    #   fill true
    #   circle 30, 50, 15
    # 
    #   fill false
    #   circle 70, 50, 15
    def fill filled=nil
      if filled.present?
        filled ? Native.ofFill : Native.ofNoFill
      else
        Native.ofGetFill == :filled
      end
    end

    # @screenshot Blend mode
    #   color :white, 128
    # 
    #   blend_mode :add
    #   circle 20, 25, 10
    #   circle 30, 25, 10
    # 
    #   blend_mode :subtract
    #   circle 80, 25, 10
    #   circle 70, 25, 10
    # 
    #   blend_mode :multiply
    #   circle 80, 75, 10
    #   circle 70, 75, 10
    # 
    #   blend_mode :alpha
    #   circle 20, 75, 10
    #   circle 30, 75, 10
    # 
    def blend_mode mode=nil
      @blend_mode ||= :disabled

      if mode.present?
        @blend_mode = mode
        Native.ofDisableBlendMode
        Native.ofEnableBlendMode @blend_mode unless @blend_mode == :disabled
      else
        @blend_mode
      end
    end

    def point_sprites sprites=nil
      @point_sprites ||= false

      if sprites.present?
        @point_sprites = sprites.to_bool
        @point_sprites ? Native.ofEnablePointSprites : Native.ofDisablePointSprites
      else
        @point_sprites
      end
    end

    def push_style
      Native.ofPushStyle
    end

    def pop_style
      Native.ofPopStyle
    end

    # @screenshot Isolated style
    #   fill true
    #   color :white
    #   circle 30, 30, 15
    # 
    #   style do
    #     color :yellow
    #     fill false
    #     circle 70, 50, 15
    #   end
    # 
    #   circle 30, 70, 15
    def style
      push_style
      yield
      pop_style
    end

    def clear_background clear=nil
      if clear.present?
        Native.ofSetBackgroundAuto clear.to_bool
      else
        Native.ofbClearBg
      end
    end

    # @screenshot Triangle
    #   triangle 50, 50, 30
    # 
    # @screenshot Equilateral triangles
    #   fill false
    #   triangle 50, 50, 50
    #   triangle 50, 50, 40
    #   triangle 50, 50, 30
    #   triangle 50, 50, 20
    #   triangle 50, 50, 10
    # 
    # 
    # @screenshot Isosceles triangles
    #   fill false
    #   triangle 50, 50, 30, 170
    #   triangle 50, 50, 30, 150
    #   triangle 50, 50, 30, 130
    #   triangle 50, 50, 30, 110
    #   triangle 50, 50, 30, 90
    # 
    # 
    # @screenshot Scalene triangle
    #   fill false
    #   triangle 75, 60, 50, 50, 80, 10
    # 
    def triangle *args
      x1 = y1 = z1 = x2 = y2 = z2 = x3 = y3 = z3 = 0

      equilateral_algorithm = proc { |x, y, z, r|
        a = Math::PI - Math::PI/3
        x1 = x + cos(Math::PI/2) * r
        y1 = y - sin(Math::PI/2) * r
        z1 = z
        x2 = x + cos(Math::PI/2 + a) * r
        y2 = y - sin(Math::PI/2 + a) * r
        z2 = z
        x3 = x + cos(Math::PI/2 + 2*a) * r
        y3 = y - sin(Math::PI/2 + 2*a) * r
        z3 = z
      }

      isosceles_algorithm = proc { |x, y, z, r, a|
        a = a.to_rad
        h = (r+r/2) / sin(a/2) # sine law, bitches
        x1 = x + cos(Math::PI/2) * r
        y1 = y - sin(Math::PI/2) * r
        z1 = z
        x2 = x1 + cos(Math::PI + (Math::PI - a/2)) * h
        y2 = y1 - sin(Math::PI + (Math::PI - a/2)) * h
        z2 = z
        x3 = x1 + cos(a/2 - Math::PI) * h
        y3 = y1 - sin(a/2 - Math::PI) * h
        z3 = z
      }

      case args
      # equilateral triangle
      when Signature[[:x,:y,:z], :to_f]
        point, r = *args
        equilateral_algorithm.call point.x, point.y, point.z, r
        
      when Signature[[:x,:y], :to_f]
        point, r = *args
        equilateral_algorithm.call point.x, point.y, 0, r
        
      when Signature[:to_f, :to_f, :to_f]
        x, y, r = *args
        equilateral_algorithm.call x, y, 0, r

      # isosceles triangle
      when Signature[[:x,:y,:z], :to_f, :to_f]
        point, r, a = *args
        isosceles_algorithm.call point.x, point.y, point.z, r, a

      when Signature[[:x,:y], :to_f, :to_f]
        point, r, a = *args
        isosceles_algorithm.call point.x, point.y, 0, r, a

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, r, a = *args
        isosceles_algorithm.call x, y, 0, r, a

      # scalene triangle
      when Signature[[:x,:y,:z], [:x,:y,:z], [:x,:y,:z]]
        a, b, c = *args
        x1, y1, z1 = a.x, a.y, a.z
        x2, y2, z2 = b.x, b.y, b.z
        x3, y3, z3 = c.x, c.y, c.z

      when Signature[[:x,:y], [:x,:y], [:x,:y]]
        a, b, c = *args
        x1, y1 = a.x, a.y
        x2, y2 = b.x, b.y
        x3, y3 = c.x, c.y

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x1, y1, z1, x2, y2, z2, x3, y3, z3 = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x1, y1, x2, y2, x3, y3 = *args
      end

      Native.ofTriangle x1.to_f, y1.to_f, z1.to_f, x2.to_f, y2.to_f, z2.to_f, x3.to_f, y3.to_f, z3.to_f
    end

    # @screenshot Ellipse
    #   ellipse 50, 50, 80, 40
    # 
    def ellipse *args
      x = y = z = w = h = 0

      case args
      when Signature[[:x,:y], [:width,:height]]
        point, dim = *args
        x, y = point.x, point.y
        w, h = point.width, point.height

      when Signature[[:x,:y], :to_f, :to_f]
        point, w, h = *args
        x, y = point.x, point.y

      when Signature[:to_f, :to_f, [:width,:height]]
        x, y, dim = *args
        w, h = dim.width, dim.height

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, w, h = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f]
        x, y, z, w, h = *args
      end

      Native.ofEllipse x.to_f, y.to_f, z.to_f, w.to_f, h.to_f
    end

    # @screenshot Basic rounded rectangle
    #   rounded_rectangle 10, 10, 80, 80, 10
    def rounded_rectangle *args
      x = y = z = w = h = r = 0

      case args
      when Signature[[:x,:y,:z], [:width,:height], :to_f]
        point, dim, r = *args
        x, y, z = point.x, point.y, point.z
        w, h = dim.width, dim.height

      when Signature[[:x,:y], [:width,:height], :to_f]
        point, dim, r = *args
        x, y = point.x, point.y
        w, h = dim.width, dim.height

      when Signature[:to_f, :to_f, [:width,:height], :to_f]
        x, y, dim, r = *args
        w, h = dim.width, dim.height

      when Signature[[:x,:y], :to_f, :to_f, :to_f]
        point, w, h, r = *args
        x, y = point.x, point.y

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f]
        x, y, w, h, r = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x, y, z, w, h, r = *args
      end

      Native.ofRectRounded x.to_f, y.to_f, z.to_f, w.to_f, h.to_f, r.to_f
    end

    # @screenshot
    #   fill false
    #   curve 10, -100, 10, 50, 90, 50, 90, 200
    def curve *args
      x0 = y0 = z0 = x1 = y1 = z1 = x2 = y2 = z2 = x3 = y3 = z3 = 0

      case args
      when Signature[[:x,:y,:z], [:x,:y,:z], [:x,:y,:z], [:x,:y,:z]]
        a, b, c, d = *args
        x0, y0, z0 = a.x, a.y, a.z
        x1, y1, z1 = b.x, b.y, b.z
        x2, y2, z2 = c.x, c.y, c.z
        x3, y3, z3 = d.x, d.y, d.z

      when Signature[[:x,:y], [:x,:y], [:x,:y], [:x,:y]]
        a, b, c, d = *args
        x0, y0 = a.x, a.y
        x1, y1 = b.x, b.y
        x2, y2 = c.x, c.y
        x3, y3 = d.x, d.y

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x0, y0, x1, y1, x2, y2, x3, y3 = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3 = *args
      end

      Native.ofCurve x0.to_f, y0.to_f, z0.to_f, x1.to_f, y1.to_f, z1.to_f, x2.to_f, y2.to_f, z2.to_f, x3.to_f, y3.to_f, z3.to_f
    end

    # @screenshot Bezier curve
    #   fill false
    #   bezier 10, 10, 10, 50, 90, 50, 90, 90
    def bezier *args
      x0 = y0 = z0 = x1 = y1 = z1 = x2 = y2 = z2 = x3 = y3 = z3 = 0

      case args
      when Signature[[:x,:y,:z], [:x,:y,:z], [:x,:y,:z], [:x,:y,:z]]
        a, b, c, d = *args
        x0, y0, z0 = a.x, a.y, a.z
        x1, y1, z1 = b.x, b.y, b.z
        x2, y2, z2 = c.x, c.y, c.z
        x3, y3, z3 = d.x, d.y, d.z

      when Signature[[:x,:y], [:x,:y], [:x,:y], [:x,:y]]
        a, b, c, d = *args
        x0, y0 = a.x, a.y
        x1, y1 = b.x, b.y
        x2, y2 = c.x, c.y
        x3, y3 = d.x, d.y

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x0, y0, x1, y1, x2, y2, x3, y3 = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3 = *args
      end

      Native.ofBezier x0.to_f, y0.to_f, z0.to_f, x1.to_f, y1.to_f, z1.to_f, x2.to_f, y2.to_f, z2.to_f, x3.to_f, y3.to_f, z3.to_f
    end

    def begin_shape
      Native.ofBeginShape
    end

    def end_shape close=true
      Native.ofEndShape close.to_bool
    end

    # @screenshot Star
    #   shape do
    #     vertex 50, 10
    #     vertex 40, 30
    #     vertex 10, 30
    #     vertex 40, 45
    #     vertex 20, 80
    #     vertex 50, 60
    #     vertex 80, 80
    #     vertex 60, 45
    #     vertex 90, 30
    #     vertex 60, 30
    #   end
    # 
    # @screenshot Wave
    #   fill false
    #   shape :open do
    #     width.to_i.times do |x|
    #       vertex x, 50 + sin(x / 4.0) * 10
    #     end
    #   end
    # 
    # @see #vertex, #curve_vertex, #begin_shape, #end_shape, #next_contour
    def shape close=:closed
      begin_shape
      yield
      end_shape close==:closed
    end

    def next_contour close=true
      Native.ofNextContour close.to_bool
    end

    def vertex *args
      x = y = z = 0

      case args
      when Signature[[:x,:y,:z]]
        x, y, z, = args.first.x, args.first.y, args.first.z

      when Signature[[:x,:y]]
        x, y = args.first.x, args.first.y

      when Signature[:to_f, :to_f]
        x, y = *args

      when Signature[:to_f, :to_f, :to_f]
        x, y, z = *args
      end

      Native.ofVertex x.to_f, y.to_f, z.to_f
    end

    # @screenshot Soft star
    #   shape do
    #     curve_vertex 50, 10
    #     curve_vertex 50, 10
    #     curve_vertex 40, 30
    #     curve_vertex 10, 30
    #     curve_vertex 40, 45
    #     curve_vertex 20, 80
    #     curve_vertex 50, 60
    #     curve_vertex 80, 80
    #     curve_vertex 60, 45
    #     curve_vertex 90, 30
    #     curve_vertex 60, 30
    #     curve_vertex 50, 10
    #   end
    def curve_vertex *args
      x = y = 0

      case args
      when Signature[[:x,:y]]
        x, y = args.first.x, args.first.y

      when Signature[:to_f, :to_f]
        x, y = *args
      end

      Native.ofCurveVertex x.to_f, y.to_f
    end

    def bezier_vertex *args
      x1 = y1 = z1 = x2 = y2 = z2 = 0

      case args
      when Signature[[:x,:y,:z], [:x,:y,:z]]
        a, b = *args
        x1, y1, z1 = a.x, a.y, a.z
        x2, y2, z2 = b.x, b.y, b.z

      when Signature[[:x,:y], [:x,:y]]
        a, b = *args
        x1, y1 = a.x, a.y
        x2, y2 = b.x, b.y

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x1, y1, x2, y2 = *args

      when Signature[:to_f, :to_f, :to_f, :to_f, :to_f, :to_f]
        x1, y1, z1, x2, y2, z2 = *args
      end
      
      Native.ofBezierVertex x1.to_f, y1.to_f, z1.to_f, x2.to_f, y2.to_f, z2.to_f
    end

    # @screenshot Wireframe Sphere
    #   fill false
    #   sphere 50, 50, 40
    def sphere *args
      x = y = z = r = 0

      case args
      when Signature[[:x,:y,:z], :to_f]
        p, r = *args
        x, y, z = p.x, p.y, p.z

      when Signature[[:x,:y], :to_f]
        p, r = *args
        x, y = p.x, p.y

      when Signature[:to_f, :to_f, :to_f]
        x, y, r = *args

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, z, r = *args
      end

      Native.ofSphere x.to_f, y.to_f, z.to_f, r.to_f
    end

    # @screenshot Boxes in the corners
    #   fill false
    #   box 20, 20, 30
    #   box 20, 80, 30
    #   box 80, 20, 30
    #   box 80, 80, 30
    def box *args
      x = y = z = r = 0

      case args
      when Signature[[:x,:y,:z], :to_f]
        p, r = *args
        x, y, z = p.x, p.y, p.z

      when Signature[[:x,:y], :to_f]
        p, r = *args
        x, y = p.x, p.y

      when Signature[:to_f, :to_f, :to_f]
        x, y, r = *args

      when Signature[:to_f, :to_f, :to_f, :to_f]
        x, y, z, r = *args
      end

      Native.ofBox x.to_f, y.to_f, z.to_f, r.to_f
    end

    def polygon_winding_mode mode=nil
      @polygon_winding_mode ||= :odd # is this the default?

      if mode.present?
        @polygon_winding_mode = mode
        Native.ofSetPolyMode @polygon_winding_mode
      else
        @polygon_winding_mode
      end
    end

    def push_view
      Native.ofPushView
    end

    def pop_view
      Native.ofPopView
    end

    def view
      push_view
      yield
      pop_view
    end

    def viewport x=0.0, y=0.0, w=0.0, h=0.0, invert_y=true
      Native.ofViewport x.to_f, y.to_f, w.to_f, h.to_f, invert_y.to_bool
    end

    def viewport_height
      Native.ofGetViewportHeight
    end

    def viewport_width
      Native.ofGetViewportWidth
    end

    # Enable smoothing
    def smoothing smooth=nil
      @smoothing_enabled ||= false

      if smooth.present?
        @smoothing_enabled = smooth.to_bool
        @smoothing_enabled ? Native.ofEnableSmoothing : Native.ofDisableSmoothing
      else
        @smoothing_enabled
      end
    end

    # @screenshot Single point
    #   point 50, 50
    def point x, y
      shape { vertex x, y; vertex x, y+1 }
    end

    # Reset graphics settings to Zajal's defaults
    def defaults
      alpha_blending false
      background :ketchup
      blend_mode :disabled
      circle_resolution 22
      clear_background true
      color_mode :rgb
      color :white
      curve_resolution 22
      fill true
      line_width 1
      point_sprites false
      polygon_winding_mode :odd
      rectangle_mode :corner
      smoothing false
      sphere_resolution 8
      Zajal::Graphics::Native.ofSetupScreenPerspective width.to_f, height.to_f, :default, false, 60.0, 0.0, 0.0
    end

    # @api internal
    def self.included sketch
      sketch.before_event :setup do
        defaults
      end

      sketch.after_event :setup do
        @defaults = {}
        %w[alpha_blending background blend_mode circle_resolution clear_background
          color curve_resolution fill line_width point_sprites polygon_winding_mode
          rectangle_mode smoothing sphere_resolution].each do |m|
          @defaults[m.to_sym] = self.send m.to_sym
        end
      end

      sketch.before_event :draw do
        Native.ofSetupScreen
        @defaults.each { |meth, val| self.send meth, val }
      end
    end

    # FFI hooks to Math::pIled openFrameworks functionality.
    # 
    # The methods in here do the actual work by invoking Math::pIled C++
    # functions in +libof.so+.
    # @api internal
    module Native
      extend FFI::Cpp::Library

      ffi_lib "lib/core/lib/libof.so"

      enum :ofOrientation,
       [:default,
        :oneEighty,
        :ninety_left,
        :ninety_right,
        :unknown]
      enum :ofHandednessType,
       [:left,
        :right]
      enum :ofRectMode,
       [:corner,
        :center]
      enum :ofFillFlag,
       [:outline,
        :filled]
      enum :ofBlendMode,
       [:disabled,
        :alpha,
        :add,
        :subtract,
        :multiply,
        :screen]
      enum :ofPolyWindingMode,
       [:odd,
        :nonzero,
        :positive,
        :negative,
        :abs_geq_two]

      typedef :pointer, :ofRectangle
      typedef :pointer, :ofStyle

      # TODO technically, this is not a Graphics method. Move it.
      typedef :pointer, :ofAppBaseWindow
      attach_function :ofSetupOpenGL, [type(:ofAppBaseWindow).pointer, :int, :int, :int], :void

      # pdf screenshot
      attach_function :ofBeginSaveScreenAsPDF, [:stdstring, :bool, :bool, :ofRectangle], :void
      attach_function :ofEndSaveScreenAsPDF, [], :void

      #  view transformations
      attach_function :ofPushView, [], :void
      attach_function :ofPopView, [], :void

      #  matrices and viewport
      attach_function :ofViewport, [:float, :float, :float, :float, :bool], :void
      attach_function :ofSetupScreenPerspective, [:float, :float, :ofOrientation, :bool, :float, :float, :float], :void
      attach_function :ofSetupScreenOrtho, [:float, :float, :ofOrientation, :bool, :float, :float], :void
      attach_function :ofGetCurrentViewport, [], :ofRectangle
      attach_function :ofGetViewportWidth, [], :int
      attach_function :ofGetViewportHeight, [], :int
      attach_function :ofOrientationToDegrees, [:ofOrientation], :int
      attach_function :ofSetCoordHandedness, [:ofHandednessType], :void
      attach_function :ofGetCoordHandedness, [], :ofHandednessType

      # transformations
      attach_function :ofPushMatrix, [], :void # matrix, push_matrix
      attach_function :ofPopMatrix, [], :void # matrix, pop_matrix
      attach_function :ofTranslate, [:float, :float, :float], :void # translate
      attach_function :ofScale, [:float, :float, :float], :void # scale
      attach_function :ofRotate, [:float, :float, :float, :float], :void 
      attach_function :ofRotateX, [:float], :void
      attach_function :ofRotateY, [:float], :void
      attach_function :ofRotateZ, [:float], :void # rotate

      #  screen coordinates / default gl values
      attach_function :ofSetupGraphicDefaults, [], :void
      attach_function :ofSetupScreen, [], :void

      #  drawing modes
      attach_function :ofGetRectMode, [], :ofRectMode
      attach_function :ofSetCircleResolution, [:int], :void
      attach_function :ofSetCurveResolution, [:int], :void
      attach_function :ofSetSphereResolution, [:int], :void

      #  drawing options
      attach_function :ofNoFill, [], :void
      attach_function :ofFill, [], :void
      attach_function :ofGetFill, [], :ofFillFlag
      attach_function :ofSetLineWidth, [:float], :void

      #  color options
      attach_function :ofSetColor, [:int, :int, :int, :int], :void 
      attach_function :ofSetHexColor, [:int], :void

      #  Blending
      attach_function :ofEnableBlendMode, [:ofBlendMode], :void
      attach_function :ofDisableBlendMode, [], :void

      #  point
      attach_function :ofEnablePointSprites, [], :void
      attach_function :ofDisablePointSprites, [], :void

      #  transparency
      attach_function :ofEnableAlphaBlending, [], :void
      attach_function :ofDisableAlphaBlending, [], :void

      #  smooth 
      attach_function :ofEnableSmoothing, [], :void
      attach_function :ofDisableSmoothing, [], :void

      #  drawing style
      attach_function :ofGetStyle, [], :ofStyle
      attach_function :ofSetStyle, [:ofStyle], :void
      attach_function :ofPushStyle, [], :void
      attach_function :ofPopStyle, [], :void
      attach_function :ofSetPolyMode, [:ofPolyWindingMode], :void
      attach_function :ofSetRectMode, [:ofRectMode], :void

      #  background
      attach_function :ofBgColorPtr, [], :pointer
      attach_function :ofBackground, [:int, :int, :int, :int], :void
      attach_function :ofBackgroundHex, [:int, :int], :void
      # attach_function :ofBackgroundGradient, [const ofColor& start, const ofColor& end, ofGradientMode mode], :void
      attach_function :ofSetBackgroundColor, [:int, :int, :int, :int], :void
      attach_function :ofSetBackgroundColorHex, [:int, :int], :void
      attach_function :ofSetBackgroundAuto, [:bool], :void
      attach_function :ofClear, [:float, :float, :float, :float], :void
      attach_function :ofClearAlpha, [], :void
      attach_function :ofbClearBg, [], :bool

      #  geometry
      attach_function :ofTriangle, [:float, :float, :float, :float, :float, :float, :float, :float, :float], :void
      attach_function :ofCircle, [:float, :float, :float, :float], :void
      attach_function :ofEllipse, [:float, :float, :float, :float, :float], :void
      attach_function :ofLine, [:float, :float, :float, :float, :float, :float], :void
      attach_function :ofRect, [:float, :float, :float, :float, :float], :void
      attach_function :ofRectRounded, [:float, :float, :float, :float, :float, :float], :void
      attach_function :ofCurve, [:float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :float], :void
      attach_function :ofBezier, [:float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :float, :float], :void

      # polygons
      attach_function :ofBeginShape, [], :void
      attach_function :ofVertex, [:float, :float, :float], :void
      attach_function :ofCurveVertex, [:float, :float], :void
      attach_function :ofBezierVertex, [:float, :float, :float, :float, :float, :float, :float, :float, :float], :void
      attach_function :ofEndShape, [:bool], :void
      attach_function :ofNextContour, [:bool], :void

      # 3d
      attach_function :ofSphere, [:float, :float, :float, :float], :void
      attach_function :ofBox, [:float, :float, :float, :float], :void
      attach_function :ofCone, [:float, :float, :float, :float, :float], :void
    end
  end
end