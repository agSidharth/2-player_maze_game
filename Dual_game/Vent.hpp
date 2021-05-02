#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class Vent
{
    public:

    Vent(int x,int y);
    void init(SDL_Renderer* renderer);

    void draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos);

    SDL_Rect destR;
    SDL_Texture* ventTex;
};

Vent::Vent(int x,int y)
{
    destR.x = x;
    destR.y = y;
    destR.w = TILE_SIZE;
    destR.h = TILE_SIZE;
}

void Vent::init(SDL_Renderer* renderer)
{
    string path = "./resources/vent.png";
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	ventTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Vent::draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos)
{
    destR.x = xpos;
    destR.y = ypos;
    SDL_RenderCopy(renderer,ventTex,NULL,&(destR));
}
