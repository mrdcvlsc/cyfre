CPPFLAGS := -O3 -march=native -DOMPTHREAD -fopenmp
CXXFLAGS := -std=c++11

OS := $(shell uname)

ifeq ($(OS), Linux)
CPPFLAGS += -fsanitize=address
endif

SRC := test
SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ := $(patsubst $(SRC)/%.cpp,$(SRC)/%.o,$(SRC_FILES))

# -------------------------- run test programs ---------------------------

check: $(OBJ)
	@echo "running test programs"
	@for o in $(SRC)/*.o; do ./$$o; done

# -------------------------- test program compilation ---------------------------

$(SRC)/%.o: $(SRC)/%.cpp
	@echo "compiling test programs"
	@g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $<
