#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Mobs.h"
#include "UI.h"
#include "Equipment.h"
#include "LevelEditor.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	Map* map;
	Mobs* mobs;
	UI* ui;
	Equipment* equipment;
	LevelEditor* levelEditor;
	
	SDL_Texture* textback;
	SDL_Rect rectback;
	SDL_Event event;

public:
	Game();

	void SetUpWindow();

	void Start();

	void LoadTextures();

	void Events();

	void Exit();

	void Movement();

	void Render();

	void Clear();

	void SetWindow();

	SDL_Texture* load(const char* file, SDL_Renderer* ren);

	~Game();

};
