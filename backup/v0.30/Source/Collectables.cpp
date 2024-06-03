#include <iostream>
#include <SDL.h>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>

#include "Collectables.h"
#include "Player.h"
#include "Colision.h"
#include "SoundManager.h"
#include "UI.h"
#include "TextureManager.h"

extern std::string levelName;

//Top Objects

SDL_Rect* CollectableWeapon::GetRectangle() {
	return &rectangle;
}

bool CollectableWeapon::GetRenderable() { return renderable; }

void CollectableWeapon::SetRenderable(bool temp) { renderable = temp; }

SDL_Texture* CollectableWeapon::GetTexture() {
	return texture;
}

void CollectableWeapon::SetTexture(SDL_Texture* temptex) {
	texture = temptex;
}


SDL_Rect* Pickable::GetRectangle() {
	return &rectangle;
}

bool Pickable::GetRenderable() { return renderable; }

void Pickable::SetRenderable(bool temp) { renderable = temp; }

SDL_Texture* Pickable::GetTexture() {
	return texture;
}

void Pickable::SetTexture(SDL_Texture* temptex) {
	texture = temptex;
}

bool Point::CollisionPlayer(Player* player, UI* ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		SoundManager::PlayCoinSound();
		ui->SetScore(ui->GetScore() + 10);
		return true;
	}
	return false;
}

bool MedKit::CollisionPlayer(Player* player, UI* ui) {
	if (SimpleCollision(*player->GetRectangle(), *GetRectangle())) {
		SoundManager::PlayMedKitSound();
		ui->AddHearth();
		return true;
	}
	return false;
}

//Main Objetct

Collectables::Collectables(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

//Getters and setters
std::vector<Texture>& Collectables::getTextures() {
	return Textures;
}
//Getters and setters

void Collectables::LoadTextures() {
	std::string directory = "Textures/Collectables";
	LoadMultipleTextures(Textures, directory, renderer);
}

void LoadObject(std::vector<CollectableWeapon*>& vec1, Texture& texture, std::ifstream& levelFile, std::string& line) {
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

void LoadObject(std::vector<Pickable*>& vec1, Texture& texture, std::ifstream& levelFile, std::string& line) {
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

void Collectables::LoadEquipment() {
	ShortSword tempShortSword;
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "shortSword") {
				Weapons.push_back(new ShortSword());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Weapons, it, levelFile, line);
					}
				}
			}
			else if (line == "coin") {
				Pickables.push_back(new Point());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Pickables, it, levelFile, line);
					}
				}
			}
			else if (line == "medKit") {
				Pickables.push_back(new MedKit());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Pickables, it, levelFile, line);
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

void Collectables::DetectCollison(UI * ui, Player* player,SDL_Rect camRect) {
	for (int i = 0; i < Weapons.size(); i++)
	{
		if (SimpleCollision(camRect, *Weapons[i]->GetRectangle())) {
			Weapons[i]->SetRenderable(true);
			if (SimpleCollision(*player->GetRectangle(), *Weapons[i]->GetRectangle()))
			{
				player->SetWeapon(Weapons[i]->GetRectangle()->w, Weapons[i]->GetRectangle()->h, 10, Weapons[i]->GetTexture());
				delete Weapons[i];
				Weapons.erase(Weapons.begin() + i);
			}
		}
		else
		{
			Weapons[i]->SetRenderable(false);
		}
	}
	for (int i = 0; i < Pickables.size(); i++)
	{
		if (SimpleCollision(camRect, *Pickables[i]->GetRectangle())) {
			Pickables[i]->SetRenderable(true);
			if (Pickables[i]->CollisionPlayer(player, ui)){
				delete Pickables[i];
				Pickables.erase(Pickables.begin() + i);
			}
		}
		else
		{
			Pickables[i]->SetRenderable(false);
		}
	}
}

void Collectables::Render(SDL_Rect camRect) {
	RenderCollectableWeapon(camRect);
	RenderPickables(camRect);
}

void Collectables::RenderCollectableWeapon(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Weapons.size(); i++)
	{
		if (Weapons[i]->GetRenderable()) {
			temp.x = Weapons[i]->GetRectangle()->x - camRect.x;
			temp.y = Weapons[i]->GetRectangle()->y - camRect.y;
			temp.w = Weapons[i]->GetRectangle()->w;
			temp.h = Weapons[i]->GetRectangle()->h;

			SDL_RenderCopy(renderer, Weapons[i]->GetTexture(), NULL, &temp);
		}
	}
	
}

void Collectables::RenderPickables(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Pickables.size(); i++)
	{
		if (Pickables[i]->GetRenderable()) {
			temp.x = Pickables[i]->GetRectangle()->x - camRect.x;
			temp.y = Pickables[i]->GetRectangle()->y - camRect.y;
			temp.w = Pickables[i]->GetRectangle()->w;
			temp.h = Pickables[i]->GetRectangle()->h;

			SDL_RenderCopy(renderer, Pickables[i]->GetTexture(), NULL, &temp);
		}
	}

}




Collectables::~Collectables() {
	for (auto it:Textures)
	{
		SDL_DestroyTexture(it.GetTexture());
	}
	for (auto weapon : Weapons) {
		delete weapon;
	}
	Weapons.clear();
	for (auto pickable : Pickables) {
		delete pickable;
	}
	Pickables.clear();
}
