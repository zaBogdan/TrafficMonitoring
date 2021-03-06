
SOURCES_DIRECTORY = ./lib/sources

INCLUDES_CLIENT = -I$(BASE_ROOT)/src/client/lib/includes
INCLUDES_SHARED = -I$(BASE_ROOT)/src/shared/lib/includes

BUILD_DIRECTORY = $(BASE_ROOT)/build/client
CPP_SOURCES = $(shell cd $(SOURCES_DIRECTORY); find . -name '*.cpp')
OBJECT_SOURCES = $(subst ./,$(BUILD_DIRECTORY)/, $(patsubst %.cpp,%.o,$(CPP_SOURCES)))

all: directories build

directories:
	@mkdir -p $(BUILD_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/commands
	@mkdir -p $(BUILD_DIRECTORY)/sensors

build: $(OBJECT_SOURCES)
	@${AR} rs $(BASE_ROOT)/build/libs/client.a $^

$(BUILD_DIRECTORY)/%.o: $(SOURCES_DIRECTORY)/%.cpp
	@${COMPILER} -o $@ $(INCLUDES_CLIENT) $(INCLUDES_SHARED) $(C_FLAGS) -c $<

cleanup:
	@rm -rd $(BUILD_DIRECTORY)