all:
	mkdir -p build
	cd build && cmake ..

clean:
	rm -Rf build
