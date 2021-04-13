#pragma once

#include<iostream>
#include<SDL2/SDL.h>
//#include "player.hpp"
using namespace std;

class Game
{
public:
	Game();

	void init(string title,int xpos,int ypos,int width,int height);			//Initialize the game window for first time..

	void handleEvents();	//Handle the keyboard input in each cycle and updates all the required variables

	void update();

	void render();			//Change the screen being rendered and updates it.

	void clean();			//Once the game is over destroys the screen and renderer

	bool running() {return isRunning;}

	bool isRunning = false;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	//player *p1 = nullptr;
	//player *p2 = nullptr;
};