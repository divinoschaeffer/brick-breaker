.PHONY: all

all:
	mkdir -p cmake-build-debug
	cd cmake-build-debug && cmake .. && make
