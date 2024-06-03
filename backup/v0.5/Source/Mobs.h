#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "player.h"


class Charger{
	private:
		SDL_Rect rectangle;
		int movementBuffor = 0;
		int movementtype = 2;
		int animation = 1;
		int randomMovement;

	public:
		SDL_Rect* GetRectangle();

		void Movement();

		int getAnimation();


		void setAnimation(int temp);
};


class Mobs {
	private:
		std::vector<Charger> Chargers;

		SDL_Texture *textureCharger = nullptr;

	public:
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		void LoadMobs();

		void DetectColison(Player* player);

		void MoveMobs(const Uint8* state, Player* player);

		void RenderChargers(SDL_Renderer* renderer);

		void Render(SDL_Renderer* renderer);
};
