.PHONY: all

all:
	mkdir -p cmake-build-debug
	cd cmake-build-debug && cmake .. && make

clean:
	rm -rf cmake-build-debug
	rm BrickBreaker