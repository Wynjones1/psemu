#export CXX=clang++-3.8
COVERAGE ?= No
all:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. -DCOVERAGE=$(COVERAGE)
	cd build && cmake --build . -- -j5

clean:
	rm -Rf build

testv: all
	- cd  build && ctest . -V

test: all
	- cd  build && ctest .

coverage: test
	lcov -c -d build/src -o build/coverage.info -b ./ --no-external
	genhtml build/coverage.info -o build/coverage --branch-coverage --demangle-cpp
