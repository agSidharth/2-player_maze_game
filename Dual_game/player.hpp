#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "constants.hpp"
#include "Map.hpp"
using namespace std;

class player
{
public:

	player(int x,int y,int z,int w);
	void init(SDL_Renderer *renderer,string path);						//initialize the player
	SDL_Rect valid_move(SDL_Rect box,int xmove,int ymove,int maze[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE]);
	SDL_Rect teleport(SDL_Rect box,Map* maze,Mix_Chunk* vent_sound);

	bool touch(Map* maze,int type);
	void ForScore(TTF_Font* Font,SDL_Renderer *renderer,string intro,bool add);

	void clean();

	SDL_Texture* playerTex;
	SDL_Texture* scoreTex;
	SDL_Rect destR,scoreR;

	int distance = 5;
	int coins = 2;
	int health = 100;

	int playerDir = -1; 			//initial direction is stored as NULL
	int lastDir   = -1;				//last direction needed for bullet

};

void player::clean()
{
	playerTex = nullptr;
	scoreTex = nullptr;
}

player::player(int x,int y,int score_x,int score_y)
{
	destR.w = PLAYER_SIZE;
	destR.h = PLAYER_SIZE;
	destR.x = x;
	destR.y = y;

	scoreR.x = score_x;
	scoreR.y = score_y;
	coins = 2;
	health = 100;
}

void player::ForScore(TTF_Font* Font,SDL_Renderer *renderer,string intro,bool add)
{
	SDL_Color Black= {0,0,0,255};

	if(add) intro =  intro + to_string(coins);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, intro.c_str(), Black);
	scoreTex = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);

	SDL_QueryTexture(scoreTex,nullptr,nullptr,&scoreR.w,&scoreR.h);
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
		check = check && (map[(box.x+xmove)/TILE_SIZE][(box.y+ymove)/TILE_SIZE]%2!=1); 
		check = check && (map[(box.x+xmove+PLAYER_SIZE)/TILE_SIZE][(box.y+ymove+PLAYER_SIZE)/TILE_SIZE]%2!=1);
		check = check && (map[(box.x+xmove+PLAYER_SIZE)/TILE_SIZE][(box.y+ymove)/TILE_SIZE]%2!=1); 
		check = check && (map[(box.x+xmove)/TILE_SIZE][(box.y+ymove+PLAYER_SIZE)/TILE_SIZE]%2!=1);

		if(check)
		{
			temp.x = box.x + xmove;
			temp.y = box.y + ymove;
		}
	}

	if(xmove==distance || ymove==distance)
	{
		valid_move(box,xmove/2,ymove/2,map);
	}

	return temp;
}

SDL_Rect player::teleport(SDL_Rect box,Map* maze,Mix_Chunk* vent_sound)
{
	SDL_Rect temp_vent = maze->first_vent;
	if(SDL_HasIntersection(&temp_vent,&box)==SDL_TRUE)
	{
		Mix_PlayChannel(-1,vent_sound, 0 );
		box.x = maze->second_vent.x;
		box.y = maze->second_vent.y;
		return box;
	}
	temp_vent = maze->second_vent;
	if(SDL_HasIntersection(&temp_vent,&box)==SDL_TRUE)
	{
		Mix_PlayChannel(-1,vent_sound, 0 );
		box.x = maze->first_vent.x;
		box.y = maze->first_vent.y;
		return box;
	}
	return box;
}

bool player::touch(Map* maze,int type)		//(3*PLAYER_SIZE)/4 to for much more efficient touc
{
	int xpos = destR.x;
	int ypos = destR.y;

	if(maze->map[xpos/TILE_SIZE][ypos/TILE_SIZE]==type)
	{
		maze->map[xpos/TILE_SIZE][ypos/TILE_SIZE] = 0; 
		coins++;
		return true;
	}
	else if(maze->map[(xpos+((3*PLAYER_SIZE)/4))/TILE_SIZE][ypos/TILE_SIZE]==type)
	{
		maze->map[(xpos+((3*PLAYER_SIZE)/4))/TILE_SIZE][ypos/TILE_SIZE] = 0; 
		coins++;
		return true;
	}
	else if(maze->map[xpos/TILE_SIZE][(ypos+((3*PLAYER_SIZE)/4))/TILE_SIZE]==type)
	{
		maze->map[xpos/TILE_SIZE][(ypos+((3*PLAYER_SIZE)/4))/TILE_SIZE] = 0;
		coins++;
		return true;	
	}
	else if(maze->map[(xpos+((3*PLAYER_SIZE)/4))/TILE_SIZE][(ypos+((3*PLAYER_SIZE)/4))/TILE_SIZE]==type)
	{
		maze->map[(xpos+((3*PLAYER_SIZE)/4))/TILE_SIZE][(ypos+((3*PLAYER_SIZE)/4))/TILE_SIZE] = 0;
		coins++;
		return true;
	}
	return false;
}