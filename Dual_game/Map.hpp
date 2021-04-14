#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Tile.hpp"
using namespace std;

class 
{
public:

    Map();

    void LoadMap();
    void DrawMap();

    SDL_Rect src,dest;
    
    int map[SCREEN_WIDTH/50][SCREEN_HEIGHT/50];
};

Map::Map()
{
    
}

Map::void LoadMap()
{

}

Map::void DrawMap()
{

}