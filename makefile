
clean: 
	rm -rf build

build: vape/*
	mkdir -p build
	cd build; cmake -G"Eclipse CDT4 - Unix Makefiles" ../arduino-cmake/

upload: build
	cd build; make upload

monitor: 
	${PUTTY_DIR}/putty.exe -serial COM8 -sercfg 9600,8,n,1,X
