#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "UI.h"
#include "Camera.h"

class Player;

class Object {
	protected:
		SDL_Rect rectangle;
		bool renderable = false;

	public:
		SDL_Rect* GetRectangle();

		bool GetRenderable();

		void SetRenderable(bool temp);

};

class MapObject : public Object {
	private:
		SDL_Rect rectangle;
		SDL_Texture* texture;
		bool renderable = false;

	public:

		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);
};


class Flag : public Object  {
	private:
		SDL_Rect rectangle;
		bool renderable = false;

	public:
};

class InvWall : public Object {
	private:
		SDL_Rect rectangle;

	public:
};


class Map {
	private:
		SDL_Renderer* renderer = nullptr;

		std::vector<MapObject> MapObjects;
		std::vector<Flag> Flags;
		std::vector<InvWall> InvWalls;

		SDL_Texture* texturePlatform = nullptr;
		SDL_Texture* texturePillar = nullptr;
		SDL_Texture* textureFlag = nullptr;
		SDL_Texture* textureFloor = nullptr;
	
	public:
		//SDL_Texture* textureInvWall = nullptr;
		Map(SDL_Renderer* renderer);

		//getters and setters

		SDL_Texture* GetTextureFloor();

		void SetTextureFloor(SDL_Texture* temptex);

		SDL_Texture* GetTexturePLatform();

		void SetTexturePlatform(SDL_Texture* temptex);

		SDL_Texture* GetTexturePilar();

		void SetTexturePilar(SDL_Texture* temptex);

		SDL_Texture* GetTextureFlag();

		void SetTextureFlag(SDL_Texture* temptex);

		SDL_Rect* GetRectangle(int index);
		//getters and setters

		void Render(SDL_Rect camRect);

		void DetectColison(Player* player,UI *ui, Camera* camera);

		void MoveMap(const Uint8* state,Player *player);

		void CreateLevel();

		void RenderObjects(SDL_Rect camRect);

		void RenderFlag(SDL_Rect camRect);

		std::vector<MapObject> &getMapObjects();

		std::vector<Flag> &getFlag();

		std::vector<InvWall>& getInvWalls();


		~Map();
};
