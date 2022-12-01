CC:=g++
SRC := cyfre/test
CXXFLAGS := -std=c++17 -Wall -Wextra -Og -g
THREADED := -march=native -DOMPTHREAD -fopenmp

ifeq ($(OS), Linux)
CPPFLAGS += -fsanitize=address
endif

test:
	$(CC) $(CXXFLAGS) $(SRC)/test.cpp -o $(SRC)/test.out
	$(SRC)/test.out
	$(MAKE) clean
	$(CC) $(CXXFLAGS) $(THREADED) $(SRC)/test.cpp -o $(SRC)/test.out
	$(SRC)/test.out
	$(MAKE) clean

clean:
	@echo "main makefile - clean"
	@rm $(SRC)/test.out

install:
	@ln -s $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/cyfre /usr/local/include/

uninstall:
	@unlink /usr/local/include/cyfre

style:
	@clang-format -i -style=file *.cpp *.hpp tests/*.hpp tests/*.cpp benchmark/*.cpp