#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Mobs.h"
#include "UI.h"
#include "Collectables.h"
#include "LevelEditor.h"
#include "ParticlesManager.h"
#include "Camera.h"

class Game {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Camera* camera;
	Player* player;
	Map* map;
	Mobs* mobs;
	UI* ui;
	Collectables* collectables;
	ParticlesManager* particlesManager;
	LevelEditor* levelEditor;
	
	SDL_Texture* textback = nullptr;
	bool renderBack = true;
	SDL_Rect rectback{0,0,1400,800};
	SDL_Event event = {};
	long long int framesCounter = 0;

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
