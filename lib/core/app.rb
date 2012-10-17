module Zajal
  module App
    def framerate new_framerate=nil
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_framerate.present?
        Native.ofSetFrameRate new_framerate.to_i
      else
        Native.ofGetFrameRate
      end
    end

    def frame
      # TODO set frame number?
      Native.ofGetFrameNum
    end

    def last_frame_time
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetLastFrameTime
    end

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

    def window_position_x new_x=nil?
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_x.present?
        window_position new_x, window_position_y
      else
        Native.ofGetWindowPositionX
      end
    end

    def window_position_y new_y=nil?
      warn "WARNING: App##{__method__} still needs native implementation!"
      if new_y.present?
        window_position window_position_x, new_y
      else
        Native.ofGetWindowPositionX
      end
    end

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

    def screen_width
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetScreenWidth
    end

    def screen_height
      warn "WARNING: App##{__method__} still needs native implementation!"
      Native.ofGetScreenHeight
    end

    def title new_title=nil
      @window_title ||= ""

      if new_title.present?
        @window_title = new_title.to_s
        Native.ofSetWindowTitle @window_title.to_ptr
      else
        @window_title
      end
    end

    def width new_width=nil
      if new_width.present?
        size new_width, height
      else
        Native.ofGetWidth
      end
    end

    def height new_height=nil
      if new_height.present?
        size width, new_height
      else
        Native.ofGetHeight
      end
    end

    def size new_width=nil, new_height=nil
      if new_height.present?
        Native.ofSetWindowShape new_width.to_i, new_height.to_i
      elsif new_width.present?
        size new_width, new_width
      else
        [width, height]
      end
    end

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
    end
  end
end