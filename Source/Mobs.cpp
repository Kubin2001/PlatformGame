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

extern SDL_Texture* load(const char* file, SDL_Renderer* ren);

Mobs::Mobs(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

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

void Pirate::Movement(Player* player, Map* map, ParticlesManager* particleManager) {
	if (isAggressive == false) {
		if (cProj == nullptr) {
			switch (animation)
			{
			case 1:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y+30, 1, 1, 30, 0);
				break;
			case 2:
				cProj = new CollisonProjectile(GetRectangle()->x, GetRectangle()->y+30, 1, 1, -30, 0);
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
					SoundManager::PlayPirateAttackSound();
					particleManager->CreateEnemyAttackParticles(rect, 1, 6, 35);
					break;
				case 2:
					SoundManager::PlayPirateAttackSound();
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


void Charger::MakeAgressive() {}

void Wolf::MakeAgressive() {
	if (cProj != nullptr) {
		cProj->SetTimer(50);
	}
	SoundManager::PlayWolfGrowlSound();
	agroo = 300;
}

void Pirate::MakeAgressive() {
	if (cProj != nullptr) {
		cProj->SetTimer(50);
	}
	isAggressive = true;
	agroo = 500;
}

//getters and setters
std::vector<Texture>& Mobs::getTextures() {
	return Textures;
}

std::vector<Enemy*>& Mobs::getEnemies() { return Enemies; }

//getters and setters


void Mobs::LoadTextures() {
	Texture temp;
	std::string directory = "Textures/Mobs";
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
}

void LoadObject(std::vector<Enemy*>& vec1, Texture& texture, std::ifstream& levelFile, std::string& line) {
	vec1[vec1.size() - 1]->setTexture(texture.GetTexture());
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->x = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->y = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->w = std::stoi(line);
	getline(levelFile, line);
	vec1[vec1.size() - 1]->GetRectangle()->h = std::stoi(line);
}

void Mobs::LoadMobs() {
	std::ifstream levelFile(levelName);
	std::string line;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			if (line == "charger") {
				Enemies.push_back(new Charger());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Enemies, Textures[i], levelFile, line);
					}
				}
			}
			else if (line == "wolf") {
				Enemies.push_back(new Wolf());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Enemies, Textures[i], levelFile, line);
					}
				}
			}

			else if (line == "pirate") {
				Enemies.push_back(new Pirate());
				for (int i = 0; i < Textures.size(); i++)
				{
					if (Textures[i].GetName() == line) {
						LoadObject(Enemies, Textures[i], levelFile, line);
						Enemies[Enemies.size() - 1]->LoadAnimations(41);
					}
				}

			}
		}
	}
	else
	{
		std::cout << "Nie mo�na otworzy� pliku\n";
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
			case 2:
				if (Enemies[i]->GetJumpable()) {
					player->setColison(true, 1);
					player->setJumpBuffer(15);
					SoundManager::PlayPlayerJumpSound();
					Enemies[i]->setHitPoints(Enemies[i]->getHitPoints() - 10);
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
