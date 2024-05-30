#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <filesystem>

#include "Mobs.h"
#include "Player.h"
#include "Colision.h"
#include "Map.h"
#include "Camera.h"
#include "SoundManager.h"
#include "TextureManager.h"

extern std::string levelName;
extern long long framesCounter;


SDL_Rect* Enemy::GetRectangle() {
	return &rectangle;
}

std::vector<SDL_Rect> &Enemy::GetSourceRectangle() {
	return sourceRectangle;
}

void Enemy::setTexture(SDL_Texture* text) { texture = text; }

SDL_Texture* Enemy::getTexture() { return texture; }

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

bool Enemy::GetJumpable() {
	return jumpable;
}

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

//CHARGER
void Charger::MakeAgressive() {}

SDL_Rect* Charger::ChooseAnimation() {
	return NULL;
}

void Charger::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
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
		GetRectangle()->x--;
		break;

	case 2:
		GetRectangle()->x++;
		break;

	}

}

//CHARGER

//WOLF
void Wolf::MakeAgressive() {
	if (cProj != nullptr) {
		cProj->SetTimer(50);
	}
	SoundManager::PlayWolfGrowlSound();
	agroo = 300;
}

SDL_Rect* Wolf::ChooseAnimation() {
	return NULL;
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
		for (int i = 0; i < map->getObjects().size(); i++)
		{
			if (SimpleCollision(*cProj->GetRectangle(), *map->getObjects()[i]->GetRectangle()) == 1)
			{
				cProj->SetTimer(50);
				break;
			}
		}


		if (SimpleCollision(*cProj->GetRectangle(), *player->GetRectangle()) == 1) {
			cProj->SetTimer(50);
			if (agroo == 0) {
				SoundManager::PlayWolfGrowlSound();
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
//WOLF

//PIRATE

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

void Pirate::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
	if (isAggressive == false) {
		if (cProj == nullptr) {
			switch (animation)
			{
			case 1:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y + 30, 1, 1, 30, 0);
				break;
			case 2:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y + 30, 1, 1, -30, 0);
				break;
			}
		}
		else
		{
			cProj->MoveProjectlile();
			for (int i = 0; i < map->getObjects().size(); i++)
			{
				if (SimpleCollision(*cProj->GetRectangle(), *map->getObjects()[i]->GetRectangle()) == 1)
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
			GetRectangle()->x += 2;
		}
		else if (!colision[0] && player->GetRectangle()->x < GetRectangle()->x) {
			animation = 2;
			GetRectangle()->x -= 2;
		}

		if (AttackDelay < 0) {
			AttackDelay = 100;
			SDL_Rect rect{ GetRectangle()->x ,GetRectangle()->y ,30,80 };
			switch (animation)
			{
			case 1:
				SoundManager::PlayPirateAttackSound();
				particleManager->CreateEnemyParticle(rect, 1, 6, 0, 35, "wave",0);
				break;
			case 2:
				SoundManager::PlayPirateAttackSound();
				particleManager->CreateEnemyParticle(rect, 2, -6, 0, 35, "wave",0);
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

void Pirate::MakeAgressive() {
	if (cProj != nullptr) {
		cProj->SetTimer(50);
	}
	isAggressive = true;
	agroo = 500;
}

//PIRATE

//ARCHER
SDL_Rect* Archer::ChooseAnimation() {
	animationTimer++;
	if (isAggressive) {
		if (framesCounter % 150 == 0) {
			animationTimer = 0;
		}
		if (animationTimer < 75) {
			return &sourceRectangle[2];
		}
		else
		{
			return &sourceRectangle[3];
		}
	}
	else
	{
		if (framesCounter % 50 == 0) {
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
}

void Archer::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
	if (isAggressive) {
		agroo--;
		if (agroo <= 0) {
			isAggressive = false;
			return;
		}
		if (player->GetRectangle()->x > GetRectangle()->x) {
			animation = 1;
		}
		else
		{
			animation = 2;
		}

		if (framesCounter % 150 == 0) {
			SDL_Rect rect{ GetRectangle()->x, GetRectangle()->y + 30, 40, 10 };

			double initialDiffX = (player->GetRectangle()->x - GetRectangle()->x) / 60.0;
			double initialDiffY = (player->GetRectangle()->y - GetRectangle()->y) / 60.0;

			if (initialDiffX == 0 && initialDiffY == 0) {
				initialDiffX = 6;
			}
			double sum = std::abs(initialDiffX) + std::abs(initialDiffY);

			double scale = 7.0 / sum;

			int dirX = static_cast<int>(initialDiffX * scale);
			int dirY = static_cast<int>(initialDiffY * scale);

			double angle = 0;
			if (animation == 2) {
				angle = (dirY * 13) * -1;
			}
			else
			{
				angle = (dirY * 13);
			}
			SoundManager::PlayArrowShootSound();



			particleManager->CreateEnemyParticle(rect, animation, dirX, dirY, 200, "arrow",angle);
		}
	}
	else
	{
		if (framesCounter % 100 == 0) {
			int random = rand() % 2;
			if (random == 0) {
				switch (animation)
				{
				case 1:
					animation = 2;
					break;
				case 2:
					animation = 1;
					break;
				}
			}
		}
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
			for (int i = 0; i < map->getObjects().size(); i++)
			{
				if (SimpleCollision(*cProj->GetRectangle(), *map->getObjects()[i]->GetRectangle()) == 1)
				{
					cProj->SetTimer(50);
					break;
				}
			}


			if (SimpleCollision(*cProj->GetRectangle(), *player->GetRectangle()) == 1) {
				cProj->SetTimer(50);
				if (agroo == 0) {
					agroo = 1000;
					isAggressive = true;
				}
			}
			else
			{
				if (cProj->GetTimer() > 50) {
					delete cProj;
					cProj = nullptr;
				}
			}
		}
		
	}
}

void Archer::MakeAgressive() {
	if (cProj != nullptr) {
		cProj->SetTimer(50);
	}
	isAggressive = true;
	agroo = 500;
}

void Shotter::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
	if (renderable) {
		if (framesCounter % 150 == 0) {
			SDL_Rect rect{ GetRectangle()->x -5, GetRectangle()->y +18, 40, 10 };

			SoundManager::PlayArrowShootSound();
			particleManager->CreateEnemyParticle(rect, 2, -6, 0, 200, "arrow", 0);
		}
	}
}

void Shotter::MakeAgressive(){}

SDL_Rect* Shotter::ChooseAnimation() { return NULL; }

//ARCHER

//getters and setters
std::vector<Texture>& Mobs::getTextures() {
	return Textures;
}

std::vector<Enemy*>& Mobs::getEnemies() { return Enemies; }

//getters and setters

Mobs::Mobs(SDL_Renderer* renderer) {
	this->renderer = renderer;
}


void Mobs::LoadTextures() {
	std::string directory = "Textures/Mobs";
	LoadMultipleTextures(Textures, directory, renderer);
}

void LoadObject(std::vector<Enemy*>& vec1, Texture& texture, std::ifstream& levelFile, std::string& line) {
	vec1.back()->setTexture(texture.GetTexture());
	getline(levelFile, line);
	vec1.back()->GetRectangle()->x = std::stoi(line);
	getline(levelFile, line);
	vec1.back()->GetRectangle()->y = std::stoi(line);
	getline(levelFile, line);
	vec1.back()->GetRectangle()->w = std::stoi(line);
	getline(levelFile, line);
	vec1.back()->GetRectangle()->h = std::stoi(line);
}

void Mobs::LoadMobs() {
	std::ifstream levelFile(levelName);
	std::string line;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "charger") {
				Enemies.push_back(new Charger());
				for (auto &it: Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Enemies, it, levelFile, line);
					}
				}
			}
			else if (line == "wolf") {
				Enemies.push_back(new Wolf());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Enemies, it, levelFile, line);
					}
				}
			}

			else if (line == "pirate") {
				Enemies.push_back(new Pirate());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Enemies, Textures[i], levelFile, line);
						Enemies.back()->LoadAnimations(41);
					}
				}

			}

			else if (line == "archer") {
				Enemies.push_back(new Archer());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Enemies, it, levelFile, line);
						Enemies.back()->LoadAnimations(41);
					}
				}

			}
			else if (line == "shootter") {
				Enemies.push_back(new Shotter());
				for (auto& it : Textures)
				{
					if (it.GetName() == line) {
						LoadObject(Enemies, it, levelFile, line);
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

		for (int j = 0; j < map->getObjects().size(); j++)
		{
			map->getObjects()[j]->MobCollision(Enemies[i]);
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
				case 2:{
					if (Enemies[i]->GetJumpable()) {
						player->setColison(true, 1);
						player->setJumpBuffer(15);
						SoundManager::PlayPlayerJumpSound();
						Enemies[i]->setHitPoints(Enemies[i]->getHitPoints() - 10);
					}
					else
					{
						Shotter* shooterEnemy = dynamic_cast<Shotter*>(Enemies[i]);
						if (shooterEnemy != nullptr) {
							player->setColison(true, 1);
						}
					}
				}
				break;
				
			case 3:
				player->setColison(true, 2);
				player->SetDamage(true);
				break;
		}
	}
	for (int i = 0; i < Enemies.size(); i++) {
		if (Enemies[i]->getHitPoints() < 1) {
			SoundManager::PlayEnemyDeathSound();
			delete Enemies[i];
			Enemies.erase(Enemies.begin() + i);
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
					SDL_RenderCopyEx(renderer, Enemies[i]->getTexture(), Enemies[i]->ChooseAnimation(), &temp, 0.0, NULL, flip);
					break;
					}

				case 2:
					SDL_RenderCopy(renderer, Enemies[i]->getTexture(), Enemies[i]->ChooseAnimation(), &temp);
					break;
					

			}
		}
	}
}

void Mobs::Render(SDL_Rect camRect) {
	RenderEnemies(camRect);
}



Mobs::~Mobs() {
	for (auto it : Textures)
	{
		SDL_DestroyTexture(it.GetTexture());
	}
	for (auto enemy : Enemies) {
		delete enemy;
	}
	Enemies.clear();
}
