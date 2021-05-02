#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class  Tile
{
public:

    Tile(int x,int y);

    void init(SDL_Renderer* renderer);

    void draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos);

    void clean();

    SDL_Rect destR;
    SDL_Texture* tileTex;
};

void Tile::clean()
{
    tileTex = nullptr;
}

Tile::Tile(int x,int y)
{
    destR.x = x;
    destR.y = y;
    destR.w = TILE_SIZE;
    destR.h = TILE_SIZE;
}

void Tile::init(SDL_Renderer* renderer)
{
    string path = "./resources/tile.png";
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	tileTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Tile::draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos)
{
    destR.x = xpos;
    destR.y = ypos;
    SDL_RenderCopy(renderer,tileTex,NULL,&(destR));
}