#pragma once
#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "player.hpp"
using namespace std;

class bullet
{
public:

	bullet(int x,int y,int dir,int my_id);
	
	void init(SDL_Renderer *renderer);
	bool safe_move(int xpos,int ypos,int type,int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE]);
	bool move(int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE],player* player1,player* player2);
	void clear();

	SDL_Texture* bulletTex;
	SDL_Rect destR;

	int shooter;
	int pathlen = 0;			//stores total pathlength covered till now, bullet can go finite distances only..
	int direction; 
	int distance = 8;		//distance moved in single iteration.				
};

void bullet::clear()
{
	bulletTex = nullptr;
}

bullet::bullet(int x,int y,int dir,int my_id)
{
	shooter = my_id;
	destR.w = BULLET_SIZE;
	destR.h = BULLET_SIZE;
	switch (dir)
	{
		case 0:	destR.x = x; destR.y = y - (PLAYER_SIZE+3); break;
		case 1: destR.x = x + (PLAYER_SIZE+3); destR.y = y; break;
		case 2: destR.x = x; destR.y = y + (PLAYER_SIZE+3); break;
		case 3: destR.x = x - (PLAYER_SIZE+3); destR.y = y; break;
	}
	direction = dir;
	
	if(destR.x<0)
	{
		destR.x = 1;
		direction = 1;
	}
	else if(destR.x>SCREEN_WIDTH)
	{
		destR.x = SCREEN_WIDTH-1;
		direction = 3;
	}
	else if(destR.y<0)
	{
		destR.y = 1;
		direction = 2;
	}
	else if(destR.y>SCREEN_HEIGHT)
	{
		destR.y = SCREEN_HEIGHT-1;
		direction = 0;
	}
}

void bullet::init(SDL_Renderer *renderer)
{
	string path = "./resources/bullet.png";
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	bulletTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

bool bullet::safe_move(int xpos,int ypos,int type,int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE])
{
	if(xpos<0 || xpos+BULLET_SIZE>SCREEN_WIDTH || ypos<0 || ypos+BULLET_SIZE>SCREEN_HEIGHT) return false;

	bool check = (map[(xpos)/TILE_SIZE][(ypos)/TILE_SIZE]!=type) && (map[(xpos+BULLET_SIZE)/TILE_SIZE][(ypos)/TILE_SIZE]!=type);
	check = (map[(xpos)/TILE_SIZE][(ypos+BULLET_SIZE)/TILE_SIZE]!=type) && (map[(xpos+BULLET_SIZE)/TILE_SIZE][(ypos+BULLET_SIZE)/TILE_SIZE]!=type);
	return check;
}

bool bullet::move(int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE],player* player1,player* player2)
{
	if(pathlen >= 2000) return false;

	if(SDL_HasIntersection(&destR,&(player1->destR))==SDL_TRUE && !(shooter==0 && pathlen<distance))
	{
		player1->health = 0;
		return false;
	}
	else if(SDL_HasIntersection(&destR,&(player2->destR))==SDL_TRUE && !(shooter==1 && pathlen<distance))
	{
		player2->health = 0;
		return false;
	}

	int xpos,ypos;

	switch(direction)
	{
		case 0: xpos = destR.x; ypos = destR.y-distance;break;
		case 1: xpos = destR.x+distance; ypos = destR.y;break;
		case 2: xpos = destR.x; ypos = destR.y + distance;break;
		case 3: xpos = destR.x-distance; ypos = destR.y;break;
	}

	if(safe_move(xpos,ypos,1,map))
	{destR.x = xpos; destR.y = ypos;}
	else if(direction==0) direction = 2;
	else if(direction==1) direction = 3;
	else if(direction==2) direction = 0;
	else if(direction==3) direction = 1;

	pathlen += distance;
	return true;
}