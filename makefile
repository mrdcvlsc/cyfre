CPPFLAGS := -O3 -march=native -DOMPTHREAD -fopenmp
CXXFLAGS := -std=c++11

OS := $(shell uname)

ifeq ($(OS), Linux)
CPPFLAGS += -fsanitize=address
endif

SRC := test
SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ := $(patsubst $(SRC)/%.cpp,$(SRC)/%.out,$(SRC_FILES))

# -------------------------- run test programs ---------------------------

check: $(OBJ)
	@echo "running test programs"
	@for o in $(SRC)/*.out; do ./$$o; done

# -------------------------- test program compilation ---------------------------

$(SRC)/%.out: $(SRC)/%.cpp
	@echo "compiling test program"
	@g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

clean:
	rm test/test*.out