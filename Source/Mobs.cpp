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

void Charger::Movement() {
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

std::vector<Charger>& Mobs::getChargers() { return Chargers; }

std::vector<Wolf>& Mobs::getWolfs() { return Wolfs; }
//getters and setters

void Mobs::LoadMobs() {
	Charger charger;
	Wolf wolf;
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "charger") {
				Chargers.push_back(charger);
				getline(levelFile, line);
				Chargers[Chargers.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Chargers[Chargers.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Chargers[Chargers.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Chargers[Chargers.size() - 1].GetRectangle()->h = std::stoi(line);
			}
			if (line == "wolf") {
				Wolfs.push_back(wolf);
				getline(levelFile, line);
				Wolfs[Wolfs.size() - 1].GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Wolfs[Wolfs.size() - 1].GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Wolfs[Wolfs.size() - 1].GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Wolfs[Wolfs.size() - 1].GetRectangle()->h = std::stoi(line);

			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Mobs::DetectColison(Player* player,Map *map) {
	for (int i = 0; i < Chargers.size(); i++)
	{
		Chargers[i].setColison(false, 0);
		Chargers[i].setColison(false, 1);
		Chargers[i].setColison(false, 2);

		for (int j = 0; j < map->getMapObjects().size(); j++)
		{
			switch (Collision(*Chargers[i].GetRectangle(), *map->getMapObjects()[j].GetRectangle()))
			{
			case 1:
				Chargers[i].setColison(true, 0);
				break;
			case 2:
				Chargers[i].setColison(true, 1);
				break;
			case 3:
				Chargers[i].setColison(true, 2);
				break;
			}
		}

		for (int j = 0; j < map->getInvWalls().size(); j++)
		{
			switch (Collision(*Chargers[i].GetRectangle(), *map->getInvWalls()[j].GetRectangle()))
			{
			case 1:
				Chargers[i].setColison(true, 0);
				break;
			case 2:
				Chargers[i].setColison(true, 1);
				break;
			case 3:
				Chargers[i].setColison(true, 2);
				break;
			}
		}


		if (Chargers[i].getColison(1) == false) {
			Chargers[i].GetRectangle()->y += 2;
		}


		switch (Collision(*player->GetRectangle(), *Chargers[i].GetRectangle()))
		{
			case 1:
				player->setColison(true, 0);
				player->SetDamage(true);
				break;
			case 2:
				player->setColison(true, 1);
				player->setJumpBuffer(40);
				Chargers[i].setHitPoints(Chargers[i].getHitPoints() - 10);
				if (Chargers[i].getHitPoints() < 1) {
					Chargers.erase(Chargers.begin() + i);
				}
				break;
			case 3:
				player->setColison(true, 2);
				player->SetDamage(true);
				break;
			}
	}

	for (int i = 0; i < Wolfs.size(); i++)
	{
		Wolfs[i].setColison(false, 0);
		Wolfs[i].setColison(false, 1);
		Wolfs[i].setColison(false, 2);

		for (int j = 0; j < map->getMapObjects().size(); j++)
		{
			switch (Collision(*Wolfs[i].GetRectangle(), *map->getMapObjects()[j].GetRectangle()))
			{
			case 1:
				Wolfs[i].setColison(true, 0);
				break;
			case 2:
				Wolfs[i].setColison(true, 1);
				break;
			case 3:
				Wolfs[i].setColison(true, 2);
				break;
			}
		}

		for (int j = 0; j < map->getInvWalls().size(); j++)
		{
			switch (Collision(*Wolfs[i].GetRectangle(), *map->getInvWalls()[j].GetRectangle()))
			{
			case 1:
				Wolfs[i].setColison(true, 0);
				break;
			case 2:
				Wolfs[i].setColison(true, 1);
				break;
			case 3:
				Wolfs[i].setColison(true, 2);
				break;
			}
		}

		if (Wolfs[i].getColison(1) == false) {
			Wolfs[i].GetRectangle()->y += 2;
		}


		switch (Collision(*player->GetRectangle(), *Wolfs[i].GetRectangle()))
		{
		case 1:
			player->setColison(true, 0);
			player->SetDamage(true);
			break;
		case 2:
			player->setColison(true, 1);
			player->setJumpBuffer(40);
			Wolfs[i].setHitPoints(Wolfs[i].getHitPoints() - 10);
			if (Wolfs[i].getHitPoints() < 1) {
				Wolfs.erase(Wolfs.begin() + i);
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
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->x -= 4;
		}
		for (int i = 0; i < Wolfs.size(); i++)
		{
			Wolfs[i].GetRectangle()->x -= 4;
		}
	}
	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->x += 4;
		}
		for (int i = 0; i < Wolfs.size(); i++)
		{
			Wolfs[i].GetRectangle()->x += 4;
		}
	}

	if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->y -= 5;
		}
		for (int i = 0; i < Wolfs.size(); i++)
		{
			Wolfs[i].GetRectangle()->y -= 5;
		}
		
	}
	if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->y += 5;
		}
		for (int i = 0; i < Wolfs.size(); i++)
		{
			Wolfs[i].GetRectangle()->y += 5;
		}
	}
	for (int i = 0; i < Chargers.size(); i++)
	{
		Chargers[i].Movement();
	}

	for (int i = 0; i < Wolfs.size(); i++)
	{
		Wolfs[i].Movement(player,map);
	}
}


void Mobs::RenderChargers() {
	for (int i = 0; i < Chargers.size(); i++)
	{
		switch (Chargers[i].getAnimation())
		{
			case 2:
				SDL_RenderCopy(renderer, textureCharger, NULL, Chargers[i].GetRectangle());
				break;

			case 1:
				SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
				SDL_RenderCopyEx(renderer, textureCharger, NULL, Chargers[i].GetRectangle(), 0.0, NULL, flip);
				break;
		}
	}
}

void Mobs::RenderWolfs() {
	for (int i = 0; i < Wolfs.size(); i++)
	{
		switch (Wolfs[i].getAnimation())
		{
		case 2:
			SDL_RenderCopy(renderer, textureWolf, NULL, Wolfs[i].GetRectangle());
			break;

		case 1:
			SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
			SDL_RenderCopyEx(renderer, textureWolf, NULL, Wolfs[i].GetRectangle(), 0.0, NULL, flip);
			break;
		}
	}
}

void Mobs::Render() {
	RenderChargers();
	RenderWolfs();
}



Mobs::~Mobs() {
	SDL_DestroyTexture(textureCharger);
}
