#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Tile.hpp"
#include "mazegen.hpp"
using namespace std;

class Map 
{
public:

    Map(SDL_Renderer *renderer);

    void DrawMap(SDL_Renderer *renderer);

    pair<int,int> init_pos(int xpos,int ypos,int parameter);

    SDL_Rect srcR;
    Tile* tile = nullptr;

    int map[SCREEN_WIDTH/TILE_SIZE][SCREEN_HEIGHT/TILE_SIZE];
};

Map::Map(SDL_Renderer *renderer)
{
    tile = new Tile(0,0);
    tile->init(renderer);

    srcR.w = TILE_SIZE;
    srcR.h = TILE_SIZE;
    srcR.x = 0;
    srcR.y = 0;

    Maze* matrix = new Maze(SCREEN_WIDTH/TILE_SIZE,SCREEN_WIDTH/TILE_SIZE);
    matrix -> init(43);
    
    matrix -> create(SCREEN_WIDTH/TILE_SIZE,SCREEN_HEIGHT/TILE_SIZE);
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

            switch(type)
            {
                case 1:
                    tile->draw(renderer,srcR,xpos,ypos);break;
                default:break;
            }
        }
    }
}

pair<int,int> Map::init_pos(int xpos,int ypos,int parameter)
{
    int x = xpos;
    int y = ypos;
    int factor = 8;

    while(map[xpos][y]==1 && map[x][ypos]==1)
    {
        x+=parameter;
        y+=parameter;

        if(x<0 || y<0 || x>=SCREEN_WIDTH/TILE_SIZE || y>=SCREEN_HEIGHT/TILE_SIZE)
        {
            xpos+= parameter*(SCREEN_WIDTH/TILE_SIZE-1)/factor;
            ypos+= parameter*(SCREEN_HEIGHT/TILE_SIZE-1)/factor;
            x = xpos;
            y = ypos;
        }
    }
    if(map[xpos][y]==0) return make_pair(xpos*TILE_SIZE,y*TILE_SIZE);
    return make_pair(x*TILE_SIZE,ypos*TILE_SIZE);

}