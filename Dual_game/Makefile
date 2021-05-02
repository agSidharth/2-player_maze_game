CC = g++
CFLAG = -w
SDLFLAG = -lSDL2 -lSDL2_image -lSDL2_ttf


OBJ_F = game.hpp player.hpp

all: $(OBJ_F) Main.cpp
	$(CC) Main.cpp $(CFLAG) $(SDLFLAG) -o game

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out
	rm -f game

