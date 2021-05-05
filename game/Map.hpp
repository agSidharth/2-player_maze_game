#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Tile.hpp"
#include "Coin.hpp"
# include "Vent.hpp"
#include "mazegen.hpp"
using namespace std;

class Map 
{
public:

    Map(SDL_Renderer *renderer);

    void DrawMap(SDL_Renderer *renderer);

    void clean();

    pair<int,int> init_pos(int xpos,int ypos,int parameter);

    SDL_Rect srcR;
    Tile* tile = nullptr;
    Coin* coin = nullptr;
    Vent* vent = nullptr;

    SDL_Rect first_vent,second_vent;
    int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE];
};

void Map::clean()
{
    tile->clean();
    tile = nullptr;
    coin->clean();
    coin = nullptr;
    vent->clean();
    vent = nullptr;
}

Map::Map(SDL_Renderer *renderer)
{
    tile = new Tile(0,0);
    tile->init(renderer);
    coin = new Coin(0,0);
    coin->init(renderer);
    vent = new Vent(0,0);
    vent->init(renderer);

    srcR.w = TILE_SIZE;
    srcR.h = TILE_SIZE;
    srcR.x = 0;
    srcR.y = 0;

    first_vent.w = TILE_SIZE;
    first_vent.h = TILE_SIZE;

    second_vent.w = TILE_SIZE;
    second_vent.h = TILE_SIZE;
    
    Maze* matrix = new Maze(SCREEN_WIDTH/TILE_SIZE,SCREEN_HEIGHT/TILE_SIZE);
    matrix -> init(34);
    
    matrix -> create(0,0);
    vector<vector<int>> vector_map = matrix->M;
    
    for(int row=0;row<SCREEN_WIDTH/TILE_SIZE;row++)
    {
        for(int col=0;col<SCREEN_HEIGHT/TILE_SIZE;col++)
        {
            map[row][col] = vector_map[row][col];
        }
    }
    
}

void Map::DrawMap(SDL_Renderer *renderer)
{
    int type = 0;
    int xpos = 0;
    int ypos = 0;
    
    for(int row=0;row<SCREEN_WIDTH/TILE_SIZE;row++)
    {
        for(int col=0;col<SCREEN_HEIGHT/TILE_SIZE;col++)
        {
            type = map[row][col];
            xpos = row*TILE_SIZE;
            ypos = col*TILE_SIZE;
            if(type == 0)
            {
            	int k = rand()%160000;
            	if(k==0) map[row][col] = 2;
            }
            switch(type)
            {
                case -1:
                    vent->draw(renderer,srcR,xpos,ypos);break;
                case 1:
                    tile->draw(renderer,srcR,xpos,ypos);break;
                case 2:
                	coin->draw(renderer,srcR,xpos,ypos);break;
                default:break;
            }
        }
    }
}

pair<int,int> Map::init_pos(int xpos,int ypos,int parameter)
{
	for(int d=0;;d++)
    {
    	for(int xd = 0;xd <=d;xd++)
    	{
    		int yd = d-xd;
    		if ((xpos+xd)>=0 && ((xpos+xd)< SCREEN_WIDTH/TILE_SIZE) && (ypos+yd)>=0 && (ypos+yd)< SCREEN_WIDTH/TILE_SIZE) 
    		{
    			if(map[xpos+xd][ypos+yd]==0) return make_pair((xpos+xd)*TILE_SIZE,(ypos+yd)*TILE_SIZE);
    		}
    		if ((xpos+xd)>=0 && ((xpos+xd)< SCREEN_WIDTH/TILE_SIZE) && (ypos-yd)>=0 && (ypos-yd)< SCREEN_WIDTH/TILE_SIZE) 
    		{
    			if(map[xpos+xd][ypos-yd]==0) return make_pair((xpos+xd)*TILE_SIZE,(ypos-yd)*TILE_SIZE);
    		}
    		if ((xpos-xd)>=0 && ((xpos-xd)< SCREEN_WIDTH/TILE_SIZE) && (ypos+yd)>=0 && (ypos+yd)< SCREEN_WIDTH/TILE_SIZE) 
    		{
    			if(map[xpos-xd][ypos+yd]==0) return make_pair((xpos-xd)*TILE_SIZE,(ypos+yd)*TILE_SIZE);
    		}
    		if ((xpos-xd)>=0 && ((xpos-xd)< SCREEN_WIDTH/TILE_SIZE) && (ypos-yd)>=0 && (ypos-yd)< SCREEN_WIDTH/TILE_SIZE) 
    		{
    			if(map[xpos-xd][ypos-yd]==0) return make_pair((xpos-xd)*TILE_SIZE,(ypos-yd)*TILE_SIZE);
    		}
    	}
    }
}