# Load openFrameworks' binary dependancies into the process
%w[PocoFoundation PocoNet PocoXML PocoUtil glew tess freeimage freetype].each do |libname|
  FFI::DynamicLibrary.open_library "lib/core/lib/#{libname}.so", FFI::DynamicLibrary::RTLD_LAZY | FFI::DynamicLibrary::RTLD_GLOBAL
end

require_relative "core/graphics"
require_relative "core/typography"
require_relative "core/color"
require_relative "core/mathematics"
require_relative "core/time"

require_relative "core/version"
require_relative "core/sketch"
require_relative "core/thanks"