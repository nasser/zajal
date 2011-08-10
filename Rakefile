require "rakelib/helpers.rb"

ZAJAL_DIR = "src"
BUILD_DIR = "build"
BIN_DIR = "bin"
BINARY = "#{BIN_DIR}/zajal"
LIBRARY = "#{BIN_DIR}/libzajal.a"
CLI_FRONTEND_DIR = "frontends/cli"

DEFINES = PrefixArray.new "-D"
DEFINES << "HAVE_STRUCT_TIMEZONE"
DEFINES << "HAVE_STRUCT_TIMESPEC"
DEFINES << "OF_SOUND_PLAYER_QUICKTIME"

CC = "gcc"
CXX = "g++"
CXXFLAGS = "-arch i386 -g #{DEFINES}"
GIT = "git"

# openFrameworks
OF_DIR = "lib/openframeworks"
OF_LIB = "#{OF_DIR}/libof.a"
OF_INCLUDE_DIR = "#{OF_DIR}/include"
OF_INCLUDES = PrefixArray.new "-idirafter ", Dir["#{OF_INCLUDE_DIR}/**/*/"]
OF_FRAMEWORKS = PrefixArray.new "-framework ", %w[OpenGL Glut QuickTime CoreAudio Carbon]

# ruby
RUBY_DIR = "lib/ruby"
RUBY_LIB = "#{RUBY_DIR}/libruby.a"
RUBY_INCLUDE_DIR = "#{RUBY_DIR}/include"
RUBY_INCLUDES = PrefixArray.new "-I", Dir["#{RUBY_INCLUDE_DIR}/**/*/"]
RUBY_INCLUDES << RUBY_INCLUDE_DIR

# zajal interperter
ZAJAL_GIT_BRANCH = `#{GIT} name-rev --name-only HEAD`
ZAJAL_GIT_HASH = `#{GIT} log -1 --pretty=format:%H`
ZAJAL_GIT_SHORT_HASH = `#{GIT} log -1 --pretty=format:%h`

ZAJAL_INCLUDES = "-I#{ZAJAL_DIR}"
ZAJAL_SRC = Dir["#{ZAJAL_DIR}/*.cc"] + Dir["#{CLI_FRONTEND_DIR}/*.cc"]
ZAJAL_OBJ = ZAJAL_SRC.map { |f| f.sub("cc", "o") }
ZAJAL_LIBRARIES = "#{OF_LIB} #{RUBY_LIB}"

task :default => "cli:bin"