#pragma once
#include <SDL.h>
#include "UI.h"
#include "Mobs.h"
#include "ParticlesManager.h"

class Mobs;
class ParticlesManager;

class Weapon {
	private:
		SDL_Rect rectangle;
		int damage = 0;
		int animation = 1;
		SDL_Texture* texture = nullptr;

	public:
		Weapon(int w, int h, int tempdamage, SDL_Texture *temptext);
		SDL_Rect* GetRectangle();
		SDL_Texture * GetTexture();
		void Move(SDL_Rect rect);

		int GetAnimation();
		void SetAnimation(int temp);

};


class Player {
	private:
		SDL_Renderer* renderer = nullptr;
		SDL_Texture* texture = nullptr;
		SDL_Rect rectangle{ 700,400,32,70 };
		Weapon* weapon = nullptr;
		int JumpBuffer = 0;
		bool colision[4] = { 0,0,0,0 };
		int animation = 1;
		int damage = false;
		int damageBuffer = 0;
		int attackBuffer = 0;
		bool alive = true;
		bool armed = false;
	public:
		Player(SDL_Renderer *renderer);

		//Getters and setters
		SDL_Texture* GetTexture();

		void setJumpBuffer(int temp);

		int getJumpBuffer();

		void setColison(bool value,int index);

		bool getColison(int index);

		void setanimation(int value);

		int getanimation();

		void setattackBuffer(int value);

		int getDamageBuffer();

		void setDamageBuffer(int value);

		int getattackBuffer();

		bool GetDamage();

		void SetDamage(bool temp);

		void SetTexture(SDL_Texture* temptex);

		SDL_Rect* GetRectangle();

		SDL_Texture* GetTextureAttackParticle();

		void SetTextureAttackParticle(SDL_Texture* temptex);
		//Getters and setters

		void Render();

		void Jump(const Uint8* state);

		void CheckDamage(UI * ui);

		void SetWeapon(int w, int h, int tempdamage, SDL_Texture* temptext);

		void UpdateWeapon();

		void Attack(const Uint8* state, ParticlesManager* particleManager);

		~Player();
};