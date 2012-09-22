# FFI extension to allow calling into C++ code.
# 
# FFIPP (Foreign Function Interface Plus Plus) handles the name mangling and
# calling convention issues that come up when calling compiled C++ code. This
# allows for pure-Ruby bridges to C++ libraries like openFrameworks without
# clunky C shims or generated wrappers. The goal is to be able to use
# unmodified C++ shared objects as if they were written in C.
# 
# It supports normal functions, instance methods, and class construtcors.
# Still missing are class destructors, templates, std::strings, and others.
# GCC 4.x only at the moment.
module FFI::Cpp
  # Contains manglers for different compiler/versions
  module Manglers
    # Mangler for GCC 4.x
    # @see http://mentorembedded.github.com/cxx-abi/abi.html#mangling
    class GCC4X
      MangledTypes = {
        stdstring:      "Ss",
        void:         "v",
        wchar_t:      "w",
        bool:         "b",
        char:         "c",
        signed_char:    "a",
        unsigned_char:    "h",
        short:        "s",
        unsigned_short:   "t",
        int:        "i",
        unsigned_int:     "j",
        long:         "l",
        unsigned_long:    "m",
        long_long:      "x",
        ___int64:       "x",
        unsigned_long_long: "y",
        ___int64:       "y",
        __int128:       "n",
        unsigned___int128:  "o",
        float:        "f",
        double:       "d",
        long_double:    "e",
        ___float80:     "e",
        __float128:     "g",
        ellipsis:       "z",
        ieee_754r_64:     "Dd",
        ieee_754r_128:    "De",
        ieee_754r_32:     "Df",
        ieee_754r_16:     "Dh",
        char32_t:       "Di",
        char16_t:       "Ds",
        auto:         "Da",
        stdnullptr_t:     "Dn"
      }

      # Mangle a type
      # 
      # Used by {GCC4X.mangle_function} and {GCC4X.mangle_method} to
      # generate signatures out of arrays of symbols.
      # 
      # @example
      #   [:int, :int, :float].map { |t| GCC4X.mangle_type(t) }.join # => "iif"
      # 
      # @param [Symbol] t Type to mangle. One of the symbols in
      #   {MangledTypes}
      # @return [String] mangled representation of +t+
      def self.mangle_type t
        if MangledTypes.has_key? t
          MangledTypes[t] 
        # elsif FFI.find_type(t) == :pointer # TODO Fix kludge!
        else
          "P#{t.length}#{t}"
        end
      end

      # Mangle an identifier, generally a method or class name
      # 
      # @example
      #   GCC4X.mangle_identifier "ofCircle" # => "8ofCircle"
      # 
      # @example
      #   GCC4X.mangle_identifier :ctor # => "C1"
      # 
      # @param [#to_s, :ctor, :dtor] i the identifier to mangle.
      #   Construtcors and destructors don't have identifiers, so use
      #   :ctor or :dtor instead
      # @return [String] mangled representation of i
      def self.mangle_identifier i
        case i
        when :ctor; "C1"
        when :dtor; "D1"
        else; "#{i.size}#{i}"
        end
      end

      # Mangle a top level C++ function name
      # 
      # The resulting name can be succesfully used to attach to
      # functions in a C++ shared object
      # 
      # @example
      #   GCC4X.mangle_function :ofCircle, [:float, :float, :float] # => "_Z8ofCirclefff"
      # 
      # @example
      #   GCC4X.mangle_function :ofNoFill, [] # => "_Z6ofFillv"
      # 
      # @param name [#to_s] name the name of the function
      # @param params [Array<Symbol>] params the types and order of parameters
      #   the function takes, or an empty array if function doesnt take
      #   parameters.
      # 
      # @return [String] mangled function name
      def self.mangle_function name, params
        name = mangle_identifier name
        params = [:void] if params.empty?

        "_Z#{name}#{params.map { |p| mangle_type(p) }.join}"
      end

      # Mangle an instance method name
      # 
      # @param klass [#to_s] the object's class
      # @param klass [#to_s] the object's class
      # 
      # @return [String] mangled instance method name
      def self.mangle_method klass, method, params
        klass = "#{klass.size}#{klass}"
        method = mangle_identifier method
        params = [:void] if params.empty?

        "_ZN#{klass}#{method}E#{params.map { |p| mangle_type(p) }.join}"
      end

    end
  end

  # C++ Library support
  module Library
    include FFI::Library

    # support cpp linkage in attach_function
    alias :attach_c_function :attach_function

    # Attatch top level C/C++ function to this module
    # 
    # @overload attach_function name, params, returns, options={}
    #   This variant will match the Ruby name to the C/C++ name
    #   @param name [Symbol] the name of the function
    #   @param params [Array<Symbol>] array of symbols indicating parameter 
    #     type
    #   @param returns [Symbol] symbol indicating return type
    #   @opthash foo
    # 
    # @overload attach_function ruby_name, c_name, params, returns, options={}
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

    # Attatch constructor for class +klass+ to module
    # 
    # @example
    #   module Native
    #     attach_constructor :Widget, 682, [:float, :float, :int]
    #   end
    def attach_constructor klass, size, params, mangled_name=nil
      mangled_name ||= FFI::Cpp::Manglers::GCC4X.mangle_method klass, :ctor, params
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
end