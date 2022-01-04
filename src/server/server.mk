SOURCES_DIRECTORY = ./lib/sources
INCLUDES_SERVER = -I$(BASE_ROOT)/src/server/lib/includes
INCLUDES_SHARED = -I$(BASE_ROOT)/src/shared/lib/includes
BUILD_DIRECTORY = $(BASE_ROOT)/build/server
CPP_SOURCES = $(shell cd $(SOURCES_DIRECTORY); find . -name '*.cpp')
OBJECT_SOURCES = $(subst ./,$(BUILD_DIRECTORY)/, $(patsubst %.cpp,%.o,$(CPP_SOURCES)))

all: directories build

directories:
	@mkdir -p $(BUILD_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/commands
	@mkdir -p $(BUILD_DIRECTORY)/models

build: $(OBJECT_SOURCES)
	@${AR} rvs $(BASE_ROOT)/build/libs/server.a $^

$(BUILD_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.cpp
	@${COMPILER} -o $@ $(INCLUDES_SERVER) $(INCLUDES_SHARED) $(C_FLAGS) -c $<

cleanup:
	@rm -rd $(BUILD_DIRECTORY)