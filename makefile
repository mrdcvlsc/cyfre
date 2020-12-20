CXX=g++

FINALIZE=-static-libgcc -static-libstdc++ -c
DEVELOPMENT=-Wall -c

CXXFLAGS=-I ./include $(DEVELOPMENT)
OBJ=obj/*.o
SRC=./src/
OUT=./obj/

all: test

test: lib cyfre.lib main.cpp
	@echo "Compiling Sample Program"
	@g++ -I ./include -o main.exe main.cpp cyfre.lib
	@echo "Compiled, running Sample program"
	@./main.exe

lib: library
	@echo $(OBJ)

library: $(OUT)column_operations.o $(OUT)row_operations.o $(OUT)algorithms.o $(OUT)arithmetic_operators.o $(OUT)comparison_operators.o $(OUT)constructors.o $(OUT)io_operators.o $(OUT)maths.o $(OUT)array_matrix.o
	@echo "building single static library : cyfre.lib"
	@ar rvs cyfre.lib $(OUT)*.o

$(OUT)row_operations.o: $(SRC)row_operations.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)row_operations.cpp -o obj/row_operations.o

$(OUT)column_operations.o: $(SRC)column_operations.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)column_operations.cpp -o obj/column_operations.o

$(OUT)algorithms.o: $(SRC)algorithms.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)algorithms.cpp -o obj/algorithms.o

$(OUT)arithmetic_operators.o: $(SRC)arithmetic_operators.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)arithmetic_operators.cpp -o obj/arithmetic_operators.o

$(OUT)comparison_operators.o: $(SRC)comparison_operators.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)comparison_operators.cpp -o obj/comparison_operators.o

$(OUT)constructors.o: $(SRC)constructors.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)constructors.cpp -o obj/constructors.o
	
$(OUT)io_operators.o: $(SRC)io_operators.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)io_operators.cpp -o obj/io_operators.o

$(OUT)maths.o: $(SRC)maths.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)maths.cpp -o obj/maths.o

$(OUT)array_matrix.o: $(SRC)array_matrix.cpp
	@echo "compiling source code to object file..."
	@$(CXX) $(CXXFLAGS) $(SRC)array_matrix.cpp -o obj/array_matrix.o




