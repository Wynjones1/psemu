#export CXX=clang++-3.8
all:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
	cd build && cmake --build . -- -j5

release:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=Release ..
	cd build && cmake --build . -- -j5

clean:
	rm -Rf build

testv: all
	cd  build && ctest . -V

test: all
	cd  build && ctest .
