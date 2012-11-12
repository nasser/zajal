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

    RUBY_VM_VERSION = "Rubinius #{Rubinius::VERSION}"

    def self.print
      puts "Zajal #{Zajal::VERSION} #{Version::NAME}"
      puts "Ruby #{RUBY_VERSION} (#{RUBY_VM_VERSION})"
      puts "openFrameworks 00#{Native.ofGetVersionMajor}#{Native.ofGetVersionMinor}"
    end

    module Native
      extend FFI::Cpp::Library

      ffi_lib "lib/zajal/core/lib/libof.so"

      attach_function :ofGetVersionMajor, [], :int
      attach_function :ofGetVersionMinor, [], :int
    end
  end

  # @example
  #   VERSION # => "0.4.0"
  VERSION = "#{Version::MAJOR}.#{Version::MINOR}.#{Version::REVISION}"
end