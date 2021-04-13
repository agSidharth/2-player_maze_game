#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "player.hpp"
using namespace std;

class Game
{
public:
	Game();

	void init(char* title,int xpos,int ypos,int width,int height);			//Initialize the game window for first time..

	void handleEvents();	//Handle the keyboard input in each cycle and updates all the required variables

	void update();

	void render();			//Change the screen being rendered and updates it.

	void clean();			//Once the game is over destroys the screen and renderer

	bool running() {return isRunning;}

	bool isRunning = false;
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	player *player1 = nullptr;
	player *player2 = nullptr;
};


Game::Game()
{
	player1 = new player(0,0);
	player2 = new player(600,600);
}

void Game::init(char* title,int xpos,int ypos,int width,int height)
{
	if(SDL_Init(SDL_INIT_EVERYTHING)==0)
	{
		cout<<"The game has been initialised\n";
	}
	window = SDL_CreateWindow(title,xpos,ypos,width,height,0);

	isRunning = true;
	if(window==0)
	{
		isRunning = false;
		cout<<"Window has not been created yet";
	}

	renderer = SDL_CreateRenderer(window,-1,0);
	if(renderer==0)
	{
		cout<<"Renderer has not been initialised";
		isRunning = false;
	}

	string path1 = "resources/ghost1.png"; 
	player1->init(renderer,path1);

	string path2 = "resources/ghost2.png";
	player2->init(renderer,path2);	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: isRunning = false;break;
		default: break;
	}
}

void Game::update()
{
	player1->destR.x++;
	player2->destR.x--;
}
void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,player1->playerTex,NULL,&(player1->destR));
	SDL_RenderCopy(renderer,player2->playerTex,NULL,&(player2->destR));
	SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"GAME OVER"<<endl; 
}