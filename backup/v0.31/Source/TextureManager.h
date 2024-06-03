#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "SDL_image.h"


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


SDL_Texture* load(const char* file, SDL_Renderer* ren);


void LoadMultipleTextures(std::vector<Texture>&vector, const std::string& directory, SDL_Renderer* renderer);