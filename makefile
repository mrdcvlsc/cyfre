OS:=$(shell uname)
ARCH:=$(shell uname -p)

CC:=clang
CXX:=clang++

CXXFLAGS:=-std=c++20 -Wall -Wextra
LINKING:=

HEADERS:=$(wildcard include/cyfre/*)
SRC:=$(wildcard src/cyfre/*)

ifeq ($(CXX), clang++)
CXXFLAGS+=-fsanitize=address
endif

# alternative for the above ifeq
# CXXFLAGS+=$(and $(findstring clang++, $(CXX)), $(findstring clang, $(CC)), -fsanitize=address)

test: test/test.out
	@./test/test.out

test/test.out: test/tests.cpp $(HEADERS) $(SRC)
	@echo Compiling test programs...
	@echo Operating System : $(OS)
	@echo Architecture     : $(ARCH)
	@echo C Compiler       : $(CC)
	@echo C++ Compiler     : $(CXX)
	$(CXX) $(LINKING) $(CXXFLAGS) test/tests.cpp -o test/test.out

clean:
	@echo "main makefile - clean"
	@rm $(SRC)/test.out

install:
	@ln -s $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/cyfre /usr/local/include/

uninstall:
	@unlink /usr/local/include/cyfre

style:
	@clang-format -i -style=file \
	cyfre/*.*pp \
	cyfre/classes/*.*pp cyfre/helpers/*.*pp \
	cyfre/matrix-elementary-operation/*.*pp \
	cyfre/matrix-matrix/*.*pp \
	cyfre/matrix-scalar/*.*pp \
	cyfre/methods/*.*pp \
	cyfre/shaping/*.*pp \
	cyfre/statistics/*.*pp \
	cyfre/transform/*.*pp \
	cyfre/test/*.*pp \
	include/cyfre/*.hpp \
	src/cyfre/*.cpp \
	test/*.cpp