#include "player.hpp"

player::player()
{

}

player::~player()
{

}

void player::init()
{
	
}

bool player::spendcoins(int x)
{
	if(coins >= x)
	{
		coins -= x;
		return true;
	}
	else
		return false;
}