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
		SDL_Texture* texture;

	public:
		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);
};


class Decoration : public Object {
	private:
		SDL_Texture* texture;

	public:
		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);
};


class Lava : public Object {
	private:
		SDL_Texture* texture;

	public:
		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);
};


class Flag : public Object  {
	private:

	public:
};

class InvWall : public Object {
	private:

	public:
};


class Map {
	private:
		SDL_Renderer* renderer = nullptr;

		std::vector<MapObject> MapObjects;
		std::vector<Decoration> Decorations;
		std::vector<Flag> Flags;
		std::vector<InvWall> InvWalls;

		std::vector<Lava> Lavas;

		SDL_Texture* texturePlatform = nullptr;
		SDL_Texture* texturePlatform2 = nullptr;
		SDL_Texture* texturePillar = nullptr;
		SDL_Texture* texturePillar2 = nullptr;
		SDL_Texture* textureFlag = nullptr;
		SDL_Texture* textureFloor = nullptr;
		SDL_Texture* textureLava = nullptr;

		SDL_Texture* texturePalmTree = nullptr;
		SDL_Texture* textureCactus = nullptr;
		SDL_Texture* textureBoulder = nullptr;
		SDL_Texture* textureBarrel = nullptr;
	
	public:
		//SDL_Texture* textureInvWall = nullptr;
		Map(SDL_Renderer* renderer);

		//getters and setters

		SDL_Texture* GetTextureFloor();

		void SetTextureFloor(SDL_Texture* temptex);

		SDL_Texture* GetTexturePLatform();

		void SetTexturePlatform(SDL_Texture* temptex);

		SDL_Texture* GetTexturePLatform2();

		void SetTexturePlatform2(SDL_Texture* temptex);

		SDL_Texture* GetTexturePilar();

		void SetTexturePilar(SDL_Texture* temptex);

		SDL_Texture* GetTexturePilar2();

		void SetTexturePilar2(SDL_Texture* temptex);

		SDL_Texture* GetTextureFlag();

		void SetTextureFlag(SDL_Texture* temptex);

		SDL_Texture* GetTextureLava();

		void SetTextureLava(SDL_Texture* temptex);

		SDL_Texture* GetTexturePalmTree();

		void SetTexturePalmTree(SDL_Texture* temptex);

		SDL_Texture* GetTextureCactus();

		void SetTextureCactus(SDL_Texture* temptex);

		SDL_Texture* GetTextureBoulder();

		void SetTextureBoulder(SDL_Texture* temptex);

		SDL_Texture* GetTextureBarrel();

		void SetTextureBarrel(SDL_Texture* temptex);

		//getters and setters

		void Render(SDL_Rect camRect);

		void DetectColison(Player* player,UI *ui, Camera* camera);

		void MoveMap(const Uint8* state,Player *player);

		void CreateLevel();

		void RenderDecorations(SDL_Rect camRect);

		void RenderObjects(SDL_Rect camRect);

		void RenderFlag(SDL_Rect camRect);

		void RenderLava(SDL_Rect camRect);

		std::vector<MapObject> &getMapObjects();

		std::vector<Decoration>& getDecorations();

		std::vector<Flag> &getFlag();

		std::vector<InvWall>& getInvWalls();

		std::vector<Lava>& getLavas();


		~Map();
};
