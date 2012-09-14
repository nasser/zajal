module Zajal
	module Version
		MAJOR 		= 0
		MINOR 		= 4
		REVISION 	= 0
		NAME 		= "Amsterdam"

		def self.print
			puts Zajal::VERSION
			puts "Rubinius #{Rubinius::VERSION} - Ruby #{RUBY_VERSION}"
			puts "of version: 7"
		end
	end

	VERSION = "Zajal - #{Version::MAJOR}.#{Version::MINOR}.#{Version::REVISION} #{Version::NAME}"
end