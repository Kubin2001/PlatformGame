#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Mobs.h"
#include "UI.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	Map* map;
	Mobs* mobs;
	UI* ui;
	SDL_Texture* textback;
	SDL_Rect rectback;

public:
	Game();

	void SetUpWindow(int& windowtype);

	void Start(int& windowtype);

	void LoadTextures(int& windowtype);

	void Events(bool& status, int& windowtype);

	void Exit(bool& status,int& windowtype);

	void Movement(int& windowtype);

	void Render(int& windowtype);

	void Clear();

	SDL_Texture* load(const char* file, SDL_Renderer* ren);

	~Game();

};
