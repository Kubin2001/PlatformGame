#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "player.h"
#include "Map.h"

class Player;

class Map;

class Charger{
	private:
		SDL_Rect rectangle;
		int movementBuffor = 0;
		int movementtype = 1;
		int animation = 2;
		int hitPoints = 10;
		bool colision[4] = { 0,0,0,0 };

	public:
		SDL_Rect* GetRectangle();

		void Movement();

		int getAnimation();

		void setAnimation(int temp);

		int getHitPoints();

		void setHitPoints(int temp);

		void setColison(bool value, int index);

		bool getColison(int index);
};


class Mobs {
	private:
		SDL_Renderer* renderer;

		std::vector<Charger> Chargers;

		SDL_Texture *textureCharger = nullptr;

	public:
		Mobs(SDL_Renderer* renderer);

		//getters and setters
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		std::vector<Charger>& getChargers();
		//getters and setters

		void LoadMobs();

		void DetectColison(Player* player,Map* map);

		void MoveMobs(const Uint8* state, Player* player);

		void RenderChargers();

		void Render();

		~Mobs();
};
