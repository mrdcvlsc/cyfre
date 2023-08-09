HEADERS:=$(wildcard ../include/cyfre/*)
SRC:=$(wildcard ../src/cyfre/*)
TEST_EXECUTABLES:=$(subst .cpp,.out,$(wildcard *.cpp))
LINKING:=

CXXFLAGS:=-Wall -Wextra -g3 -std=c++20

ifeq ($(CXX), clang++)
CXXFLAGS+=-fsanitize=address
endif

# alternative for the above ifeq
# CXXFLAGS+=$(and $(findstring clang++, $(CXX)), $(findstring clang, $(CC)), -fsanitize=address)

.PHONY: test clean

test: $(TEST_EXECUTABLES)
	$(foreach TEST_PROGRAM, $^,\
		./$(TEST_PROGRAM) ;\
	)

$(TEST_EXECUTABLES): %.out: %.cpp $(HEADERS) $(SRC)
	$(strip $(CXX) $(LINKING) $(CXXFLAGS) $< -o $@)

clean:
	@echo "main makefile - clean"
	@rm *.out