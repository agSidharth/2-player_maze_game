#pragma once
#include<iostream>

class player
{
public:
	player();
	~player();

	void init();						//initialize the player

	void incoins(int x=1) {coins+=x;}	//increase coins by x(or 1 if not provided)

	bool spendcoins(int);				//decrease coins

private:
	int coins = 5;
	int health = 100;
}