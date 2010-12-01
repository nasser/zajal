ZAJAL_DIR = src
BUILD_DIR = build
BIN_DIR = bin
BINARY = $(BIN_DIR)/zajal


### 
CC = gcc-4.0
CXX = g++-4.0
CXXFLAGS = -arch i386 -g -DHAVE_STRUCT_TIMEZONE -DHAVE_STRUCT_TIMESPEC


### openFrameworks
OF_DIR = lib/openframeworks
OF_LIB = $(OF_DIR)/libof.a
OF_INCLUDE_DIR = $(OF_DIR)/include
OF_FRAMEWORKS = $(addprefix -framework ,OpenGL Glut QuickTime CoreAudio Carbon)
OF_INCLUDES = $(addprefix -idirafter ,$(shell find $(OF_DIR)/include -type d))


### ruby
RUBY_DIR = lib/ruby
RUBY_LIB = $(RUBY_DIR)/libruby.a
RUBY_INCLUDE_DIR = $(RUBY_DIR)/include
RUBY_INCLUDES = $(addprefix -I ,$(shell find $(RUBY_DIR)/include -type d))


### zajal interperter
ZAJAL_GIT_BRANCH = $(shell git branch | sed -e '/^[^\*]/d' -e 's/\* //')
ZAJAL_GIT_HASH = $(shell git show-ref $(ZAJAL_GIT_BRANCH) --hash --heads)
ZAJAL_GIT_SHORT_HASH = $(shell git show-ref $(ZAJAL_GIT_BRANCH) --hash=8 --heads)

ZAJAL_INCLUDES = -I$(ZAJAL_DIR)
ZAJAL_SRC = $(shell find -E $(ZAJAL_DIR) -regex ".*\.c(pp)?$$")
ZAJAL_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(notdir $(ZAJAL_SRC))))
ZAJAL_LIBRARIES = $(OF_LIB) $(RUBY_LIB)


.PHONY: all clean $(BUILD_DIR)/version.c.o

all: $(BINARY)
	@echo
	@echo "Built Zajal $(ZAJAL_GIT_SHORT_HASH) to $(BINARY)"

$(BINARY): $(ZAJAL_OBJ)
	@echo -n "Making binary..."
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) $(OF_INCLUDES) $(RUBY_INCLUDES) $(ZAJAL_INCLUDES) $(OF_FRAMEWORKS) $(ZAJAL_LIBRARIES) $(ZAJAL_OBJ) -o $(BINARY)
	@echo "OK"

$(BUILD_DIR)/%.cpp.o: $(ZAJAL_DIR)/%.cpp
	@echo -n "Building $<..."
	@$(CXX) $(CXXFLAGS) $(OF_INCLUDES) $(RUBY_INCLUDES) $(ZAJAL_INCLUDES) -c -o $@ $<
	@echo "OK"

$(BUILD_DIR)/%.c.o: $(ZAJAL_DIR)/%.c
	@echo -n "Building $<..."
	@$(CXX) $(CXXFLAGS) $(OF_INCLUDES) $(RUBY_INCLUDES) $(ZAJAL_INCLUDES) -c -o $@ $<
	@echo "OK"

$(BUILD_DIR)/version.c.o: $(ZAJAL_DIR)/version.c
	@echo -n "Building in version information..."
	@cp $< $<.bak
	@sed -i '' -Ee 's/zajal_hash\[\] = "[^"]*"/zajal_hash[] = "$(ZAJAL_GIT_HASH)"/' $<
	@sed -i '' -Ee 's/zajal_short_hash\[\] = "[^"]*"/zajal_short_hash[] = "$(ZAJAL_GIT_SHORT_HASH)"/' $<
	@sed -i '' -Ee 's/zajal_branch\[\] = "[^"]*"/zajal_branch[] = "$(ZAJAL_GIT_BRANCH)"/' $<
	@$(CXX) $(CXXFLAGS) $(OF_INCLUDES) $(RUBY_INCLUDES) $(ZAJAL_INCLUDES) -c -o $@ $<
	@mv $<.bak $<
	@echo "OK"

clean:
	@echo -n "Cleaning..."
	@rm $(BUILD_DIR)/*
	@echo "OK"