#include <Windows.h>
#include <ctime>
#include "Game.h"
#include "SDL_image.h"

bool status = true;
int windowtype = 1;
int localWindow = 1;
std::string levelName = "Levels/level1.txt";

SDL_Texture* load(const char* file, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(file);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}

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
			game->SetWindow();
			SDL_Delay(16);
		}

		if (windowtype == 2) {
			game->Clear();
			game->Start();
		}

		while (windowtype == 2)
		{
			game->Movement();
			game->Events();
			game->Render();
			game->SetWindow();
			SDL_Delay(16);
		}
		if (windowtype == 3) {
			game->Clear();
			game->Start();
		}

		while (windowtype == 3)
		{
			game->Movement();
			game->Events();
			game->Render();
			game->SetWindow();
			SDL_Delay(16);
		}
		game->Clear();
	}
	delete game;
	FreeConsole();
	exit(0);
	return 0;

}
