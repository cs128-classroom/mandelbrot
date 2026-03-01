CXX=clang++
CC=clang
INCLUDES=-Iincludes/

# this sets different clang-tidy rules for the imported c code
THIRD_PARTY_SUPPRESS=-Wno-gnu-anonymous-struct -Wno-nested-anon-types

CXXFLAGS=-std=c++20 -O0 -gdwarf-4 -Wall -Wextra -Werror -pedantic \
        -fsanitize=address,undefined,implicit-conversion,local-bounds \
        -fno-omit-frame-pointer -fno-optimize-sibling-calls \
        -fsanitize-address-use-after-return=always \
        -Wno-error=unused-parameter \
        $(THIRD_PARTY_SUPPRESS) $(INCLUDES)

# compiles uselibpng as C (and allow gnu since the header uses anon structs)
USLIBPNG_CFLAGS=-std=gnu11 -O0 -gdwarf-4 -Wall -Wextra -pedantic \
                -Wno-gnu-anonymous-struct -Wno-nested-anon-types \
                $(INCLUDES)

LIBS=-lpng -lz

exec: bin/exec
tests: bin/tests

bin/uselibpng.o: ./src/uselibpng.c ./includes/uselibpng.h
	@mkdir -p bin
	$(CC) $(USLIBPNG_CFLAGS) -c ./src/uselibpng.c -o $@

bin/exec: ./includes/complex.hpp ./includes/mandelbrot.hpp \
          ./src/complex.cc ./src/mandelbrot.cc ./src/driver.cc ./src/color.cc ./includes/color.hpp bin/uselibpng.o
	$(CXX) $(CXXFLAGS) ./src/driver.cc ./src/complex.cc ./src/color.cc ./src/mandelbrot.cc bin/uselibpng.o -o $@ -lpng -lz

bin/tests: ./includes/complex.hpp ./includes/mandelbrot.hpp ./tests/grader_support.hpp ./tests/grader_support.hpp \
            ./src/complex.cc ./src/mandelbrot.cc ./src/color.cc ./includes/color.hpp ./tests/tests.cc bin/uselibpng.o
	$(CXX) -std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -pedantic \
	       -Wno-gnu-anonymous-struct -Wno-nested-anon-types \
	       ./tests/tests.cc ./src/complex.cc ./src/mandelbrot.cc ./src/color.cc bin/uselibpng.o -o $@ -lpng -lz

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/*