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

SDL_Rect* Charger::GetRectangle() {
    return &rectangle;
}

int Charger::getAnimation() {
	return animation;
}


void Charger::setAnimation(int temp) {
	animation = temp;
}


int Charger::getHitPoints() {
	return hitPoints;
}


void Charger::setHitPoints(int temp) {
	hitPoints = temp;
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

std::vector<Charger>& Mobs::getChargers() { return Chargers; }
//getters and setters

void Mobs::LoadMobs() {
	Charger charger;
	std::ifstream levelFile(levelName);
	std::string line;
	int xCord = 0;
	int yCord = 0;
	if (levelFile.is_open()) {
		while (getline(levelFile, line)) {
			yCord += 40;
			for (size_t i = 0; i < line.length(); i++)
			{
				xCord += 40;
				if (line[i] == 'a') {
					Chargers.push_back(charger);
					Chargers[Chargers.size() - 1].GetRectangle()->x = xCord;
					Chargers[Chargers.size() - 1].GetRectangle()->y = yCord;
					Chargers[Chargers.size() - 1].GetRectangle()->w = 30;
					Chargers[Chargers.size() - 1].GetRectangle()->h = 30;
				}
			}
			xCord = 0;
		}
	}
	else
	{
		std::cout << "Nie mo�na otworzy� pliku\n";
	}


}

void Mobs::DetectColison(Player* player,Map *map) {
	int x = 730; // 730 wynika z kalkulacji 760 czyli y pod�ogi - wysoko�� obiektu w tym wypadku 30
	for (int i = 0; i < Chargers.size(); i++)
	{
		Chargers[i].setColison(false, 0);
		Chargers[i].setColison(false, 1);
		Chargers[i].setColison(false, 2);

		for (int j = 0; j < map->getPlatform().size(); j++)
		{
			switch (Collision(*Chargers[i].GetRectangle(), *map->getPlatform()[j].GetRectangle()))
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

		for (int j = 0; j < map->getPillar().size(); j++)
		{
			switch (Collision(*Chargers[i].GetRectangle(), *map->getPillar()[j].GetRectangle()))
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

		if (Chargers[i].GetRectangle()->y < x && Chargers[i].getColison(1) == false) {
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
}

void Mobs::MoveMobs(const Uint8* state, Player* player) {
	if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->x -= 4;
		}
	}
	if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
		for (int i = 0; i < Chargers.size(); i++)
		{
			Chargers[i].GetRectangle()->x += 4;
		}
	}
	for (int i = 0; i < Chargers.size(); i++)
	{
		Chargers[i].Movement();
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

void Mobs::Render() {
	RenderChargers();
}


void Charger::setColison(bool value, int index) {
	if (index < 4) {
		colision[index] = value;
	}

}

bool Charger::getColison(int index) {
	if (index < 4) {
		return colision[index];
	}

}


Mobs::~Mobs() {
	SDL_DestroyTexture(textureCharger);
}