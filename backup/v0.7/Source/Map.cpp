#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "Player.h"
#include "Colision.h"

SDL_Texture* Map::GetTextureGrass() {
	return textureGrass;
}

void Map::SetTextureGrass(SDL_Texture* temptex) {
	textureGrass = temptex;
}

SDL_Texture* Map::GetTexturePLatform() {
	return texturePlatform;
}

void Map::SetTexturePlatform(SDL_Texture* temptex) {
	texturePlatform = temptex;
}

SDL_Texture* Map::GetTexturePilar() {
	return texturePilar;
}

void Map::SetTexturePilar(SDL_Texture* temptex) {
	texturePilar = temptex;
}

SDL_Rect* Map::GetRectangle(int index) {
	return &rectanglesGrass[index];
}

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

void Map::DetectColison(Player* player) {
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

	for (int i = 0; i < Pilars.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *Pilars[i].GetRectangle()))
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
		for (int i = 0; i < Pilars.size(); i++)
		{
			Pilars[i].GetRectangle()->x -= 4;
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
		for (int i = 0; i < Pilars.size(); i++)
		{
			Pilars[i].GetRectangle()->x += 4;
		}
		player->setanimation(2);
	}
}

void Map::CreateLevel() {
	Pilar pilar;
	Platform platform;
	std::ifstream levelFile("Levels/level1.txt");
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
					Pilars.push_back(pilar);
					Pilars[Pilars.size() - 1].GetRectangle()->x = xCord;
					Pilars[Pilars.size() - 1].GetRectangle()->y = yCord;
					Pilars[Pilars.size() - 1].GetRectangle()->w = 40;
					Pilars[Pilars.size() - 1].GetRectangle()->h = 160;
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

void Map::RenderFloor(SDL_Renderer* renderer) {
	for (int i = 0; i < 37; i++)
	{
		SDL_RenderCopy(renderer, textureGrass, NULL, &rectanglesGrass[i]);
	}
}

void Map::RenderPlatforms(SDL_Renderer *renderer) {
	for (int i = 0; i < Platforms.size(); i++)
	{
		SDL_RenderCopy(renderer, texturePlatform, NULL, Platforms[i].GetRectangle());
	}
}

void Map::RenderPilar(SDL_Renderer* renderer) {
	for (int i = 0; i < Pilars.size(); i++)
	{
		SDL_RenderCopy(renderer, texturePilar, NULL, Pilars[i].GetRectangle());
	}
}

void Map::Render(SDL_Renderer* renderer) {
	RenderFloor(renderer);
	RenderPlatforms(renderer);
	RenderPilar(renderer);
}

SDL_Rect* Platform::GetRectangle() {
	return &rectangle;
}


SDL_Rect* Pilar::GetRectangle() {
	return &rectangle;
}


std::vector<Pilar> &Map::getPillar() {
	return Pilars;
}


std::vector<Platform>& Map::getPlatform() {
	return Platforms;
}