#include <iostream>
#include <SDL.h>
#include <fstream>
#include <vector>
#include <string>
#include "Equipment.h"
#include "Player.h"
#include "Colision.h"

extern std::string levelName;

Equipment::Equipment(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

SDL_Texture* Equipment::GetTextureShortSword() {
    return textureShortSword;
}

void Equipment::SetTextureShortSword(SDL_Texture * temptex) {
    textureShortSword = temptex;
}

void Equipment::LoadEquipment() {
	ShortSword tempShortSword;
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "shortSword") {
				ShortSwords.push_back(tempShortSword);
				getline(levelFile, line);
				ShortSwords[ShortSwords.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				ShortSwords[ShortSwords.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				ShortSwords[ShortSwords.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				ShortSwords[ShortSwords.size() - 1].GetRectangle()->h = std::stoi(line);
			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Equipment::MoveEquipment(const Uint8* state, Player* player) {
	
}

void Equipment::DetectCollison(Player* player,SDL_Rect camRect) {
	for (int i = 0; i < ShortSwords.size(); i++)
	{
		if (SimpleCollision(camRect, *ShortSwords[i].GetRectangle())) {
			ShortSwords[i].SetRenderable(true);
		}
		else
		{
			ShortSwords[i].SetRenderable(false);
		}
	}
	for (int i = 0; i < ShortSwords.size(); i++)
	{
		switch (SimpleCollision(*player->GetRectangle(), *ShortSwords[i].GetRectangle()))
		{
		case 0:
			break;
		case 1:
			player->SetWeapon(ShortSwords[i].GetRectangle()->w, ShortSwords[i].GetRectangle()->h, 10, textureShortSword);
			ShortSwords.erase(ShortSwords.begin() + i);
			break;
		}
	}
}

void Equipment::Render(SDL_Rect camRect) {
	RenderShortSword(camRect);
}

void Equipment::RenderShortSword(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < ShortSwords.size(); i++)
	{
		if (ShortSwords[i].GetRenderable()) {
			temp.x = ShortSwords[i].GetRectangle()->x - camRect.x;
			temp.y = ShortSwords[i].GetRectangle()->y - camRect.y;
			temp.w = ShortSwords[i].GetRectangle()->w;
			temp.h = ShortSwords[i].GetRectangle()->h;

			SDL_RenderCopy(renderer, textureShortSword, NULL, &temp);
		}
	}
	
}


SDL_Rect* ShortSword::GetRectangle() {
    return &rectangle;
}

bool ShortSword::GetRenderable() { return renderable; }

void ShortSword::SetRenderable(bool temp) { renderable = temp; }

Equipment::~Equipment() {
	SDL_DestroyTexture(textureShortSword);
}
