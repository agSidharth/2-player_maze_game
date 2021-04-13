#include<iostream>
#include"game.hpp"
#include "player.hpp"
using namespace std;

Game::Game()
{
	p1 = new player();
	p2 = new player();
}

Game::~Game()
{

}

void Game::init()
{
	p1->init();
	p2->init();
}

void Game::handleEvents()
{

}

void Game::render()
{

}

void Game::clean()
{

}