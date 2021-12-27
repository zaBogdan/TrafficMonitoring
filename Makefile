# setting the compiler
COMPILER = g++

# special libs for each component
LIBS_SERVER = $(shell find server/lib -name '*.cpp')
LIBS_CLIENT = $(shell find client/lib -name '*.cpp')

# the shared library
SHARED_LIB =  $(shell find shared/lib -name '*.cpp')

#FLAGS
CLIENT_FLAGS = -D "__CLIENT__"
SERVER_FLAGS = -D "__SERVER__" -lsqlite3

# includes folder
INCLUDES_SERVER = -I./server/lib/includes
INCLUDES_CLIENT = -I./client/lib/includes
INCLUDES_SHARED = -I./shared/lib/includes

# flags for libraries that we include
CRYPTO_FLAG = -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto

# flags for compiler
C_FLAGS = -Wextra -pedantic -std=c++0x  -lpthread

all: bserver bclient

bserver: 
	@mkdir -p build
	${COMPILER} -o build/$@ ${C_FLAGS} ${SERVER_FLAGS} ${CRYPTO_FLAG} ${INCLUDES_SHARED} ${INCLUDES_SERVER} ${LIBS_SERVER} ${SHARED_LIB} server/server.cpp

bclient: 
	@mkdir -p build
	${COMPILER} -o build/$@ ${C_FLAGS} ${CLIENT_FLAGS} ${CRYPTO_FLAG} ${INCLUDES_SHARED} ${INCLUDES_CLIENT} ${LIBS_CLIENT} ${SHARED_LIB} client/main.cpp

clean:
	rm -rd build