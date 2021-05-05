.PHONY:game
game: main.cpp
	g++ -o game main.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_mixer -lpthread -I. -Wall -lSDL2_image

.PHONY:clean
clean:
	rm -f game
