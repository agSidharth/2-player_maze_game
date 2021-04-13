#include <iostream>
#include <SDL2/SDL.h>
#include "game.hpp"			//handles all the things on the screen
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{
	char PLAY_AGAIN = 'Y';

	int FPS = 60;
	int frameDelay = 1000/FPS;

	int frameStart;
	int frameTime,difference;

	while(PLAY_AGAIN == 'Y' || PLAY_AGAIN == 'y')
	{
		Game* game;
		game = new Game();
		game->init("Dual",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT);

		while(game->running())
		{
			frameStart = SDL_GetTicks();

			game->handleEvents();
			game->update();
			game->render();

			frameTime = SDL_GetTicks() - frameStart;

			difference = frameDelay - frameTime;
			if(difference>0)
			{
				SDL_Delay(difference);
			}
		}
		game->clean();

		cout << "Want to play again  (Y/N)"<<endl;
		cin >> PLAY_AGAIN;
	}
	return 0;
}