#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "UI.h"
#include "Camera.h"
#include "TextureManager.h"

class Player;

class Enemy;

class Object {
	protected:
		SDL_Rect rectangle;
		bool renderable = false;
		SDL_Texture* texture;

	public:
		virtual SDL_Rect* GetRectangle();

		virtual bool GetRenderable();

		virtual void SetRenderable(bool temp);

		virtual SDL_Texture* GetTexture();

		virtual void SetTexture(SDL_Texture* temptex);

		virtual void PlayerCollision(Player* player, UI* ui) = 0;

		virtual void MobCollision(Enemy* enemy) = 0;

};

class MapObject : public Object {
	public:
		MapObject() {}
		void PlayerCollision(Player* player, UI* ui)override;

		void MobCollision(Enemy* enemy)override;
};


class Decoration : public Object {
	public:
		Decoration() {}
		void PlayerCollision(Player* player, UI* ui)override;

		void MobCollision(Enemy* enemy)override;
};


class DangerousObject : public Object {
	private:
		int damage = 10;
		bool floating = true;
	public:
		DangerousObject(int damage, bool floating) {
			this->damage = damage;
			this->floating = floating;
		}
		void PlayerCollision(Player* player, UI* ui)override;

		void MobCollision(Enemy* enemy)override;
};


class Flag : public Object  {
	public:
		Flag() {}
		void PlayerCollision(Player* player, UI* ui)override;

		void MobCollision(Enemy* enemy)override;
};

class InvWall{
	private:
		SDL_Rect rectangle;
		bool renderable = false;

	public:
		SDL_Rect* GetRectangle();

		bool GetRenderable();

		void SetRenderable(bool temp);
};


class Map {
	private:
		SDL_Renderer* renderer = nullptr;

		std::vector<Object*> Objects;
		std::vector<InvWall> InvWalls;

		std::vector<Object*> postPlayerRenderables;

		std::vector<Texture> Textures;
	
	public:
		//SDL_Texture* textureInvWall = nullptr;
		Map(SDL_Renderer* renderer);

		//getters and setters
		std::vector<Object*>& getObjects();

		std::vector<InvWall>& getInvWalls();

		std::vector<Texture>& getTextures();
		//getters and setters

		void LoadTextures();

		void Render(SDL_Rect camRect);

		void DetectColison(Player* player,UI *ui, Camera* camera);

		void CreateLevel();

		void RenderObjects(SDL_Rect camRect);

		void RenderObjectsPostPlayer(SDL_Rect camRect);

		~Map();
};
