# setting the compiler
COMPILER = g++

# special libs for each component
LIBS_SERVER = $(shell find server/lib -name '*.cpp')
LIBS_CLIENT = $(shell find client/lib -name '*.cpp')

# the shared library
SHARED_LIB =  $(shell find shared/lib -name '*.cpp')

# flags for libraries that we include
CRYPTO_FLAG = -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto

# flags for compiler
C_FLAGS = -Wall -Wextra -pedantic -std=c++0x 

server_s: 
	@mkdir -p build
	${COMPILER} -o build/$@ ${C_FLAGS} ${CRYPTO_FLAG} ${LIBS_SERVER} ${SHARED_LIB} ${SERVER_SOURCES} server/main.cpp
clean:
	rm -f *compiled