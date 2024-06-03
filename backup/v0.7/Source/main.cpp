#include <Windows.h>
#include <ctime>
#include "Game.h"

bool status = true;
int windowtype = 1;

int main(int argv, char* argc[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Game* game = new Game();

	game->SetUpWindow(windowtype);
	while (status) {

		game->Start(windowtype);
		while (status == true && windowtype == 1)
		{
			game->Movement(windowtype);
			game->Events(status, windowtype);
			game->Render(windowtype);
			game->Exit(status, windowtype);
			SDL_Delay(16);
		}

		game->Start(windowtype);
		while (windowtype == 2)
		{
			game->Movement(windowtype);
			game->Events(status, windowtype);
			game->Render(windowtype);
			game->Exit(status, windowtype);
			SDL_Delay(16);
		}
		game->Clear();
	}
	delete game;
	FreeConsole();
	exit(0);
	return 0;

}
