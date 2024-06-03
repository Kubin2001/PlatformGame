#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"

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

class Pilar {
private:
	SDL_Rect rectangle;

public:

	SDL_Rect* GetRectangle();
};

class Map {
private:
	SDL_Rect rectanglesGrass[37];

	std::vector<Platform> Platforms;
	std::vector<Pilar> Pilars;
	std::vector<Flag> Flags;

	SDL_Texture* textureGrass = nullptr;
	SDL_Texture* texturePlatform = nullptr;
	SDL_Texture* texturePilar = nullptr;
	SDL_Texture* textureFlag = nullptr;
	
public:

	SDL_Texture* GetTextureGrass();

	void SetTextureGrass(SDL_Texture* temptex);

	SDL_Texture* GetTexturePLatform();

	void SetTexturePlatform(SDL_Texture* temptex);

	SDL_Texture* GetTexturePilar();

	void SetTexturePilar(SDL_Texture* temptex);

	SDL_Texture* GetTextureFlag();

	void SetTextureFlag(SDL_Texture* temptex);

	SDL_Rect* GetRectangle(int index);

	void Render(SDL_Renderer* renderer);

	void CreateFloor();

	void DetectColison(Player* player);

	void MoveMap(const Uint8* state,Player *player);

	void RenderFloor(SDL_Renderer* renderer);

	void CreateLevel();

	void RenderPlatforms(SDL_Renderer* renderer);

	void RenderPilar(SDL_Renderer* renderer);

	void RenderFlag(SDL_Renderer* renderer);

	std::vector<Pilar> &getPillar();

	std::vector<Platform> &getPlatform();

	std::vector<Flag> &getFlag();
};
