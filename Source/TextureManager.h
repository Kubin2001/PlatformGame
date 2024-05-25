#pragma once
#include <iostream>
#include <SDL.h>


class Texture {
private:
	SDL_Texture* texture;
	std::string name = "";
public:
	SDL_Texture* GetTexture();

	void SetTexture(SDL_Texture* temptex);

	std::string GetName();

	void SetName(std::string temp);
};