#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Mobs.h"
#include "UI.h"
#include "Equipment.h"
#include "LevelEditor.h"
#include "ParticlesManager.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player* player;
	Map* map;
	Mobs* mobs;
	UI* ui;
	Equipment* equipment;
	ParticlesManager* particlesManager;
	LevelEditor* levelEditor;
	
	SDL_Texture* textback;
	bool renderBack = true;
	SDL_Rect rectback{0,0,1400,800};
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
