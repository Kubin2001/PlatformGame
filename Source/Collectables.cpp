#include <iostream>
#include <SDL.h>
#include <fstream>
#include <vector>
#include <string>
#include "Collectables.h"
#include "Player.h"
#include "Colision.h"
#include "SoundManager.h"
#include "UI.h"

extern std::string levelName;

Collectables::Collectables(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

SDL_Texture* Collectables::GetTextureShortSword() {
    return textureShortSword;
}

void Collectables::SetTextureShortSword(SDL_Texture * temptex) {
    textureShortSword = temptex;
}

SDL_Texture* Collectables::GetTextureCoin() {
	return textureCoin;
}

void Collectables::SetTextureCoin(SDL_Texture* temptex) {
	textureCoin = temptex;
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
				getline(levelFile, line);
				Weapons[Weapons.size() - 1]->GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Weapons[Weapons.size() - 1]->GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Weapons[Weapons.size() - 1]->GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Weapons[Weapons.size() - 1]->GetRectangle()->h = std::stoi(line);
			}
			else if (line == "coin") {
				Pickables.push_back(new Pickable());
				getline(levelFile, line);
				Pickables[Pickables.size() - 1]->GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Pickables[Pickables.size() - 1]->GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Pickables[Pickables.size() - 1]->GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Pickables[Pickables.size() - 1]->GetRectangle()->h = std::stoi(line);
				Pickables[Pickables.size() - 1]->SetTexture(textureCoin);
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
			switch (SimpleCollision(*player->GetRectangle(), *Weapons[i]->GetRectangle()))
			{
				case 0:
					break;
				case 1:
					player->SetWeapon(Weapons[i]->GetRectangle()->w, Weapons[i]->GetRectangle()->h, 10, textureShortSword);
					delete Weapons[i];
					Weapons.erase(Weapons.begin() + i);
					break;
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
			switch (SimpleCollision(*player->GetRectangle(), *Pickables[i]->GetRectangle()))
			{
				case 0:
					break;
				case 1:
					SoundManager::PlayCoinSound();
					ui->SetScore(ui->GetScore() + 10);
					delete Pickables[i];
					Pickables.erase(Pickables.begin() + i);
					break;
			}
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

			SDL_RenderCopy(renderer, textureShortSword, NULL, &temp);
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


SDL_Rect* CollectableWeapon::GetRectangle() {
    return &rectangle;
}

bool CollectableWeapon::GetRenderable() { return renderable; }

void CollectableWeapon::SetRenderable(bool temp) { renderable = temp; }


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

Collectables::~Collectables() {
	SDL_DestroyTexture(textureShortSword);
	SDL_DestroyTexture(textureCoin);
}
