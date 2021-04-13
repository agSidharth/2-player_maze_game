#include<SDL2/SDL.h>
#include<iostream>
#include"game.hpp"
//#include "player.hpp"
using namespace std;

Game::Game()
{
	
}

void Game::init(string title,int xpos,int ypos,int width,int height)
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

}
void Game::render()
{
	SDL_RenderClear(Renderer);
	SDL_RenderPresent(Renderer);
	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"GAME OVER";

}