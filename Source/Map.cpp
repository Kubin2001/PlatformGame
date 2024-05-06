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
	for (int i = 0; i < MapObjects.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *MapObjects[i].GetRectangle()))
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
}

void Map::MoveMap(const Uint8* state,Player *player) {
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
		for (int i = 0; i < MapObjects.size(); i++)
		{
			MapObjects[i].GetRectangle()->x-=4;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->x -= 4;
		}
		for (int i = 0; i < InvWalls.size(); i++)
		{
			InvWalls[i].GetRectangle()->x -= 4;
		}
		player->setanimation(1);
	}
	

	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < MapObjects.size(); i++)
		{
			MapObjects[i].GetRectangle()->x += 4;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->x += 4;
		}
		for (int i = 0; i < InvWalls.size(); i++)
		{
			InvWalls[i].GetRectangle()->x += 4;
		}
		player->setanimation(2);
	}

	if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
		for (int i = 0; i < MapObjects.size(); i++)
		{
			MapObjects[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < InvWalls.size(); i++)
		{
			InvWalls[i].GetRectangle()->y -= 5;
		}
	}
	if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
		for (int i = 0; i < MapObjects.size(); i++)
		{
			MapObjects[i].GetRectangle()->y += 5;
		}

		for (int i = 0; i < Flags.size(); i++)
		{
			Flags[i].GetRectangle()->y += 5;
		}
		for (int i = 0; i < InvWalls.size(); i++)
		{
			InvWalls[i].GetRectangle()->y += 5;
		}
	}
}

void Map::CreateLevel(){
	MapObject mapObject;
	Flag flag;
	InvWall invWall;
	std::ifstream levelFile(levelName);
	std::string line;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "platform" || line == "pillar" || line == "grass") {
				MapObjects.push_back(mapObject);
				if (line == "platform") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePlatform);
				}
				else if (line == "pillar") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePillar);
				}
				else if (line == "grass") {
					MapObjects[MapObjects.size() - 1].SetTexture(textureFloor);
				}
				getline(levelFile, line);
				MapObjects[MapObjects.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				MapObjects[MapObjects.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				MapObjects[MapObjects.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				MapObjects[MapObjects.size() - 1].GetRectangle()->h = std::stoi(line);

			}
			else if (line == "flag") {
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
			else if (line == "invWall") {
				InvWalls.push_back(invWall);
				getline(levelFile, line);
				InvWalls[InvWalls.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				InvWalls[InvWalls.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				InvWalls[InvWalls.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				InvWalls[InvWalls.size() - 1].GetRectangle()->h = std::stoi(line);
			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Map::RenderObjects() {
	for (int i = 0; i < MapObjects.size(); i++)
	{
		SDL_RenderCopy(renderer, MapObjects[i].GetTexture(), NULL, MapObjects[i].GetRectangle());
	}
}

void Map::RenderFlag() {
	for (int i = 0; i < Flags.size(); i++)
	{
		SDL_RenderCopy(renderer, textureFlag, NULL, Flags[i].GetRectangle());
	}
}

void Map::Render() {
	RenderObjects();
	RenderFlag();
	//for (int i = 0; i < InvWalls.size(); i++){
	//	SDL_RenderCopy(renderer, textureInvWall, NULL, InvWalls[i].GetRectangle());
	//}
}


SDL_Rect* MapObject::GetRectangle() {
	return &rectangle;
}



SDL_Rect* Flag::GetRectangle() {
	return &rectangle;
}

SDL_Rect* InvWall::GetRectangle() {
	return &rectangle;
}


std::vector<MapObject>& Map::getMapObjects() {
	return MapObjects;
}



std::vector<Flag>& Map::getFlag() {
	return Flags;
}

std::vector<InvWall>& Map::getInvWalls() {
	return InvWalls;
}


SDL_Texture* MapObject::GetTexture() { return texture; }

void MapObject::SetTexture(SDL_Texture* temptex) { texture = temptex; }

Map::~Map() {
	SDL_DestroyTexture(textureFloor);
	SDL_DestroyTexture(texturePlatform);
	SDL_DestroyTexture(texturePillar);
	SDL_DestroyTexture(textureFlag);
}