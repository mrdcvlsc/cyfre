CC=g++
CFLAGS= -I ./include -c -Wall
SRC = ./src/
OUT = ./obj

$(OUT)%.obj:$(SRC)%.cpp Makefile
	$(CC) $(CFLAGS)