#include <Windows.h>
#include <ctime>
#include "Game.h"

bool status = true;
int windowtype = 1;
std::string levelName = "Levels/level1.txt";

int main(int argv, char* argc[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	Game* game = new Game();

	game->SetUpWindow();
	while (status) {

		game->Start();
		while (windowtype == 1)
		{
			game->Movement();
			game->Events();
			game->Render();
			SDL_Delay(16);
		}

		game->Start();
		while (windowtype == 2)
		{
			game->Movement();
			game->Events();
			game->Render();
			SDL_Delay(16);
		}
		game->Clear();
	}
	delete game;
	FreeConsole();
	exit(0);
	return 0;

}
