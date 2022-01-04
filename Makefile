# setting the compiler
COMPILER = g++
BASE_ROOT = $(shell pwd)

# the root directory
ROOT_DIR = ./src
# special libs for each component
SERVER_LIB = $(shell find src/server/lib -name '*.cpp')
CLIENT_LIB = $(shell find src/client/lib -name '*.cpp')

# the shared library
SHARED_LIB =  $(shell find src/shared/lib -name '*.cpp')

#FLAGS
CLIENT_FLAGS = -D "__CLIENT__"
SERVER_FLAGS = -D "__SERVER__" -lsqlite3  -lpthread

# includes folder
INCLUDES_SERVER = -I${ROOT_DIR}/server/lib/includes
INCLUDES_CLIENT = -I${ROOT_DIR}/client/lib/includes
INCLUDES_SHARED = -I${ROOT_DIR}/shared/lib/includes

# flags for libraries that we include
CRYPTO_FLAG = -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto

# flags for compiler
C_FLAGS = -Wextra -pedantic -std=c++0x
export C_FLAGS CRYPTO_FLAG COMPILER BASE_ROOT

all: client server

server: shared


shared: 
	@$(MAKE) -C src/shared -f shared.mk all