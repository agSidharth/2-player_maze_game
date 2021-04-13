CC = g++
CFLAG = -w
SDLFLAG = -lSDL2

OBJ_F = game.cpp
OBJ_O = game.o

all:$(OBJ_F)
	$(CC) $(OBJS) $(CFLAG) $(SDLFLAG) -o $(OBJ_O)

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out

