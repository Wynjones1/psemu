all:
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . -- -j5

clean:
	rm -Rf build

test: all
	cd  build && ctest .
