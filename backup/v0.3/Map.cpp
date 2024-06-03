#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "Player.h"

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


void Map::Render(SDL_Renderer* renderer) {
	RenderFloor(renderer);
	RenderPlatforms(renderer);
	RenderPilar(renderer);
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

void Map::MoveMap(const Uint8* state,Player *player) {
	int x = 0;

	for (int i = 0; i < Platforms.size(); i++)
	{
		if (Platforms[i].Colison(player) == true) {
			return;
		}
	}

	for (int i = 0; i < Pilars.size(); i++)
	{
		if (Pilars[i].Colison(player) == true) {
			return;
		}
	}
	
	if (state[SDL_SCANCODE_RIGHT]) {
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
	}
	if (state[SDL_SCANCODE_LEFT]) {
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

SDL_Rect* Platform::GetRectangle() {
	return &rectangle;
}


SDL_Rect* Pilar::GetRectangle() {
	return &rectangle;
}

bool Platform::Colison(Player* player) {

	if (player->GetRectangle()->x >= GetRectangle()->x - 35  && player->GetRectangle()->x + 10 <= GetRectangle()->x + 165
		&& player->GetRectangle()->y <= GetRectangle()->y && player->GetRectangle()->y >= GetRectangle()->y - 105) {

		if (player->GetRectangle()->y <= GetRectangle()->y + -90 && player->GetRectangle()->y >= GetRectangle()->y - 100) {
			player->setColison(true);
			return false;
		}

		if (player->GetRectangle()->y <= GetRectangle()->y && player->GetRectangle()->y >= GetRectangle()->y - 10) {
			player->setJumpBuffer(20);
			return false;
		}
		return true;
	}
	return false;
}



bool Pilar::Colison(Player *player) {
	
	if (player->GetRectangle()->x >=  GetRectangle()->x -40 && player->GetRectangle()->x +10 <= GetRectangle()->x + 40 
		&&  player->GetRectangle()->y <= GetRectangle()->y  + 120 && player->GetRectangle()->y >= GetRectangle()->y -105) {

		if (player->GetRectangle()->y <= GetRectangle()->y + -90 && player->GetRectangle()->y >= GetRectangle()->y - 100){
			player->setColison(true);
			return false;
		}
		if (player->GetRectangle()->y <= GetRectangle()->y +110 && player->GetRectangle()->y >= GetRectangle()->y + 100) {
			player->setJumpBuffer(20);
			return false;
		}
		return true;
	}
	return false;
}


