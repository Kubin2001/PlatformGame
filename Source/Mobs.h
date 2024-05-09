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

class Enemy {
	protected:
		SDL_Rect rectangle;
		int movementtype = 1;
		int animation = 2;
		int hitPoints = 20;
		bool colision[4] = { 0,0,0,0 };
		int invTime = 0;

	public:
		SDL_Texture* texture;

		virtual SDL_Rect* GetRectangle();

		virtual int getAnimation();

		virtual void setAnimation(int temp);

		virtual int getHitPoints();

		virtual void setHitPoints(int temp);

		virtual void setColison(bool value, int index);

		virtual bool getColison(int index);

		virtual void Movement(Player* player, Map* map) = 0;

		virtual void setInvTime(int value);

		virtual int getInvTime();

};

class Wolf : public Enemy{
	private:
		CollisonProjectile* cProj;
		int agroo = 0;

	public:
		Wolf() {
			hitPoints = 20;
		}
		void Movement(Player* player, Map* map)override;
};

class Charger : public Enemy{
	public:
		Charger() {
			hitPoints = 10;
		}
		void Movement(Player* player, Map* map)override;
};


class Mobs {
	private:
		SDL_Renderer* renderer;

		std::vector<Enemy*> Enemies;

		SDL_Texture *textureCharger = nullptr;

		SDL_Texture *textureWolf = nullptr;

	public:
		Mobs(SDL_Renderer* renderer);

		//getters and setters
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		SDL_Texture* GetTextureWolf();

		void SetTextureWolf(SDL_Texture* temptex);

		std::vector<Enemy*>& getEnemies();

		//getters and setters

		void LoadMobs();

		void DetectColison(Player* player,Map* map);

		void MoveMobs(const Uint8* state, Player* player, Map *map);

		void RenderEnemies();

		void Render();

		~Mobs();
};
