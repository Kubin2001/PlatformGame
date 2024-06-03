#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Mobs.h"
class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	Map* map;
	Mobs* mobs;
	SDL_Texture* textback;
	SDL_Rect rectback;

	int buffer = 0;
	int buffer2 = 0;

public:
	Game();

	void StartGame();

	void LoadTextures();

	void Events();

	void Exit(bool& status, const Uint8* state);

	void Movement(bool& status);

	void Render();

	SDL_Texture* load(const char* file, SDL_Renderer* ren);

	~Game();

};
