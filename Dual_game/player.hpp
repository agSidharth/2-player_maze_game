#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class player
{
public:

	player(int x,int y);

	void init(SDL_Renderer *renderer,string path);						//initialize the player

	void incoins(int x=1) {coins+=x;}	//increase coins by x(or 1 if not provided)

	bool spendcoins(int);				//decrease coins

	SDL_Texture* playerTex;
	SDL_Rect destR;

	int coins = 5;
	int health = 100;
};

player::player(int x,int y)
{
	destR.w = 64;
	destR.h = 64;
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