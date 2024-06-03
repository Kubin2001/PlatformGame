#pragma once

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "UI.h"

class Player;


class MapObject {
	private:
		SDL_Rect rectangle;
		SDL_Texture* texture;

	public:
		SDL_Rect* GetRectangle();

		SDL_Texture* GetTexture();

		void SetTexture(SDL_Texture* temptex);
};


class Flag {
	private:
		SDL_Rect rectangle;

	public:
		SDL_Rect* GetRectangle();
};

class InvWall {
	private:
		SDL_Rect rectangle;

	public:
		SDL_Rect* GetRectangle();
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

		void Render();

		void DetectColison(Player* player,UI *ui);

		void MoveMap(const Uint8* state,Player *player);

		void CreateLevel();

		void RenderObjects();

		void RenderFlag();

		std::vector<MapObject> &getMapObjects();

		std::vector<Flag> &getFlag();

		std::vector<InvWall>& getInvWalls();


		~Map();
};
