CXX:=clang++
CXXFLAGS:=-std=c++17 -Wall -Wextra

HEADERS:=$(wildcard include/cyfre/*)
SRC:=$(wildcard src/cyfre/*)

ifeq ($(OS), Linux)
CXXFLAGS+=-fsanitize=address
endif

test: test/test.out
	@./test/test.out

test/test.out: test/tests.cpp $(HEADERS) $(SRC)
	$(CXX) $(CXXFLAGS) test/tests.cpp -o test/test.out -fsanitize=address

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