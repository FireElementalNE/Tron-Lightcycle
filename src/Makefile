CC=g++
CFLAGS=-g -Wall
GLFLAGS=-lGL -lGLU -lglut
OBJ=lightCycle.o
all: main
main: main.cpp $(OBJ)
	$(CC) -o main main.cpp $(OBJ) $(CFLAGS) $(GLFLAGS)
lightCycle.o: lightCycle.cpp
	$(CC) -c -o lightCycle.o lightCycle.cpp $(CFLAGS) $(GLFLAGS)
clean:
	rm -rf main *.o
