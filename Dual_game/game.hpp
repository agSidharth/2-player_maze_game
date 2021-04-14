#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Map.hpp"
#include "bullet.hpp"
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
	Map* maze = nullptr;
	deque<bullet*> all_bullets;
};


Game::Game()
{
	
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

	maze = new Map(renderer);

	//for correct initialization of location of players.
	pair<int,int> min_location = maze->init_pos(0,0,1);
	player1 = new player(min_location.first,min_location.second);

	pair<int,int> max_location = maze->init_pos(SCREEN_WIDTH/TILE_SIZE-1,SCREEN_HEIGHT/TILE_SIZE-1,-1);
	player2 = new player(max_location.first,max_location.second);
	
	string path1 = "resources/ghost1.png"; 
	player1->init(renderer,path1);

	string path2 = "resources/ghost2.png";
	player2->init(renderer,path2);	
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	int xmove = 0;
	int ymove = 0;

	if(event.type==SDL_QUIT) isRunning = false;
	else	
    {
		switch (event.key.keysym.sym)
    	{
        	case SDLK_LEFT: 	xmove = -4;player1->playerDir = 3;break;
        	case SDLK_RIGHT: 	xmove = 4; player1->playerDir = 1;break;
        	case SDLK_UP:    	ymove = -4; player1->playerDir = 0; break;
        	case SDLK_DOWN:  	ymove = 4; player1->playerDir = 2; break;
			case SDLK_s: 		
			bullet* newbullet = new bullet(player1->destR.x,player1->destR.y,player1->playerDir);
			newbullet->init(renderer);
			all_bullets.push_back(newbullet);break;
    	} 
		player1->destR = player1->valid_move(player1->destR,xmove,ymove,maze->map);
	}
}

void Game::update()
{
	int i=0;
	int total_bullets = all_bullets.size();
	while(i<all_bullets.size())
	{
		if(all_bullets[i]->move(maze->map) == false)
		{
			auto it = all_bullets.begin();
			all_bullets.pop_front();
			continue;
		}
		i++;
	}
}
void Game::render()
{
	SDL_RenderClear(renderer);
	maze->DrawMap(renderer);
	SDL_RenderCopy(renderer,player1->playerTex,NULL,&(player1->destR));
	SDL_RenderCopy(renderer,player2->playerTex,NULL,&(player2->destR));

	int i=0;
	int total_bullets = all_bullets.size();
	while(i<total_bullets)
	{
		SDL_RenderCopy(renderer,all_bullets[i]->bulletTex,NULL,&(all_bullets[i]->destR));
		i++;
	}

	SDL_RenderPresent(renderer);	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"GAME OVER"<<endl; 
}