#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "constants.hpp"
using namespace std;

class player
{
public:

	player(int x,int y);
	void init(SDL_Renderer *renderer,string path);						//initialize the player
	SDL_Rect valid_move(SDL_Rect box,int xmove,int ymove,int maze[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE]);
	void incoins(int x=1) {coins+=x;}	//increase coins by x(or 1 if not provided)
	bool spendcoins(int);				//decrease coins
	SDL_Texture* playerTex;
	SDL_Rect destR;

	int coins = 5;
	int health = 100;
	int playerDir = 0; 			//initial direction is stored at NORTH
};

player::player(int x,int y)
{
	destR.w = PLAYER_SIZE;
	destR.h = PLAYER_SIZE;
	destR.x = x;
	destR.y = y;
}

void player::init(SDL_Renderer *renderer,string path)
{
	const char* path_array = path.c_str();
	SDL_Surface* tmpSurface = IMG_Load(path_array);
	playerTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

SDL_Rect player::valid_move(SDL_Rect box,int xmove,int ymove,int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE])
{
	bool check = (box.x+xmove>=0) && (box.x+PLAYER_SIZE+xmove<=SCREEN_WIDTH);
	check = check && (box.y+ymove>=0) && (box.y+PLAYER_SIZE+ymove<=SCREEN_HEIGHT);
	
	SDL_Rect temp = box;
	if(check)
	{
		check = check && (map[(box.x+xmove)/TILE_SIZE][(box.y+ymove)/TILE_SIZE]%2==0); 
		check = check && (map[(box.x+xmove+PLAYER_SIZE)/TILE_SIZE][(box.y+ymove+PLAYER_SIZE)/TILE_SIZE]%2==0);
		check = check && (map[(box.x+xmove+PLAYER_SIZE)/TILE_SIZE][(box.y+ymove)/TILE_SIZE]%2==0); 
		check = check && (map[(box.x+xmove)/TILE_SIZE][(box.y+ymove+PLAYER_SIZE)/TILE_SIZE]%2==0);

		if(check)
		{
			temp.x = box.x + xmove;
			temp.y = box.y + ymove;
		}
	}
	return temp;
}

bool player::spendcoins(int x)
{
	if(coins >= x)
	{
		coins -= x;
		return true;
	}
	else
		return false;
}