#pragma once
#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class bullet
{
public:

	bullet(int x,int y,int dir);
	
	void init(SDL_Renderer *renderer);
	void move();

	SDL_Texture* bulletTex;
	SDL_Rect destR;
	
	//int pathlen;			//stores total pathlength covered till now, bullet can go finite distances only..
	int direction; 
	int distance = 10;		//distance moved in single iteration.				
};

bullet::bullet(int x,int y,int dir)
{
	destR.w = BULLET_SIZE;
	destR.h = BULLET_SIZE;
	destR.x = x;
	destR.y = y;
	direction = dir;
}

void bullet::init(SDL_Renderer *renderer)
{
	string path = "./resources/bullet.png";
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	bulletTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void bullet::move()
{
	switch(direction)
	{
		case 0: 
		if(destR.y<distance) direction = 2;
		destR.y = abs(destR.y - distance); break;
		case 1:
		if(destR.x+BULLET_SIZE+distance>SCREEN_WIDTH) direction = 3;
		destR.x = SCREEN_WIDTH - BULLET_SIZE - abs(destR.x+distance+BULLET_SIZE-SCREEN_WIDTH);break;
		case 2:
		if(destR.y+BULLET_SIZE+distance>SCREEN_HEIGHT) direction = 0;
		destR.y = SCREEN_HEIGHT - BULLET_SIZE - abs(destR.y+BULLET_SIZE+distance-SCREEN_HEIGHT);break;
		case 3:
		if(destR.x<distance) direction = 1;
		destR.x = abs(destR.x - distance);break;		
	}
}