module FFI::Cpp
	module Manglers
		class GCC4X
			# http://mentorembedded.github.com/cxx-abi/abi.html#mangling
			MangledTypes = {
				stdstring:			"Ss",
				void: 				"v",
				wchar_t: 			"w",
				bool: 				"b",
				char: 				"c",
				signed_char: 		"a",
				unsigned_char: 		"h",
				short: 				"s",
				unsigned_short: 	"t",
				int: 				"i",
				unsigned_int: 		"j",
				long: 				"l",
				unsigned_long: 		"m",
				long_long: 			"x",
				___int64: 			"x",
				unsigned_long_long: "y",
				___int64: 			"y",
				__int128: 			"n",
				unsigned___int128: 	"o",
				float: 				"f",
				double: 			"d",
				long_double: 		"e",
				___float80: 		"e",
				__float128: 		"g",
				ellipsis: 			"z",
				ieee_754r_64: 		"Dd",
				ieee_754r_128: 		"De",
				ieee_754r_32: 		"Df",
				ieee_754r_16: 		"Dh",
				char32_t: 			"Di",
				char16_t: 			"Ds",
				auto: 				"Da",
				stdnullptr_t: 		"Dn"
			}

			def self.mangle_type t
				if MangledTypes.has_key? t
					MangledTypes[t] 
				# elsif FFI.find_type(t) == :pointer # TODO Fix kludge!
				else
					"P#{t.length}#{t}"
				end
			end

			def self.mangle_identifier i
				case i
				when :ctor; "C1"
				when :dtor; "D1"
				else; "#{i.size}#{i}"
				end
			end

			def self.mangle_function method, params
				method = mangle_identifier method
				params = [:void] if params.empty?

				"_Z#{method}#{params.map { |p| mangle_type(p) }.join}"
			end

			def self.mangle_method klass, method, params
				klass = "#{klass.size}#{klass}"
				method = mangle_identifier method
				params = [:void] if params.empty?

				"_ZN#{klass}#{method}E#{params.map { |p| mangle_type(p) }.join}"
			end

		end
	end
end

module FFI::Cpp::Library
	include FFI::Library

	# support cpp linkage in attach_function
	alias :attach_c_function :attach_function
	def attach_function rbname, cname, params, returns=nil, options={}
		if returns.nil?
			returns = params
			params = cname
			cname = rbname
		end

		begin
			# try c linkage
			attach_c_function rbname, cname, params, returns

		rescue FFI::NotFoundError
			# try cpp linkage
			mangled_name = FFI::Cpp::Manglers::GCC4X.mangle_function cname, params
			attach_c_function rbname, mangled_name, params, returns

		end
	end

	def attach_constructor klass, size, params
		mangled_name = FFI::Cpp::Manglers::GCC4X.mangle_method klass, :ctor, params
		implicit_params = [:pointer] + params

		attach_c_function "#{klass.downcase}_ctor", mangled_name, implicit_params, :void

		self.module_eval <<-code
			def self.#{klass.downcase}_alloc
				FFI::MemoryPointer.new(:pointer, #{size})
			end

			def self.#{klass.downcase}_new *args
				instance = #{klass.downcase}_alloc
				#{klass.downcase}_ctor(instance, *args)
				instance
			end
		code
	end

	def attach_method klass, name, params, returns, mangled_name=nil
		mangled_name ||= FFI::Cpp::Manglers::GCC4X.mangle_method klass, name, params
		implicit_params = [:pointer] + params

		attach_c_function "#{klass.downcase}_#{name}", mangled_name, implicit_params, returns
	end
end