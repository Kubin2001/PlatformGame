#include <iostream>
#include <fstream>
#include <string>

#include "Map.h"
#include "Player.h"
#include "Colision.h"
#include "UI.h"
#include "Camera.h"

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

SDL_Texture* Map::GetTexturePLatform2() { return texturePlatform2; }

void Map::SetTexturePlatform2(SDL_Texture* temptex) { texturePlatform2 = temptex; }

SDL_Texture* Map::GetTexturePilar() {return texturePillar;}

void Map::SetTexturePilar(SDL_Texture* temptex) {texturePillar = temptex;}

SDL_Texture* Map::GetTexturePilar2() { return texturePillar; }

void Map::SetTexturePilar2(SDL_Texture* temptex) { texturePillar2 = temptex; }

SDL_Texture* Map::GetTextureFlag() {return textureFlag;}

void Map::SetTextureFlag(SDL_Texture* temptex) {textureFlag = temptex;}

SDL_Texture* Map::GetTextureLava() { return textureFlag; }

void Map::SetTextureLava(SDL_Texture* temptex) { textureLava = temptex; }




//getters and setters

void Map::CreateLevel() {
	MapObject mapObject;
	Flag flag;
	InvWall invWall;
	Lava lava;
	std::ifstream levelFile(levelName);
	std::string line;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "platform" || line == "platform2" || line == "pillar" || line == "pillar2" || line == "grass") {
				MapObjects.push_back(mapObject);
				if (line == "platform") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePlatform);
				}
				else if (line == "platform2") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePlatform2);
				}
				else if (line == "pillar") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePillar);
				}
				else if (line == "pillar2") {
					MapObjects[MapObjects.size() - 1].SetTexture(texturePillar2);
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
			else if (line == "lava") {
				Lavas.push_back(lava);
				Lavas[Lavas.size() - 1].SetTexture(textureLava);
				getline(levelFile, line);
				Lavas[Lavas.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Lavas[Lavas.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Lavas[Lavas.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Lavas[Lavas.size() - 1].GetRectangle()->h = std::stoi(line);
			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Map::DetectColison(Player* player,UI *ui,Camera *camera) {
	for (int i = 0; i < MapObjects.size(); i++)
	{
		if (SimpleCollision(*camera->GetRectangle(), *MapObjects[i].GetRectangle())) {
			MapObjects[i].SetRenderable(true);
		}
		else
		{
			MapObjects[i].SetRenderable(false);
		}
	}
	for (int i = 0; i < Flags.size(); i++)
	{
		if (SimpleCollision(*camera->GetRectangle(), *Flags[i].GetRectangle())) {
			Flags[i].SetRenderable(true);
		}
		else
		{
			Flags[i].SetRenderable(false);
		}
	}

	for (int i = 0; i < Lavas.size(); i++)
	{
		if (SimpleCollision(*camera->GetRectangle(), *Lavas[i].GetRectangle())) {
			Lavas[i].SetRenderable(true);
		}
		else
		{
			Lavas[i].SetRenderable(false);
		}
	}

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

	for (int i = 0; i < Lavas.size(); i++)
	{
		if (SimpleCollision(*player->GetRectangle(), *Lavas[i].GetRectangle())){
			player->SetDamage(true);
			player->GetRectangle()->y -=3;
		}
	}

}

void Map::MoveMap(const Uint8* state,Player *player) {

}


void Map::RenderObjects(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < MapObjects.size(); i++)
	{
		if (MapObjects[i].GetRenderable()) {
			temp.x = MapObjects[i].GetRectangle()->x - camRect.x;
			temp.y = MapObjects[i].GetRectangle()->y - camRect.y;
			temp.w = MapObjects[i].GetRectangle()->w;
			temp.h = MapObjects[i].GetRectangle()->h;

			SDL_RenderCopy(renderer, MapObjects[i].GetTexture(), NULL, &temp);
		}
	}
}

void Map::RenderFlag(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Flags.size(); i++)
	{
		if (Flags[i].GetRenderable()) {
			temp.x = Flags[i].GetRectangle()->x - camRect.x;
			temp.y = Flags[i].GetRectangle()->y - camRect.y;
			temp.w = Flags[i].GetRectangle()->w;
			temp.h = Flags[i].GetRectangle()->h;

			SDL_RenderCopy(renderer, textureFlag, NULL, &temp);
		}
	}
}


void Map::RenderLava(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Lavas.size(); i++)
	{
		if (Lavas[i].GetRenderable()) {
			temp.x = Lavas[i].GetRectangle()->x - camRect.x;
			temp.y = Lavas[i].GetRectangle()->y - camRect.y;
			temp.w = Lavas[i].GetRectangle()->w;
			temp.h = Lavas[i].GetRectangle()->h;

			SDL_RenderCopy(renderer, textureLava, NULL, &temp);
		}
	}
}

void Map::Render(SDL_Rect camRect) {
	RenderObjects(camRect);
	RenderFlag(camRect);
	RenderLava(camRect);
	//for (int i = 0; i < InvWalls.size(); i++){
	//	SDL_RenderCopy(renderer, textureInvWall, NULL, InvWalls[i].GetRectangle());
	//}
}

SDL_Rect* Object::GetRectangle() { return &rectangle;}

bool Object::GetRenderable() { return renderable;}

void Object::SetRenderable(bool temp) { renderable = temp;}

std::vector<MapObject>& Map::getMapObjects() {
	return MapObjects;
}

std::vector<Flag>& Map::getFlag() {
	return Flags;
}

std::vector<InvWall>& Map::getInvWalls() {
	return InvWalls;
}



std::vector<Lava>& Map::getLavas() {
	return Lavas;
}

SDL_Texture* MapObject::GetTexture() { return texture; }

void MapObject::SetTexture(SDL_Texture* temptex) { texture = temptex; }

SDL_Texture* Lava::GetTexture() { return texture; }

void Lava::SetTexture(SDL_Texture* temptex) { texture = temptex; }


Map::~Map() {
	SDL_DestroyTexture(textureFloor);
	SDL_DestroyTexture(texturePlatform);
	SDL_DestroyTexture(texturePillar);
	SDL_DestroyTexture(textureFlag);
}