#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "Player.h"
#include "Colision.h"
#include "UI.h"

extern int windowtype;
extern int localWindow;
extern std::string levelName;

Map::Map(SDL_Renderer *renderer) {
	this->renderer = renderer;
}
//getters and setters
SDL_Texture* Map::GetTextureFloor() {return textureFloor;}

void Map::SetTextureFloor(SDL_Texture* temptex) {textureFloor = temptex;}

SDL_Texture* Map::GetTexturePLatform() {return texturePlatform;}

void Map::SetTexturePlatform(SDL_Texture* temptex) {texturePlatform = temptex;}

SDL_Texture* Map::GetTexturePilar() {return texturePillar;}

void Map::SetTexturePilar(SDL_Texture* temptex) {texturePillar = temptex;}

SDL_Texture* Map::GetTextureFlag() {return textureFlag;}

void Map::SetTextureFlag(SDL_Texture* temptex) {textureFlag = temptex;}


//getters and setters

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
			localWindow = 1;
			break;
		}
	}

	for (int i = 0; i < Floors.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *Floors[i].GetRectangle()))
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
}

void Map::MoveMap(const Uint8* state,Player *player) {
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
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
		for (int i = 0; i < Floors.size(); i++)
		{
			Floors[i].GetRectangle()->x -= 4;
		}
		player->setanimation(1);
	}
	

	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
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
		for (int i = 0; i < Floors.size(); i++)
		{
			Floors[i].GetRectangle()->x += 4;
		}
		player->setanimation(2);
	}

	if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
		for (int i = 0; i < Platforms.size(); i++)
		{
			Platforms[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < Pillars.size(); i++)
		{
			Pillars[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < Floors.size(); i++)
		{
			Floors[i].GetRectangle()->y -= 5;
		}
	}
	if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
		for (int i = 0; i < Platforms.size(); i++)
		{
			Platforms[i].GetRectangle()->y += 5;
		}
		for (int i = 0; i < Pillars.size(); i++)
		{
			Pillars[i].GetRectangle()->y += 5;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->y += 5;
		}
		for (int i = 0; i < Floors.size(); i++)
		{
			Floors[i].GetRectangle()->y += 5;
		}
	}
}

void Map::CreateLevel() {
	Pillar pillar;
	Platform platform;
	Flag flag;
	Floor floor;
	std::ifstream levelFile(levelName);
	std::string line;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "platform") {
				Platforms.push_back(platform);
				getline(levelFile, line);
				Platforms[Platforms.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Platforms[Platforms.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Platforms[Platforms.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Platforms[Platforms.size() - 1].GetRectangle()->h = std::stoi(line);
			}
			if (line == "pillar") {
				Pillars.push_back(pillar);
				getline(levelFile, line);
				Pillars[Pillars.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Pillars[Pillars.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Pillars[Pillars.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Pillars[Pillars.size() - 1].GetRectangle()->h = std::stoi(line);

			}
			if (line == "grass") {
				Floors.push_back(floor);
				getline(levelFile, line);
				Floors[Floors.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Floors[Floors.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Floors[Floors.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Floors[Floors.size() - 1].GetRectangle()->h = std::stoi(line);

			}
			if (line == "flag") {
				Flags.push_back(flag);
				getline(levelFile, line);
				Flags[Flags.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Flags[Flags.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Flags[Flags.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Flags[Flags.size() - 1].GetRectangle()->h = std::stoi(line);

			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
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

void Map::RenderFloor() {
	for (int i = 0; i < Floors.size(); i++)
	{
		SDL_RenderCopy(renderer, textureFloor, NULL, Floors[i].GetRectangle());
	}
}

void Map::Render() {
	RenderFloor();
	RenderPlatforms();
	RenderPillar();
	RenderFlag();
	RenderFloor();
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

SDL_Rect* Floor::GetRectangle() {
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

std::vector<Floor>& Map::getFloor() {
	return Floors;
}


Map::~Map() {
	SDL_DestroyTexture(textureFloor);
	SDL_DestroyTexture(texturePlatform);
	SDL_DestroyTexture(texturePillar);
	SDL_DestroyTexture(textureFlag);
}