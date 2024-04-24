#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "player.h"
#include "Map.h"
#include "Colision.h"

class Player;

class Map;

class Wolf {
private:
	CollisonProjectile* cProj;
	SDL_Rect rectangle;
	int agroo = 0;
	int movementtype = 1;
	int animation = 2;
	int hitPoints = 20;
	bool colision[4] = { 0,0,0,0 };

public:
	SDL_Rect* GetRectangle();

	void Movement(Player* player, Map* map);

	int getAnimation();

	void setAnimation(int temp);

	int getHitPoints();

	void setHitPoints(int temp);

	void setColison(bool value, int index);

	bool getColison(int index);
};

class Charger{
	private:
		SDL_Rect rectangle;
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

		std::vector<Wolf> Wolfs;

		SDL_Texture *textureCharger = nullptr;

		SDL_Texture* textureWolf = nullptr;

	public:
		Mobs(SDL_Renderer* renderer);

		//getters and setters
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		SDL_Texture* GetTextureWolf();

		void SetTextureWolf(SDL_Texture* temptex);

		std::vector<Charger>& getChargers();

		std::vector<Wolf>& getWolfs();
		//getters and setters

		void LoadMobs();

		void DetectColison(Player* player,Map* map);

		void MoveMobs(const Uint8* state, Player* player, Map *map);

		void RenderChargers();

		void RenderWolfs();

		void Render();

		~Mobs();
};
