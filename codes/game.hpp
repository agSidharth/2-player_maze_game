#pragma once

#include<iostream>
#include<SDL2/SDL.h>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

class Game
{
public:
	Game();
	~Game();

	void init();			//Initialize the game window for first time..

	void handleEvents();	//Handle the keyboard input in each cycle and updates all the required variables

	void render();			//Change the screen being rendered and updates it.

	void clean();			//Once the game is over destroys the screen and renderer

	bool running() {return isRunning;}
private:
	bool isRunning = false;
	SDL_Window *window;
	SDL_Renderer *renderer;
};