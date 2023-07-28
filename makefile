OS:=$(shell uname)
ARCH:=$(shell uname -p)
CC:=clang
CXX:=clang++

.PHONY: test info clean style

test:
	$(MAKE) -C test test

clean:
	$(MAKE) -C test clean

info:
	@echo Compiling test programs...
	@echo Operating System : $(OS)
	@echo Architecture     : $(ARCH)
	@echo
	@echo C++ Compiler     : $(CXX)
	@echo C Compiler       : $(CC)
	@$(CC) --version
	@echo

style:
	@clang-format -i -style=file \
	include/cyfre/*.hpp include/cyfre/*/*.hpp include/cyfre/*/*/*.hpp include/cyfre/*/*/*/*.hpp \
	src/cyfre/*.cpp src/cyfre/*/*.cpp src/cyfre/*/*/*.cpp src/cyfre/*/*/*/*.cpp \
	test/*.cpp