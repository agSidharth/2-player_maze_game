#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class bullet
{
public:
	bullet();
	~bullet();

	void init()

	SDL_Texture* playerTex;
	SDL_Rect destR;
	
	int pathlen;			//stores total pathlength covered till now, bullet can go finite distances only..
	int dirn; 				// 0 for up,1 for left,2 for down,3 for right
}

void bullet::init(SDL_Renderer *renderer,string path,int x,int y,int d)
{
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	bulletTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);

	destR.w = 64;
	destR.h = 64;
	destR.x = x;
	destR.y = y;
	int dirn = d;
	pathlen = 0;
}