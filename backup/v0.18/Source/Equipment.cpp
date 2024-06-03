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
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
		for (int i = 0; i < ShortSwords.size(); i++)
		{
			ShortSwords[i].GetRectangle()->x -= 4;
		}
	}
	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < ShortSwords.size(); i++)
		{
			ShortSwords[i].GetRectangle()->x += 4;
		}
	}
	if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
		for (int i = 0; i < ShortSwords.size(); i++)
		{
			ShortSwords[i].GetRectangle()->y -= 5;
		}
	}
	if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
		for (int i = 0; i < ShortSwords.size(); i++)
		{
			ShortSwords[i].GetRectangle()->y += 5;
		}
	}
}

void Equipment::DetectCollison(Player* player) {
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

void Equipment::Render() {
	RenderShortSword();
}

void Equipment::RenderShortSword() {
	for (int i = 0; i < ShortSwords.size(); i++)
	{
		SDL_RenderCopy(renderer, textureShortSword, NULL, ShortSwords[i].GetRectangle());
	}
	
}


SDL_Rect* ShortSword::GetRectangle() {
    return &rectangle;
}

Equipment::~Equipment() {
	SDL_DestroyTexture(textureShortSword);
}
