#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>

#include "Mobs.h"
#include "Player.h"
#include "Colision.h"

SDL_Rect* Charger::GetRectangle() {
    return &rectangle;
}

int Charger::getAnimation() {
	return animation;
}


void Charger::setAnimation(int temp) {
	animation = temp;
}

void Charger::Movement() {
	if (movementBuffor > 300) {
		movementtype = rand() % 3;
		switch (movementtype)
		{
			case 0:
				animation = 1;
				break;

			case 1:
				animation = 2;
				break;

		}
		
		movementBuffor = 0;

	}
	else
	{
		movementBuffor ++;
	}

	switch (movementtype)
	{
		case 0:
			GetRectangle()->x++;
			break;

		case 1:
			GetRectangle()->x--;
			break;

	}
	
}

SDL_Texture* Mobs::GetTextureCharger() {
    return textureCharger;
}

void Mobs::SetTextureCharger(SDL_Texture* temptex) {
    textureCharger = temptex;
}

void Mobs::LoadMobs() {
	Charger charger;
	std::ifstream levelFile("Levels/level1.txt");
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

void Mobs::DetectColison(Player* player) {
	int x = 730; // 730 wynika z kalkulacji 760 czyli y pod�ogi - wysoko�� obiektu w tym wypadku 30
	for (int i = 0; i < Chargers.size(); i++)
	{
		switch (Collision(*player->GetRectangle(), *Chargers[i].GetRectangle()))
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
			player->setJumpBuffer(20);
			break;
		}
		if (Chargers[i].GetRectangle()->y < x) {
			Chargers[i].GetRectangle()->y += 2;
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


void Mobs::RenderChargers(SDL_Renderer* renderer) {
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

void Mobs::Render(SDL_Renderer* renderer) {
	RenderChargers(renderer);
}