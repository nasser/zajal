module FFI::Cpp
  module Std
    extend FFI::Cpp::Library

    ffi_lib_flags :global
    ffi_lib FFI::CURRENT_PROCESS

    # TODO autogenerate std::string constructor mangled name
    # _Z         N      Ss          C1          E        PKc         RKSa                 Ic     E
    # Start name Nested std::string Constructor End name const char* const &std::allocator<char> End all
    attach_constructor :string, 8, [:string, :pointer], :_ZNSsC1EPKcRKSaIcE
  end
end

class String
  # @todo Should this be in a separate class, i.e. FFI::Cpp::Std::String?
  # @note #to_ptr won't be called by FFI automatically because NativeFunction::call
  #   checks for String type before it checks responses to #to_ptr, and will try
  #   to pass the string as a c-string. 
  # 
  # @see https://github.com/rubinius/rubinius/blob/master/vm/builtin/nativefunction.cpp
  def to_ptr
    FFI::Cpp::Std::string_new self, nil
  end
end