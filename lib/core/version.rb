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
    NAME    = "Amsterdam"

    def self.print
      puts Zajal::VERSION
      puts "Rubinius #{Rubinius::VERSION} - Ruby #{RUBY_VERSION}"
      puts "of version: 7"
    end
  end

  # Human readable version string
  # @example
  #   VERSION # => "Zajal 0.4.0 Amsterdam"
  VERSION = "Zajal - #{Version::MAJOR}.#{Version::MINOR}.#{Version::REVISION} #{Version::NAME}"
end