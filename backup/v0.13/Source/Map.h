#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "UI.h"

class Player;

class Flag {
	private:
		SDL_Rect rectangle;

	public:

		SDL_Rect* GetRectangle();
};

class Platform {
	private:
		SDL_Rect rectangle;

	public:

		SDL_Rect* GetRectangle();
};

class Pillar {
private:
	SDL_Rect rectangle;

public:

	SDL_Rect* GetRectangle();
};

class Map {
private:
	SDL_Renderer* renderer = nullptr;

	SDL_Rect rectanglesGrass[37];

	std::vector<Platform> Platforms;
	std::vector<Pillar> Pillars;
	std::vector<Flag> Flags;

	SDL_Texture* textureGrass = nullptr;
	SDL_Texture* texturePlatform = nullptr;
	SDL_Texture* texturePillar = nullptr;
	SDL_Texture* textureFlag = nullptr;
	
public:
	Map(SDL_Renderer* renderer);

	//getters and setters

	SDL_Texture* GetTextureGrass();

	void SetTextureGrass(SDL_Texture* temptex);

	SDL_Texture* GetTexturePLatform();

	void SetTexturePlatform(SDL_Texture* temptex);

	SDL_Texture* GetTexturePilar();

	void SetTexturePilar(SDL_Texture* temptex);

	SDL_Texture* GetTextureFlag();

	void SetTextureFlag(SDL_Texture* temptex);

	SDL_Rect* GetRectangle(int index);
	//getters and setters

	void Render();

	void CreateFloor();

	void DetectColison(Player* player,UI *ui);

	void MoveMap(const Uint8* state,Player *player);

	void RenderFloor();

	void CreateLevel();

	void RenderPlatforms();

	void RenderPillar();

	void RenderFlag();

	std::vector<Pillar> &getPillar();

	std::vector<Platform> &getPlatform();

	std::vector<Flag> &getFlag();

	~Map();
};
