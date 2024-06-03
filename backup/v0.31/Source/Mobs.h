#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "SDL_mixer.h"
#include <ctime>
#include "player.h"
#include "Map.h"
#include "UI.h"
#include "Colision.h"
#include "ParticlesManager.h"
#include "Camera.h"
#include "TextureManager.h"

class Player;

class Map;

class Enemy {
	protected:
		SDL_Rect rectangle = {};
		std::vector<SDL_Rect> sourceRectangle;
		SDL_Texture* texture;
		int movementtype = 1;
		static int enemyCount;
		int animation = 2;
		int hitPoints = 20;
		bool colision[4] = { 0,0,0,0 };
		int invTime = 0;
		bool renderable = false;
		bool jumpable = false;

		int animationCount = 0;
		int animationTimer = 0;

	public:
		virtual SDL_Rect* GetRectangle();

		virtual std::vector<SDL_Rect> &GetSourceRectangle();

		virtual void setTexture(SDL_Texture* text);

		virtual SDL_Texture * getTexture();

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

		virtual bool GetJumpable();

		virtual void LoadAnimations(int step);

		virtual SDL_Rect* ChooseAnimation() = 0;

		virtual void Movement(Player* player, Map* map, ParticlesManager* particleManager) = 0;

		virtual void MakeAgressive() = 0;
};

class Charger : public Enemy{
	public:
		Charger() {
			hitPoints = 10;
			animationCount = 0;
			jumpable = true;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		void MakeAgressive()override;

		SDL_Rect* ChooseAnimation()override;
		~Charger() {
		}
};

class Wolf : public Enemy {
private:
	CollisonProjectile* cProj;
	int agroo = 0;

public:
	Wolf() {
		hitPoints = 20;
		animationCount = 0;
		jumpable = true;
	}

	void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

	SDL_Rect* ChooseAnimation()override;

	void MakeAgressive()override;

	~Wolf() {
		delete cProj;
		cProj = nullptr;

	}
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
			animationCount = 2;
			animationTimer = rand() % 30;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		SDL_Rect* ChooseAnimation()override;

		void MakeAgressive()override;

		~Pirate() {
			delete cProj;
			cProj = nullptr;
		}
};

class Archer : public Enemy {
	private:
		CollisonProjectile* cProj;
		bool isAggressive = false;
		int AttackDelay = 0;
		int agroo = 0;

	public:
		Archer() {
			hitPoints = 20;
			animationCount = 4;
			animationTimer = 0;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		SDL_Rect* ChooseAnimation()override;

		void MakeAgressive()override;

		~Archer() {
			delete cProj;
			cProj = nullptr;
		}
};

class Shotter : public Enemy {
	public:
		Shotter() {
			hitPoints = 100000;
			animationCount = 0;
			jumpable = false;
		}

		void Movement(Player* player, Map* map, ParticlesManager* particleManager)override;

		void MakeAgressive()override;

		SDL_Rect* ChooseAnimation()override;

		~Shotter() {
		}
};

class Mobs {
	private:
		SDL_Renderer* renderer;

		std::vector<Enemy*> Enemies;

		std::vector<Texture> Textures;


	public:
		Mobs(SDL_Renderer* renderer);

		//getters and setters

		std::vector<Enemy*>& getEnemies();

		std::vector<Texture>& getTextures();

		//getters and setters

		void LoadTextures();

		void LoadMobs();

		void DetectColison(Player* player,Map* map, SDL_Rect camRect);

		void MoveMobs(const Uint8* state, Player* player, Map *map, ParticlesManager* particleManager);

		void RenderEnemies(SDL_Rect camRect);

		void Render(SDL_Rect camRect);

		~Mobs();
};
