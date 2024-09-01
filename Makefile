.PHONY: clean build run install

clean:
	rm -rf build/
build:
	#This is not meant to be actually run as a makefile, run these commands as needed directly
	rm -rf build/
	mkdir -p build
	cd build
	cmake ..
	make
	cd ..
run:
	./build/app.exe
install:
	sudo apt-get update
	sudo apt-get -y upgrade
	sudo apt-get install \
		vulkan-tools \
		libvulkan-dev \
		vulkan-validationlayers \
		spirv-tools \
		libglfw3-dev \
		libglm-dev 
	# This is from here https://github.com/google/shaderc/blob/main/downloads.md
	sudo cp lib/glslc /usr/local/bin/