#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "Mobs.h"
#include "Player.h"
#include "Colision.h"
#include "Map.h"

extern std::string levelName;

Mobs::Mobs(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

SDL_Rect* Enemy::GetRectangle() {
	return &rectangle;
}

int Enemy::getAnimation() {
	return animation;
}

void Enemy::setAnimation(int temp) {
	animation = temp;
}

int Enemy::getHitPoints() {
	return hitPoints;
}

void Enemy::setHitPoints(int temp) {
	hitPoints = temp;
}

void Enemy::setColison(bool value, int index) {
	if (index < 4) {
		colision[index] = value;
	}

}

bool Enemy::getColison(int index) {
	if (index < 4) {
		return colision[index];
	}

}

void Wolf::Movement(Player* player, Map* map) {
	if (cProj == nullptr) {
		switch (animation)
		{
			case 1:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y, 1, 1, 30, 0);
				break;
			case 2:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y, 1, 1, -30, 0);
				break;
		}
	}
	else
	{
		cProj->MoveProjectlile();
		for (int i = 0; i < map->getMapObjects().size(); i++)
		{
			if (SimpleCollision(*cProj->GetRectangle(), *map->getMapObjects()[i].GetRectangle()) == 1)
			{
				cProj->SetTimer(50);
				break;
			}
		}


		if (SimpleCollision(*cProj->GetRectangle(), *player->GetRectangle()) == 1) {
			cProj->SetTimer(50);
			if (agroo == 0) {
				agroo = 300;
			}
		}

		if (cProj->GetTimer() > 50) {
			delete cProj;
			cProj = nullptr;
		}
	}

	if (colision[0]) {
		movementtype = 2;
		animation = 1;
	}
	else if (colision[2])
	{
		movementtype = 1;
		animation = 2;
	}
	else if (colision[0] == true && colision[2] == true) {
		movementtype = 0;
	}

	switch (movementtype)
	{
	case 1:
		if (agroo > 0) {
			agroo--;
			GetRectangle()->x -= 5;
		}
		else
		{
			GetRectangle()->x--;
		}
		break;

	case 2:
		if (agroo > 0) {
			agroo--;
			GetRectangle()->x += 5;
		}
		else
		{
			GetRectangle()->x++;
		}
		break;
	}
}

void Charger::Movement(Player* player, Map* map) {
	if (colision[0]) {
		movementtype = 2;
		animation = 1;
	}
	else if(colision[2])
	{
		movementtype = 1;
		animation = 2;
	}
	else if (colision[0] == true && colision[2] == true) {
		movementtype = 0;
	}
	

	switch (movementtype)
	{
		case 1:
			GetRectangle()->x--;
			break;

		case 2:
			GetRectangle()->x++;
			break;

	}
	
}
//getters and setters
SDL_Texture* Mobs::GetTextureCharger() {
    return textureCharger;
}

void Mobs::SetTextureCharger(SDL_Texture* temptex) {
    textureCharger = temptex;
}

SDL_Texture* Mobs::GetTextureWolf() {
	return textureWolf;
}

void Mobs::SetTextureWolf(SDL_Texture* temptex) {
	textureWolf = temptex;
}

std::vector<Enemy*>& Mobs::getEnemies() { return Enemies; }

//getters and setters

void Mobs::LoadMobs() {
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "charger") {
				Enemies.push_back(new Charger());
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->h = std::stoi(line);
				Enemies[Enemies.size() - 1]->texture = textureCharger;
			}
			if (line == "wolf") {
				Enemies.push_back(new Wolf());
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->h = std::stoi(line);
				Enemies[Enemies.size() - 1]->texture = textureWolf;

			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Mobs::DetectColison(Player* player,Map *map) {
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->setColison(false, 0);
		Enemies[i]->setColison(false, 1);
		Enemies[i]->setColison(false, 2);

		for (int j = 0; j < map->getMapObjects().size(); j++)
		{
			switch (Collision(*Enemies[i]->GetRectangle(), *map->getMapObjects()[j].GetRectangle()))
			{
			case 1:
				Enemies[i]->setColison(true, 0);
				break;
			case 2:
				Enemies[i]->setColison(true, 1);
				break;
			case 3:
				Enemies[i]->setColison(true, 2);
				break;
			}
		}

		for (int j = 0; j < map->getInvWalls().size(); j++)
		{
			switch (Collision(*Enemies[i]->GetRectangle(), *map->getInvWalls()[j].GetRectangle()))
			{
			case 1:
				Enemies[i]->setColison(true, 0);
				break;
			case 2:
				Enemies[i]->setColison(true, 1);
				break;
			case 3:
				Enemies[i]->setColison(true, 2);
				break;
			}
		}

		if (Enemies[i]->getColison(1) == false) {
			Enemies[i]->GetRectangle()->y += 2;
		}

		switch (Collision(*player->GetRectangle(), *Enemies[i]->GetRectangle()))
		{
			case 1:
				player->setColison(true, 0);
				player->SetDamage(true);
				break;
			case 2:
				player->setColison(true, 1);
				player->setJumpBuffer(40);
				Enemies[i]->setHitPoints(Enemies[i]->getHitPoints() - 10);
				if (Enemies[i]->getHitPoints() < 1) {
					delete Enemies[i];
					Enemies.erase(Enemies.begin() + i);
				}
				break;
			case 3:
				player->setColison(true, 2);
				player->SetDamage(true);
				break;
		}
	}
}

void Mobs::MoveMobs(const Uint8* state, Player* player,Map *map) {
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
		for (int i = 0; i < Enemies.size(); i++)
		{
			Enemies[i]->GetRectangle()->x -= 4;
		}
	}
	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < Enemies.size(); i++)
		{
			Enemies[i]->GetRectangle()->x += 4;
		}
	}

	if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
		for (int i = 0; i < Enemies.size(); i++)
		{
			Enemies[i]->GetRectangle()->y -= 5;
		}	
	}
	if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
		for (int i = 0; i < Enemies.size(); i++)
		{
			Enemies[i]->GetRectangle()->y += 5;
		}
	}
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->Movement(player,map);
	}

}


void Mobs::RenderEnemies() {
	for (int i = 0; i < Enemies.size(); i++)
	{
		switch (Enemies[i]->getAnimation())
		{
			case 2:
				SDL_RenderCopy(renderer, Enemies[i]->texture, NULL, Enemies[i]->GetRectangle());
				break;

			case 1:
				SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
				SDL_RenderCopyEx(renderer, Enemies[i]->texture, NULL, Enemies[i]->GetRectangle(), 0.0, NULL, flip);
				break;
		}
	}
}

void Mobs::Render() {
	RenderEnemies();
}



Mobs::~Mobs() {
	SDL_DestroyTexture(textureCharger);
}
