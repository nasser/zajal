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
    module GCC4X
      MangledTypes = {
        string:              "PKc",
        stdstring:           "Ss",
        void:                "v",
        wchar_t:             "w",
        bool:                "b",
        char:                "c",
        signed_char:         "a",
        unsigned_char:       "h",
        short:               "s",
        unsigned_short:      "t",
        int:                 "i",
        unsigned_int:        "j",
        long:                "l",
        unsigned_long:       "m",
        long_long:           "x",
        ___int64:            "x",
        unsigned_long_long:  "y",
        ___int64:            "y",
        __int128:            "n",
        unsigned___int128:   "o",
        float:               "f",
        double:              "d",
        long_double:         "e",
        ___float80:          "e",
        __float128:          "g",
        ellipsis:            "z",
        ieee_754r_64:        "Dd",
        ieee_754r_128:       "De",
        ieee_754r_32:        "Df",
        ieee_754r_16:        "Dh",
        char32_t:            "Di",
        char16_t:            "Ds",
        auto:                "Da",
        stdnullptr_t:        "Dn"
      }

      FFI.add_typedef :pointer, :stdstring

      # Base class for mangled symbols, including types and identifiers
      class MangledSymbol
        def self.bool_attr *args
          args.each do |sym|
            self.module_eval <<-code
              def #{sym}; ret = self.dup; ret.instance_variable_set :@#{sym}, true; ret end
              def #{sym}?; @#{sym} end
            code
          end
        end

        def self.new *args
          if args.first.is_a? self
            args.first
          else
            super *args
          end
        end

        def self.ary ary
          ary.map { |a| self.new(a) }
        end

        # TODO dubious
        def to_s
          mangle
        end

        def to_sym
          @unmangled_symbol
        end

        def actually sym
          @unmangled_symbol = sym
          self
        end
      end

      # A mangled identifier, such as a method name
      class Identifier < MangledSymbol
        def initialize sym
          @mangled_identifier = case sym
          when :ctor; "C1"
          when :dtor; "D1"
          else; "#{sym.size}#{sym}"
          end
        end

        def mangle
          @mangled_identifier
        end
      end

      class Type < MangledSymbol
        bool_attr :const, :pointer, :reference

        def initialize sym
          @unmangled_symbol = sym
          @mangled_identifier = MangledTypes.has_key?(sym) ? MangledTypes[sym] : "#{sym.length}#{sym}"
        end

        def template *params
          @template = true
          @template_params = Type.ary(params)
          self
        end

        def template?
          @template
        end

        def mangle
          "#{'P' if pointer?}" +
          "#{'R' if reference?}" +
          "#{'K' if const?}" + 
          @mangled_identifier +
          "#{'I' + @template_params.map { |t| t.mangle }.join + 'E' if template?}"
        end
      end

      class Function < MangledSymbol
        def initialize name, params
          @name = name
          @params = params.empty? ? [Type.new(:void)] : params
        end

        def mangle
          "_Z#{@name.mangle}#{@params.map { |p| p.mangle }.join}"
        end
      end

      class Method < Function
        def initialize klass, name, params
          super name, params
          @klass = klass
        end

        def mangle
          "_ZN#{@klass.mangle}#{@name.mangle}E#{@params.map { |p| p.mangle }.join}"
        end
      end

      # Mangle a top level C++ function name
      # 
      # The resulting name can be succesfully used to attach to
      # functions in a C++ shared object
      # 
      # @example
      #   mangle_function :ofCircle, [:float, :float, :float] # => "_Z8ofCirclefff"
      # 
      # @example
      #   mangle_function :ofNoFill, [] # => "_Z6ofFillv"
      # 
      # @param name [#to_s] name the name of the function
      # @param params [Array<Symbol>] params the types and order of parameters
      #   the function takes, or an empty array if function doesnt take
      #   parameters.
      # 
      # @return [String] mangled function name
      def mangle_function name, params
        Function.new(Identifier.new(name), Type.ary(params)).to_s
      end

      # Mangle an instance method name
      # 
      # @param klass [#to_s] the object's class
      # @param klass [#to_s] the object's class
      # 
      # @return [String] mangled instance method name
      def mangle_method klass, name, params
        Method.new(Type.new(klass), Identifier.new(name), Type.ary(params)).to_s
      end
    end
  end

  # C++ Library support
  module Library
    include FFI::Library
    include FFI::Cpp::Manglers::GCC4X # TODO implement system to select correct mangler

    def type t
      Type.new(t)
    end

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
        mangled_name = mangle_function cname, params
        attach_c_function rbname, mangled_name, params.map { |p| p.to_sym }, returns
      end
    end

    # Attatch constructor for class +klass+ to module
    # 
    # @example
    #   module Native
    #     attach_constructor :Widget, 682, [:float, :float, :int]
    #   end
    def attach_constructor klass, size, params, mangled_name=nil
      mangled_name ||= mangle_method klass, :ctor, params
      implicit_params = [:pointer] + params

      attach_c_function "#{klass.to_sym.downcase}_ctor", mangled_name, implicit_params.map { |p| p.to_sym }, :void

      self.module_eval <<-code
        def self.#{klass.to_sym.downcase}_alloc
          FFI::MemoryPointer.new(:pointer, #{size})
        end

        def self.#{klass.to_sym.downcase}_new *args
          instance = #{klass.to_sym.downcase}_alloc
          #{klass.to_sym.downcase}_ctor(instance, *args)
          instance
        end
      code
    end

    def attach_method klass, name, params, returns, mangled_name=nil
      mangled_name ||= mangle_method klass, name, params
      implicit_params = [:pointer] + params

      attach_c_function "#{klass.to_sym.downcase}_#{name}", mangled_name, implicit_params.map { |p| p.to_sym }, returns
    end
  end
end