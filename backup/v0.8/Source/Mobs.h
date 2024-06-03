#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "player.h"
#include "Map.h"


class Charger{
	private:
		SDL_Rect rectangle;
		int movementBuffor = 0;
		int movementtype = 1;
		int animation = 2;
		bool colision[4] = { 0,0,0,0 };

	public:
		SDL_Rect* GetRectangle();

		void Movement();

		int getAnimation();

		void setAnimation(int temp);

		void setColison(bool value, int index);

		bool getColison(int index);
};


class Mobs {
	private:
		std::vector<Charger> Chargers;

		SDL_Texture *textureCharger = nullptr;

	public:
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		void LoadMobs();

		void DetectColison(Player* player,Map* map);

		void MoveMobs(const Uint8* state, Player* player);

		void RenderChargers(SDL_Renderer* renderer);

		void Render(SDL_Renderer* renderer);
};
