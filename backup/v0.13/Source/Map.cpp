#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "Player.h"
#include "Colision.h"
#include "UI.h"

extern int windowtype;
extern std::string levelName;

Map::Map(SDL_Renderer *renderer) {
	this->renderer = renderer;
}
//getters and setters
SDL_Texture* Map::GetTextureGrass() {return textureGrass;}

void Map::SetTextureGrass(SDL_Texture* temptex) {textureGrass = temptex;}

SDL_Texture* Map::GetTexturePLatform() {return texturePlatform;}

void Map::SetTexturePlatform(SDL_Texture* temptex) {texturePlatform = temptex;}

SDL_Texture* Map::GetTexturePilar() {return texturePillar;}

void Map::SetTexturePilar(SDL_Texture* temptex) {texturePillar = temptex;}

SDL_Texture* Map::GetTextureFlag() {return textureFlag;}

void Map::SetTextureFlag(SDL_Texture* temptex) {textureFlag = temptex;}

SDL_Rect* Map::GetRectangle(int index) {return &rectanglesGrass[index];}

//getters and setters

void Map::CreateFloor() {
	int x = 0;
	for (int i = 0; i < 37; i++)
	{
		GetRectangle(i)->x = x;
		GetRectangle(i)->y = 760;
		GetRectangle(i)->w = 40;
		GetRectangle(i)->h = 40;
		x += 40;
	}
}

void Map::DetectColison(Player* player,UI *ui) {
	for (int i = 0; i < Platforms.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *Platforms[i].GetRectangle()))
		{
		case 1:
			player->setColison(true, 0);
			break;
		case 2:
			player->setColison(true, 1);
			break;
		case 3:
			player->setColison(true, 2);
			break;
		case 4:
			player->setColison(true, 3);
			player->setJumpBuffer(20);
			break;
		}
	}

	for (int i = 0; i < Pillars.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *Pillars[i].GetRectangle()))
		{
		case 1:
			player->setColison(true, 0);
			break;
		case 2:
			player->setColison(true, 1);
			break;
		case 3:
			player->setColison(true, 2);
			break;
		case 4:
			player->setColison(true, 3);
			player->setJumpBuffer(20);
			break;
		}
	}
	for (int i = 0; i < Flags.size(); i++)
	{
		switch (Collision(*Flags[i].GetRectangle(), *player->GetRectangle()))
		{
		case 3:
			ui->CreateButtonInfo(550, 250, 300, 100, "YOU WON", 30, 31);
			SDL_Delay(4000);
			windowtype = 1;
			break;
		}
	}
	if (player->GetRectangle()->y >= 660) {
		player->setColison(true, 1);
	}
}

void Map::MoveMap(const Uint8* state,Player *player) {
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
		for (int i = 0; i < 37; i++)
		{
			if (GetRectangle(i)->x < -40) {
				GetRectangle(i)->x = 1400;
			}
		}
		for (int i = 0; i < 37; i++)
		{
			GetRectangle(i)->x -=4;
		}
		for (int i = 0; i < Platforms.size(); i++)
		{
			Platforms[i].GetRectangle()->x-=4;
		}
		for (int i = 0; i < Pillars.size(); i++)
		{
			Pillars[i].GetRectangle()->x -= 4;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->x -= 4;
		}
		player->setanimation(1);
	}
	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < 37; i++)
		{
			if (GetRectangle(i)->x > 1400) {
				GetRectangle(i)->x = -40;
			}
		}
		for (int i = 0; i < 37; i++)
		{
			GetRectangle(i)->x += 4;
		}
		for (int i = 0; i < Platforms.size(); i++)
		{
			Platforms[i].GetRectangle()->x += 4;
		}
		for (int i = 0; i < Pillars.size(); i++)
		{
			Pillars[i].GetRectangle()->x += 4;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->x += 4;
		}
		player->setanimation(2);
	}
}

void Map::CreateLevel() {
	Pillar pilar;
	Platform platform;
	Flag flag;
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			yCord += 40;
			for (size_t i = 0; i < line.length(); i++)
			{
				xCord += 40;
				if (line[i] == '1') {
					Platforms.push_back(platform);
					Platforms[Platforms.size()-1].GetRectangle()->x = xCord;
					Platforms[Platforms.size()-1].GetRectangle()->y = yCord;
					Platforms[Platforms.size()-1].GetRectangle()->w = 160;
					Platforms[Platforms.size()-1].GetRectangle()->h = 40;
				}
				else if (line[i] == '2') {
					Pillars.push_back(pilar);
					Pillars[Pillars.size() - 1].GetRectangle()->x = xCord;
					Pillars[Pillars.size() - 1].GetRectangle()->y = yCord;
					Pillars[Pillars.size() - 1].GetRectangle()->w = 40;
					Pillars[Pillars.size() - 1].GetRectangle()->h = 160;
				}
				else if (line[i] == '3') {
					Flags.push_back(flag);
					Flags[Flags.size() - 1].GetRectangle()->x = xCord;
					Flags[Flags.size() - 1].GetRectangle()->y = yCord;
					Flags[Flags.size() - 1].GetRectangle()->w = 40;
					Flags[Flags.size() - 1].GetRectangle()->h = 160;
				}
			}
			xCord = 0;
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Map::RenderFloor() {
	for (int i = 0; i < 37; i++)
	{
		SDL_RenderCopy(renderer, textureGrass, NULL, &rectanglesGrass[i]);
	}
}

void Map::RenderPlatforms() {
	for (int i = 0; i < Platforms.size(); i++)
	{
		SDL_RenderCopy(renderer, texturePlatform, NULL, Platforms[i].GetRectangle());
	}
}

void Map::RenderPillar() {
	for (int i = 0; i < Pillars.size(); i++)
	{
		SDL_RenderCopy(renderer, texturePillar, NULL, Pillars[i].GetRectangle());
	}
}

void Map::RenderFlag() {
	for (int i = 0; i < Flags.size(); i++)
	{
		SDL_RenderCopy(renderer, textureFlag, NULL, Flags[i].GetRectangle());
	}
}

void Map::Render() {
	RenderFloor();
	RenderPlatforms();
	RenderPillar();
	RenderFlag();
}


SDL_Rect* Platform::GetRectangle() {
	return &rectangle;
}


SDL_Rect* Pillar::GetRectangle() {
	return &rectangle;
}

SDL_Rect* Flag::GetRectangle() {
	return &rectangle;
}


std::vector<Pillar>& Map::getPillar() {
	return Pillars;
}


std::vector<Platform>& Map::getPlatform() {
	return Platforms;
}

std::vector<Flag>& Map::getFlag() {
	return Flags;
}


Map::~Map() {
	SDL_DestroyTexture(textureGrass);
	SDL_DestroyTexture(texturePlatform);
	SDL_DestroyTexture(texturePillar);
	SDL_DestroyTexture(textureFlag);
}