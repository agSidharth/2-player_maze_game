#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"			//handles all the things on the screen

using namespace std;

int main()
{
	char PLAY_AGAIN = "Y";
	while(PLAY_AGAIN == "Y" || play_again == "y")
	{
		Game* a;
		a = new Game();
		a->init();
		while(a->running())
		{
			a->handleEvents();
			a->render();
		}
		a->clean();
		cout << "Want to play again  (Y/N)"<<endl;
		cin >> PLAY_AGAIN;
	}
	return 0;
}