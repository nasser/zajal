module Zajal
  # @api zajal
  module App
    # @overload framerate target
    #   @param [#to_i] target target framerate
    #   Set a new target framerate
    # 
    #   Zajal will try to match `target`, but complex scenes may run slower
    # 
    # @overload framerate
    #   Get the average number of frames rendered every second
    #   
    #   This is a good way to check the performance of your sketch
    #   
    #   @return [Float] actual framerate
    # @api internal
    def framerate target=nil
      warn "WARNING: App##{__method__} still needs native implementation!"
      if target.present?
        Native.ofSetFrameRate target.to_i
      else
        Native.ofGetFrameRate
      end
    end

    # Get the number of frames rendered since the sketch started
    # 
    # @example Screenshot every 30 frames
    #   draw do
    #     # draw sketch
    #     fill false
    #     30.times do |i|
    #       circle width/2, height/2, noise(time, i/10.0) * width
    #     end
    # 
    #     # save a screenshot if frame evenly divides 30
    #     grab_screen.save "~/Desktop/screenshot.png" if frame % 30 == 0
    #   end
    # 
    # @example Render out numbered sequence
    #   draw do
    #     # draw sketch
    #     fill false
    #     30.times do |i|
    #       circle width/2, height/2, noise(time, i/10.0) * width
    #     end
    #   
    #     # save a screenshot every frame
    #     # use frame number to sequentially number them
    #     grab_screen.save "~/Desktop/frame-#{frame}.png"
    #   end
    #     
    # 
    # @return [Fixnum] current frame number
    def frame
      # TODO set frame number?
      Native.ofGetFrameNum
    end

    # Get the time it took to render the last frame
    # 
    # @return [Float] time to render last frame
    # @api internal
    def last_frame_time
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetLastFrameTime
    end

    # @overload cursor show
    #   Show or hide the cursor
    #   @example Hide on mouse click, show on key press
    #     mouse_down do
    #       cursor false
    #     end
    #     
    #     key_down do
    #       cursor true
    #     end
    #   @param [Boolean] show true to show the cursor, false to hide
    # 
    # @overload cursor
    #   Get whether or not the cursor is showing
    #       
    #   @return [Boolean] is cursor visible?
    def cursor show=nil
      @cursor_visible ||= true

      if show.present?
        if show
          @cursor_visible = true
          Native.ofShowCursor
        else
          @cursor_visible = false
          Native.ofHideCursor
        end
      else
        @cursor_visible
      end
    end

    # @overload window_position_x new_x
    #   Set the x position of the sketch window
    #   @param [#to_i] new_x new x position
    # 
    # @overload window_position_x
    #   Get the x position of the sketch window
    #   @return [Fixnum] current x position of window
    # @api internal
    def window_position_x new_x=nil?
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_x.present?
        window_position new_x, window_position_y
      else
        Native.ofGetWindowPositionX
      end
    end

    # @overload window_position_y new_y
    #   Set the y position of the sketch window
    #   @param [#to_i] new_y new y position
    # 
    # @overload window_position_y
    #   Get the y position of the sketch window
    #   @return [Fixnum] current y position of window
    # @api internal
    def window_position_y new_y=nil?
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_y.present?
        window_position window_position_x, new_y
      else
        Native.ofGetWindowPositionX
      end
    end

    # @api internal
    def window_position new_x=nil, new_y=nil
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_y.present?
        Native.ofSetWindowPosition new_x.to_i, new_y.to_i
      elsif new_x.present?
        window_position new_x, new_x
      else
        [window_position_x, window_position_y]
      end
    end

    # Get the width of the screen
    # @return [Fixnum] width of the screen
    # @api internal
    def screen_width
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetScreenWidth
    end
    # Get the height of the screen
    # @return [Fixnum] height of the screen
    # @api internal
    def screen_height
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetScreenHeight
    end

    # @overload title new_title
    #   @example
    #     title "My Amazing Sketch"
    #   Set the title of the sketch window
    #   @param [#to_s] new_title new window title
    # 
    # @overload title
    #   Get the current title of the sketch window
    #   @return [String] window title
    def title new_title=nil
      @window_title ||= ""

      if new_title.present?
        @window_title = new_title.to_s
        Native.ofSetWindowTitle @window_title.to_ptr
      else
        @window_title
      end
    end

    # @overload width new_width
    #   Set the sketch's width
    #   @param [#to_i] new_width sketch width
    # 
    # @overload width
    #   Get the sketch's current width
    #   Useful for alignment
    #   @demo Right aligned
    #     circle width, 20, 10
    #     circle width, 50, 10
    #     circle width, 80, 10
    #   @demo Center aligned
    #     circle width/2, 20, 10
    #     circle width/2, 50, 10
    #     circle width/2, 80, 10
    #   @demo Displaying width
    #     text width
    #     text width/2
    # 
    #   @return [Fixnum] current width
    def width new_width=nil
      if new_width.present?
        size new_width, height
      else
        Native.ofGetWidth
      end
    end

    # @overload height new_height
    #   Set the sketch's height
    #   @param [#to_i] new_height sketch height
    # 
    # @overload height
    #   Get the sketch's current height
    #   Useful for alignment
    #   @demo Bottom aligned
    #     circle 20, height, 10
    #     circle 50, height, 10
    #     circle 80, height, 10
    #   @demo Center aligned
    #     circle 20, height/2, 10
    #     circle 50, height/2, 10
    #     circle 80, height/2, 10
    #   @demo Displaying height
    #     text height
    #     text height/2
    # 
    #   @return [Fixnum] current height
    def height new_height=nil
      if new_height.present?
        size width, new_height
      else
        Native.ofGetHeight
      end
    end

    # @overload size new_width, new_height
    # @overload size new_size
    # @overload size
    def size new_width=nil, new_height=nil
      if new_height.present?
        Native.ofSetWindowShape new_width.to_i, new_height.to_i
      elsif new_width.present?
        size new_width, new_width
      else
        [width, height]
      end
    end

    # @overload fullscreen full
    # @overload fullscreen
    # @api internal
    def fullscreen full=nil
      warn "WARNING: App##{__method__} still needs native implementation!"
      @in_fullscreen ||= false

      if full.present?
        @in_fullscreen = full.to_bool
        Native.ofSetFullscreen @in_fullscreen
      else
        @in_fullscreen
      end
    end

    # @overload vertical_sync sync
    # @overload vertical_sync
    # @api internal
    def vertical_sync sync=nil
      warn "WARNING: App##{__method__} still needs native implementation!"
      @vertical_sync = true

      if sync.present?
        @vertical_sync = sync.to_bool
        Native.ofSetVerticalSync @vertical_sync
      else
        @vertical_sync
      end
    end

    # @api internal
    def self.included sketch
      sketch.before_event :setup do
        # calls to ofToDataPath (which a bunch of classes use) will call
        # ofSetDataPathRoot if isDataPathSet() is false. ofSetDataPathRoot will
        # (annoyingly) chdir to the folder that the current executable is in
        # and break everything. fortunatley, once its called it is no longer
        # an issue. Dir.chdir will reset the chdir after ofSetDataPathRoot
        # tries to break things.
        Dir.chdir do
          Native.ofSetDataPathRoot Dir.pwd.to_ptr
        end
      end
    end

    module Native
      extend FFI::Cpp::Library
      ffi_lib "lib/core/lib/libof.so"

      attach_function :ofGetFrameRate, [], :float
      attach_function :ofGetFrameNum, [], :int
      attach_function :ofSetFrameRate, [:int], :void
      # ofSleepMillis not implemented, use Kernel#sleep
      # attach_function :ofSleepMillis, [:int], :void
      attach_function :ofGetLastFrameTime, [], :double

      # TODO figure out orientation, not super important until ios/android
      # attach_function :ofSetOrientation, [:ofOrientation], :void
      # attach_function :ofGetOrientation, [], :ofOrientation

      attach_function :ofHideCursor, [], :void
      attach_function :ofShowCursor, [], :void
      attach_function :ofGetWindowPositionX, [], :int
      attach_function :ofGetWindowPositionY, [], :int
      attach_function :ofGetScreenWidth, [], :int
      attach_function :ofGetScreenHeight, [], :int
      # TODO map window modes
      # attach_function :ofGetWindowMode, [], :int
      attach_function :ofGetWidth, [], :int
      attach_function :ofGetHeight, [], :int
      # ofGetWindowWidth not implemented, same as ofGetWidth
      # attach_function :ofGetWindowWidth, [], :int
      # ofGetWindowHeight not implemented, same as ofGetHeight
      # attach_function :ofGetWindowHeight, [], :int
      # TODO figure out orientation, see above
      # attach_function :ofDoesHWOrientation, [], :bool
      # ofGetWindowSize not implemented, not needed (use ofGetWidth, ofGetHeight) 
      # attach_function :ofGetWindowSize, [], :ofPoint
      # ofGetWindowRect not implemented, not needed (use ofGetWidth, ofGetHeight)
      # attach_function :ofGetWindowRect, [], :ofRectangle

      attach_function :ofSetWindowPosition, [:int, :int], :void
      attach_function :ofSetWindowShape, [:int, :int], :void
      attach_function :ofSetWindowTitle, [:stdstring], :void
      # ofEnableSetupScreen not implemented, not needed
      # attach_function :ofEnableSetupScreen, [], :void
      # ofDisableSetupScreen not implemented, not needed
      # attach_function :ofDisableSetupScreen, [], :void
      attach_function :ofSetFullscreen, [:bool], :void
      # ofToggleFullscreen not implemented, not needed (use ofSetFullscreen)
      # attach_function :ofToggleFullscreen, [], :void

      attach_function :ofSetVerticalSync, [:bool], :void

      attach_function :ofSetDataPathRoot, [:stdstring], :void
    end
  end
end