# setting the compiler
COMPILER = g++

# the root directory
BASE_ROOT = $(shell pwd)
ROOT_DIR = ./src

#FLAGS
CLIENT_FLAGS = -D "__CLIENT__"
SERVER_FLAGS = -D "__SERVER__" -lsqlite3  -lpthread

# includes folder
INCLUDES_SERVER = -I${ROOT_DIR}/server/lib/includes
INCLUDES_CLIENT = -I${ROOT_DIR}/client/lib/includes
INCLUDES_SHARED = -I${ROOT_DIR}/shared/lib/includes

# build locations
BUILD_SERVER = $(BASE_ROOT)/build/libs/SERVER.a
BUILD_CLIENT = $(BASE_ROOT)/build/libs/client.a 
BUILD_SHARED = $(BASE_ROOT)/build/libs/shared.a

# flags for libraries that we include
CRYPTO_FLAG = -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto

# flags for compiler
C_FLAGS = -Wextra -pedantic -std=c++0x
export C_FLAGS CRYPTO_FLAG COMPILER BASE_ROOT

all: directories client server

directories:
	@mkdir -p $(BASE_ROOT)/build
	@mkdir -p $(BASE_ROOT)/build/client
	@mkdir -p $(BASE_ROOT)/build/server
	@mkdir -p $(BASE_ROOT)/build/shared
	@mkdir -p $(BASE_ROOT)/build/libs

client: directories shared
	@$(MAKE) -C src/client -f client.mk all
	@${COMPILER} -o $(BASE_ROOT)/build/bclient ${C_FLAGS} ${CLIENT_FLAGS} ${CRYPTO_FLAG} $(INCLUDES_CLIENT) $(INCLUDES_SHARED) $(BUILD_CLIENT) $(BUILD_SHARED) src/client/main.cpp

server: directories shared
	@$(MAKE) -C src/server -f server.mk all
	@${COMPILER} -o $(BASE_ROOT)/build/bserver ${C_FLAGS} ${SERVER_FLAGS} ${CRYPTO_FLAG} $(INCLUDES_SERVER) $(INCLUDES_SHARED) $(BUILD_SERVER) $(BUILD_SHARED) src/server/server.cpp

shared: directories
	@$(MAKE) -C src/shared -f shared.mk all

cleanup:
	rm -rd $(BASE_ROOT)/build 