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

void DangerousObject::PlayerCollision(Player* player, UI* ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		player->SetDamage(true);
		if (floating) {
			player->GetRectangle()->y -= 3;
		}
	}
}

void Flag::PlayerCollision(Player* player,UI * ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		SoundManager::PlayPlayerWinSound();
		ui->CreateButtonInfo(550, 250, 300, 100, "YOU WON/SCORE:" + std::to_string(ui->GetScore()), 30, 31);
		SDL_Delay(4000);
		std::ifstream scoreFile("Data/HighScores/level1_score.txt");
		std::string line = "";
		int counter = 1;
		std::vector<int> lines;
		if (scoreFile.is_open()) {
			while (getline(scoreFile, line)) {
				if (counter < 10) {
					lines.push_back(std::stoi(line));
				}
				counter++;
			}
		}

		for (int i = 0; i <lines.size(); i++)
		{
			if (ui->GetScore() > lines[i]) {
				lines[i] = ui->GetScore();
				break;
			}
		}

		std::sort(lines.rbegin(), lines.rend());

		std::ofstream outFile("Data/HighScores/level1_score.txt");
		if (outFile.is_open()) {
			for (int it : lines) {
				outFile << it << "\n";
			}
			outFile.close();
		}
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
void DangerousObject::MobCollision(Enemy* enemy) {
	if (SimpleCollision(*enemy->GetRectangle(), *GetRectangle()))
	{
		enemy->setHitPoints(enemy->getHitPoints() - damage);
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
	std::string directory = "Textures/Terrain";
	std::string directory2 = "Textures/Decorations";

	LoadMultipleTextures(Textures, directory, renderer);
	LoadMultipleTextures(Textures, directory2, renderer);
	
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
				for (auto &it : Textures) {
					if (it.GetName() == line) {
						LoadObject(Objects, it, levelFile, line);
						std::swap(Objects[Objects.size() - 1], Objects[decorationCount]);
						decorationCount++;
					}
				}
			}
			else if (line == "platform" || line == "platform2" || line == "platform3" || line == "pillar" 
				|| line == "pillar2" || line == "pillar3" || line == "grass") {
				Objects.push_back(new MapObject());
				for (auto &it : Textures) {
					if (it.GetName() == line) {
						LoadObject(Objects, it, levelFile, line);
					}
				}
			}
			else if (line == "flag") {
				Objects.push_back(new Flag());
				for (auto &it : Textures) {
					if (it.GetName() == line) {
						LoadObject(Objects, it, levelFile, line);
					}
				}
			}
			else if (line == "lava" || line == "spikes") {
				if (line == "lava") {
					Objects.push_back(new DangerousObject(10, true));
				}
				else if (line == "spikes")
				{
					Objects.push_back(new DangerousObject(10, false));
				}
				for (auto &it : Textures) {
					if (it.GetName() == line) {
						LoadObject(Objects, it, levelFile, line);
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
	for (const auto& it : Objects) {
		if (SimpleCollision(*camera->GetRectangle(), *it->GetRectangle())) {
			it->SetRenderable(true);
			it->PlayerCollision(player,ui);
		}
		else
		{
			it->SetRenderable(false);
		}
	}
}

void Map::RenderObjects(SDL_Rect camRect) {
	SDL_Rect temp;
	for (const auto& it : Objects) {
		if (it->GetRenderable()) {
			temp.x = it->GetRectangle()->x - camRect.x;
			temp.y = it->GetRectangle()->y - camRect.y;
			temp.w = it->GetRectangle()->w;
			temp.h = it->GetRectangle()->h;

			SDL_RenderCopy(renderer, it->GetTexture(), NULL, &temp);
		}
	}
}

void Map::RenderObjectsPostPlayer(SDL_Rect camRect) {
	SDL_Rect temp;
	for(const auto &it: postPlayerRenderables){
		if (it->GetRenderable()) {
			temp.x = it->GetRectangle()->x - camRect.x;
			temp.y = it->GetRectangle()->y - camRect.y;
			temp.w = it->GetRectangle()->w;
			temp.h = it->GetRectangle()->h;

			SDL_RenderCopy(renderer, it->GetTexture(), NULL, &temp);
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