CXXFLAGS:=-std=c++20 -Wall -Wextra
LINKING:=

HEADERS:=$(wildcard ../include/cyfre/*)
SRC:=$(wildcard ../src/cyfre/*)
TEST_EXECUTABLES:=$(subst .cpp,.out,$(wildcard *.cpp))

ifeq ($(CXX), clang++)
CXXFLAGS+=-fsanitize=address
endif

.PHONY: test clean

# alternative for the above ifeq
# CXXFLAGS+=$(and $(findstring clang++, $(CXX)), $(findstring clang, $(CC)), -fsanitize=address)

test: $(TEST_EXECUTABLES)
	@echo dep = $^
	$(foreach TEST_PROGRAM, $^,\
		./$(TEST_PROGRAM) ;\
	)

$(TEST_EXECUTABLES): %.out: %.cpp $(HEADERS) $(SRC)
	$(strip $(CXX) $(LINKING) $(CXXFLAGS) $< -o $@)

clean:
	@echo "main makefile - clean"
	@rm *.out