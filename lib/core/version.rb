module Zajal
  module Version
    # Major version number, the X in X.Y.Z
    MAJOR     = 0

    # Minor version number, the Y in X.Y.Z
    MINOR     = 4

    # Revision number, the Z in X.Y.Z
    REVISION  = 0

    # Release code name, named after the streets where Zajal is being
    # developed
    NAME      = "Amsterdam"

    def self.print
      puts Zajal::VERSION
      # puts "Rubinius #{Rubinius::VERSION}"
      puts "Ruby #{RUBY_VERSION}"
      puts "openFrameworks 00#{Native.ofGetVersionMajor}#{Native.ofGetVersionMinor}"
    end

    module Native
      extend FFI::Cpp::Library

      ffi_lib "lib/core/lib/libof.so"

      attach_function :ofGetVersionMajor, [], :int
      attach_function :ofGetVersionMinor, [], :int
    end

  end

  # Human readable version string
  # @example
  #   VERSION # => "Zajal 0.4.0 Amsterdam"
  VERSION = "Zajal #{Version::MAJOR}.#{Version::MINOR}.#{Version::REVISION} #{Version::NAME}"
end