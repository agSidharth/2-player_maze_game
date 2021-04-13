#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"			//handles all the things on the screen
using namespace std;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

int main()
{
	char PLAY_AGAIN = 'Y';
	while(PLAY_AGAIN == 'Y' || PLAY_AGAIN == 'y')
	{
		Game* game;
		game = new Game();
		game->init("Dual",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);

		while(game->running())
		{
			game->handleEvents();
			game->update();
			game->render();
		}
		game->clean();

		cout << "Want to play again  (Y/N)"<<endl;
		cin >> PLAY_AGAIN;
	}
	return 0;
}