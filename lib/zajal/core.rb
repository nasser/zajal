# Load openFrameworks' binary dependancies into the process
%w[PocoFoundation PocoNet PocoXML PocoUtil glew tess freeimage freetype].each do |libname|
  FFI::DynamicLibrary.open_library File.expand_path("core/lib/#{libname}.so", File.dirname(__FILE__)), FFI::DynamicLibrary::RTLD_LAZY | FFI::DynamicLibrary::RTLD_GLOBAL
end

require "zajal/core/app"
require "zajal/core/graphics"
require "zajal/core/fbo"
require "zajal/core/shader"
require "zajal/core/pixels"
require "zajal/core/images"
require "zajal/core/mathematics"
require "zajal/core/time"
require "zajal/core/typography"
require "zajal/core/color"

require "zajal/core/sketch"
require "zajal/core/thanks"