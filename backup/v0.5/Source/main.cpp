#include <Windows.h>
#include <ctime>
#include "Game.h"

int main(int argv, char* argc[])
{
	bool status = true;
	srand(static_cast<unsigned int>(time(nullptr)));
	Game* game = new Game();

	game->StartGame();

	while (status)
	{
		game->Movement(status);
		game->Events();
		game->Render();

		SDL_Delay(16);
	}

	delete game;
	FreeConsole();
	exit(0);
	return 0;

}
