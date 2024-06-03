#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "Map.h"
#include "Player.h"
#include "Colision.h"
#include "UI.h"
#include "Camera.h"
#include "SoundManager.h"
#include "TextureManager.h"

extern int windowtype;
extern int localWindow;
extern std::string levelName;

extern SDL_Texture* load(const char* file, SDL_Renderer* ren);

//Top Objects

SDL_Rect* Object::GetRectangle() { return &rectangle; }

bool Object::GetRenderable() { return renderable; }

void Object::SetRenderable(bool temp) { renderable = temp; }

SDL_Texture* Object::GetTexture() { return texture; }

void Object::SetTexture(SDL_Texture* temptex) { texture = temptex; }


void MapObject::PlayerCollision(Player* player, UI* ui) {
	switch (Collision(*player->GetRectangle(), *GetRectangle()))
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

void Decoration::PlayerCollision(Player* player, UI* ui) {

}

void Lava::PlayerCollision(Player* player, UI* ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		player->SetDamage(true);
		player->GetRectangle()->y -= 3;
	}
}

void Flag::PlayerCollision(Player* player,UI * ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		SoundManager::PlayPlayerWinSound();
		ui->CreateButtonInfo(550, 250, 300, 100, "YOU WON", 30, 31);
		SDL_Delay(4000);
		localWindow = 1;
	}
}


void MapObject::MobCollision(Enemy* enemy) {
	switch (Collision(*enemy->GetRectangle(), *GetRectangle()))
	{
	case 1:
		enemy->setColison(true, 0);
		break;
	case 2:
		enemy->setColison(true, 1);
		break;
	case 3:
		enemy->setColison(true, 2);
		break;
	}
	
}
void Decoration::MobCollision(Enemy* enemy) {

}
void Lava::MobCollision(Enemy* enemy) {
	if (SimpleCollision(*enemy->GetRectangle(), *GetRectangle()))
	{
		enemy->setHitPoints(enemy->getHitPoints() - 10);
		enemy->setInvTime(20);
	}
}

void Flag::MobCollision(Enemy* enemy) {

}

SDL_Rect* InvWall::GetRectangle() { return &rectangle; }

bool InvWall::GetRenderable() { return renderable; }

void InvWall::SetRenderable(bool temp) { renderable = temp; }
//Top Objects

Map::Map(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
//getters and setters
std::vector<Object*>& Map::getObjects() {
	return Objects;
}


std::vector<InvWall>& Map::getInvWalls() {
	return InvWalls;
}

std::vector<Texture>& Map::getTextures() {
	return Textures;
}

//getters and setters

void Map::LoadTextures() {
	Texture temp;
	std::string directory = "Textures/Terrain";
	std::string directory2 = "Textures/Decorations";
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.path().extension() == ".png") {
			std::string pathString = entry.path().string();
			const char* path = pathString.c_str();
			Textures.push_back(temp);
			Textures[Textures.size() - 1].SetTexture(load(path, renderer));
			std::string temp = "";
			for (size_t i = directory.length(); i < pathString.length(); i++)
			{
				if (pathString[i + 1] == '.') {
					break;
				}
				temp += pathString[i + 1];
			}
			Textures[Textures.size() - 1].SetName(temp);
			temp = "";
		}
	}

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory2)) {
		if (entry.path().extension() == ".png") {
			std::string pathString = entry.path().string();
			const char* path = pathString.c_str();
			Textures.push_back(temp);
			Textures[Textures.size() - 1].SetTexture(load(path, renderer));
			std::string temp = "";
			for (size_t i = directory2.length(); i < pathString.length(); i++)
			{
				if (pathString[i + 1] == '.') {
					break;
				}
				temp += pathString[i + 1];
			}
			Textures[Textures.size() - 1].SetName(temp);
			temp = "";
		}
	}
}

void LoadObject(std::vector<Object*>& vec1, Texture& texture,std::ifstream &levelFile,std::string &line) {
	vec1[vec1.size() - 1]->SetTexture(texture.GetTexture());
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->x = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->y = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->w = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->h = std::stoi(line);
}

void Map::CreateLevel() {
	InvWall invWall;
	std::ifstream levelFile(levelName);
	std::string line;
	int decorationCount = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "palmTree" || line == "cactus" || line == "boulder" || line == "barrel") {
				Objects.push_back(new Decoration());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Objects, Textures[i], levelFile, line);
						std::swap(Objects[Objects.size() - 1], Objects[decorationCount]);
						decorationCount++;
					}
				}
			}
			else if (line == "platform" || line == "platform2" || line == "pillar" || line == "pillar2" || line == "grass") {
				Objects.push_back(new MapObject());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Objects, Textures[i], levelFile, line);
					}
				}
			}
			else if (line == "flag") {
				Objects.push_back(new Flag());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Objects, Textures[i], levelFile, line);
					}
				}
			}
			else if (line == "lava") {
				Objects.push_back(new Lava());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Objects, Textures[i], levelFile, line);
					}
				}
				postPlayerRenderables.push_back(Objects[Objects.size() - 1]);

			}
			else if (line == "invWall") {
				InvWalls.push_back(invWall);
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
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
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Map::DetectColison(Player* player, UI* ui, Camera* camera) {
	for (int i = 0; i < Objects.size(); i++)
	{
		if (SimpleCollision(*camera->GetRectangle(), *Objects[i]->GetRectangle())) {
			Objects[i]->SetRenderable(true);
			Objects[i]->PlayerCollision(player,ui);
		}
		else
		{
			Objects[i]->SetRenderable(false);
		}
	}
}

void Map::RenderObjects(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->GetRenderable()) {
			temp.x = Objects[i]->GetRectangle()->x - camRect.x;
			temp.y = Objects[i]->GetRectangle()->y - camRect.y;
			temp.w = Objects[i]->GetRectangle()->w;
			temp.h = Objects[i]->GetRectangle()->h;

			SDL_RenderCopy(renderer, Objects[i]->GetTexture(), NULL, &temp);
		}
	}
}

void Map::RenderObjectsPostPlayer(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i <postPlayerRenderables.size(); i++)
	{
		if (postPlayerRenderables[i]->GetRenderable()) {
			temp.x = postPlayerRenderables[i]->GetRectangle()->x - camRect.x;
			temp.y = postPlayerRenderables[i]->GetRectangle()->y - camRect.y;
			temp.w = postPlayerRenderables[i]->GetRectangle()->w;
			temp.h = postPlayerRenderables[i]->GetRectangle()->h;

			SDL_RenderCopy(renderer, postPlayerRenderables[i]->GetTexture(), NULL, &temp);
		}
	}
}

void Map::Render(SDL_Rect camRect) {
	RenderObjects(camRect);
	//for (int i = 0; i < InvWalls.size(); i++){
	//	SDL_RenderCopy(renderer, textureInvWall, NULL, InvWalls[i].GetRectangle());
	//}
}


Map::~Map() {
	for (auto it:Textures)
	{
		SDL_DestroyTexture(it.GetTexture());
	}
	for (auto object : Objects) {
		delete object;
	}
	Objects.clear();

}