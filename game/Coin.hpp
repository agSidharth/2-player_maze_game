#pragma once

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
using namespace std;

class  Coin
{
public:

    Coin(int x,int y);

    void init(SDL_Renderer* renderer);

    void draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos);

    void clean();
    
    SDL_Rect destR;
    SDL_Texture* CoinTex;
};

void Coin::clean()
{
    CoinTex = nullptr;
}

Coin::Coin(int x,int y)
{
    destR.x = x;
    destR.y = y;
    destR.w = COIN_SIZE;
    destR.h = COIN_SIZE;
}

void Coin::init(SDL_Renderer* renderer)
{
    string path = "./resources/Coin.png";
	const char* path_array = path.c_str();

	SDL_Surface* tmpSurface = IMG_Load(path_array);
	CoinTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Coin::draw(SDL_Renderer* renderer,SDL_Rect srcR,int xpos,int ypos)
{
    destR.x = xpos;
    destR.y = ypos;
    SDL_RenderCopy(renderer,CoinTex,NULL,&(destR));
}