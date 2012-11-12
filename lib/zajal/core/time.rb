module Zajal
  module Time
    def time
      Native.ofGetElapsedTimef
    end

    def seconds
      time
    end

    def milliseconds
      Native.ofGetElapsedTimeMillis
    end

    def microseconds
      Native.ofGetElapsedTimeMicros
    end

    def frame
      Native.ofGetFrameNum
    end

    module Native
      extend FFI::Cpp::Library

      File.expand_path("lib/libof.so", File.dirname(__FILE__))

      attach_function :ofResetElapsedTimeCounter, [], :void
      attach_function :ofGetElapsedTimef, [], :float
      attach_function :ofGetElapsedTimeMillis, [], :ulong
      attach_function :ofGetElapsedTimeMicros, [], :ulong
      attach_function :ofGetFrameNum, [], :int
    end
  end
end