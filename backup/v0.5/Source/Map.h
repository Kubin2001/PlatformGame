#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"

class Platform {
	private:
		SDL_Rect rectangle;

	public:

		SDL_Rect* GetRectangle();

		int getAnimation();

		void setAnimation();
};

class Pilar {
private:
	SDL_Rect rectangle;

public:

	SDL_Rect* GetRectangle();
};

class Map {
private:
	SDL_Texture* textureGrass = nullptr;
	SDL_Rect rectanglesGrass[37];

	std::vector<Platform> Platforms;
	std::vector<Pilar> Pilars;

	SDL_Texture* texturePlatform = nullptr;
	SDL_Texture* texturePilar = nullptr;
	
public:

	SDL_Texture* GetTextureGrass();

	void SetTextureGrass(SDL_Texture* temptex);

	SDL_Texture* GetTexturePLatform();

	void SetTexturePlatform(SDL_Texture* temptex);

	SDL_Texture* GetTexturePilar();

	void SetTexturePilar(SDL_Texture* temptex);

	SDL_Rect* GetRectangle(int index);

	void Render(SDL_Renderer* renderer);

	void CreateFloor();

	void DetectColison(Player* player);

	void MoveMap(const Uint8* state,Player *player);

	void RenderFloor(SDL_Renderer* renderer);

	void CreateLevel();

	void RenderPlatforms(SDL_Renderer* renderer);

	void RenderPilar(SDL_Renderer* renderer);
};
