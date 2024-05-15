#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "Mobs.h"
#include "Player.h"
#include "Colision.h"
#include "Map.h"
#include "Camera.h"

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

void Enemy::setInvTime(int value) {
	invTime = value;
}

int Enemy::getInvTime() {
	return invTime;
}

bool Enemy::GetRenderable() { return renderable; }

void Enemy::SetRenderable(bool temp) { renderable = temp; }

void Enemy::LoadAnimations(int step) {
	if (animationCount == 0) {
		return;
	}
	SDL_Rect temp;
	int xPos = 1;
	for (int i = 0; i < animationCount; i++)
	{
		sourceRectangle.push_back(temp);
		sourceRectangle[i].x = xPos;
		sourceRectangle[i].y = 1;
		sourceRectangle[i].w = 40;
		sourceRectangle[i].h = 90;
		xPos += step;
	}
}

SDL_Rect* Charger::ChooseAnimation() {
	return NULL;
}

SDL_Rect* Wolf::ChooseAnimation() {
	return NULL;
}

SDL_Rect* Pirate::ChooseAnimation() {
	animationTimer++;
	if (animationTimer > 50) {
		animationTimer = 0;
	}
	if (animationTimer < 25) {
		return &sourceRectangle[0];
	}
	else
	{
		return &sourceRectangle[1];
	}
}

void Wolf::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
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


void Charger::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
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


void Pirate::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
	if (isAggressive == false) {
		if (cProj == nullptr) {
			switch (animation)
			{
			case 1:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y+10, 1, 1, 30, 0);
				break;
			case 2:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y+10, 1, 1, -30, 0);
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
				isAggressive = true;
				agroo = 500;
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
		else if (colision[0] && colision[2]) {
			movementtype = 0;
		}

		switch (movementtype)
		{
		case 1:
			GetRectangle()->x--;
			break;

		case 2:
			GetRectangle()->x++;
		}
	}
	else
	{
		agroo--;
		if (!colision[2] && player->GetRectangle()->x > GetRectangle()->x) {
			animation = 1;
			GetRectangle()->x+=2;
		}
		else if (!colision[0] && player->GetRectangle()->x < GetRectangle()->x) {
			animation = 2;
			GetRectangle()->x-=2;
		}

		if (AttackDelay < 0) {
			AttackDelay = 100;
			SDL_Rect rect{ GetRectangle()->x ,GetRectangle()->y ,30,80 };
			switch (animation)
			{
				case 1:
					particleManager->CreateEnemyAttackParticles(rect, 1, 6, 35);
					break;
				case 2:
					particleManager->CreateEnemyAttackParticles(rect, 2, -6, 35);
					break;
			}
		}
		else
		{
			AttackDelay--;
		}
		if (agroo < 0) {
			isAggressive = false;
		}
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

SDL_Texture* Mobs::GetTexturePirate() {
	return texturePirate;
}

void Mobs::SetTexturePirate(SDL_Texture* temptex) {
	texturePirate = temptex;
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
			else if (line == "wolf") {
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

			else if (line == "pirate") {
				Enemies.push_back(new Pirate());
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->x = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->y = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->w = std::stoi(line);
				getline(levelFile, line);
				Enemies[Enemies.size() - 1]->GetRectangle()->h = std::stoi(line);
				Enemies[Enemies.size() - 1]->texture = texturePirate;
				Enemies[Enemies.size() - 1]->LoadAnimations(41);

			}
		}
	}
	else
	{
		std::cout << "Nie mo¿na otworzyæ pliku\n";
	}
}

void Mobs::DetectColison(Player* player,Map *map, SDL_Rect camRect) {
	for (int i = 0; i < Enemies.size(); i++)
	{
		if (SimpleCollision(camRect, *Enemies[i]->GetRectangle())) {
			Enemies[i]->SetRenderable(true);
		}
		else
		{
			Enemies[i]->SetRenderable(false);
		}
	}
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
				player->setJumpBuffer(15);
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

void Mobs::MoveMobs(const Uint8* state, Player* player,Map *map, ParticlesManager* particleManager) {
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->Movement(player,map,particleManager);
	}

	for (int i = 0; i < Enemies.size(); i++)
	{
		if (Enemies[i]->getInvTime() > 0) {
			Enemies[i]->setInvTime(Enemies[i]->getInvTime() - 1);
		}
	}

}


void Mobs::RenderEnemies(SDL_Rect camRect) {
	SDL_Rect temp;
	for (int i = 0; i < Enemies.size(); i++)
	{
		if (Enemies[i]->GetRenderable()) {
			temp.x = Enemies[i]->GetRectangle()->x - camRect.x;
			temp.y = Enemies[i]->GetRectangle()->y - camRect.y;
			temp.w = Enemies[i]->GetRectangle()->w;
			temp.h = Enemies[i]->GetRectangle()->h;
			switch (Enemies[i]->getAnimation())
			{
				case 1: {
					SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
					SDL_RenderCopyEx(renderer, Enemies[i]->texture, Enemies[i]->ChooseAnimation(), &temp, 0.0, NULL, flip);
					break;
					}

				case 2:
					SDL_RenderCopy(renderer, Enemies[i]->texture, Enemies[i]->ChooseAnimation(), &temp);
					break;
					

			}
		}
	}
}

void Mobs::Render(SDL_Rect camRect) {
	RenderEnemies(camRect);
}



Mobs::~Mobs() {
	SDL_DestroyTexture(textureCharger);
}
