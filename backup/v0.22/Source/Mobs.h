#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "player.h"
#include "Map.h"
#include "UI.h"
#include "Colision.h"
#include "ParticlesManager.h"
#include "Camera.h"

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
		bool renderable = false;

	public:
		SDL_Texture* texture;

		virtual SDL_Rect* GetRectangle();

		virtual int getAnimation();

		virtual void setAnimation(int temp);

		virtual int getHitPoints();

		virtual void setHitPoints(int temp);

		virtual void setColison(bool value, int index);

		virtual bool getColison(int index);

		virtual void setInvTime(int value);

		virtual int getInvTime();

		virtual bool GetRenderable();

		virtual void SetRenderable(bool temp);

		virtual void Movement(Player* player, Map* map, ParticlesManager* particleManager) = 0;


};

class Wolf : public Enemy{
	private:
		CollisonProjectile* cProj;
		int agroo = 0;

	public:
		Wolf() {
			hitPoints = 20;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		~Wolf() {
			delete cProj;
			cProj = nullptr;
		}
};

class Charger : public Enemy{
	public:
		Charger() {
			hitPoints = 10;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;
};

class Pirate : public Enemy {
	private:
		CollisonProjectile* cProj;
		bool isAggressive = false;
		int AttackDelay = 0;
		int agroo = 0;

	public:
		Pirate() {
			hitPoints = 40;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		~Pirate() {
			delete cProj;
			cProj = nullptr;
		}
};


class Mobs {
	private:
		SDL_Renderer* renderer;

		std::vector<Enemy*> Enemies;

		SDL_Texture *textureCharger = nullptr;

		SDL_Texture *textureWolf = nullptr;

		SDL_Texture *texturePirate = nullptr;

	public:
		Mobs(SDL_Renderer* renderer);

		//getters and setters
		SDL_Texture* GetTextureCharger();

		void SetTextureCharger(SDL_Texture* temptex);

		SDL_Texture* GetTextureWolf();

		void SetTextureWolf(SDL_Texture* temptex);

		SDL_Texture* GetTexturePirate();

		void SetTexturePirate(SDL_Texture* temptex);

		std::vector<Enemy*>& getEnemies();

		//getters and setters

		void LoadMobs();

		void DetectColison(Player* player,Map* map, SDL_Rect camRect);

		void MoveMobs(const Uint8* state, Player* player, Map *map, ParticlesManager* particleManager);

		void RenderEnemies(SDL_Rect camRect);

		void Render(SDL_Rect camRect);

		~Mobs();
};
