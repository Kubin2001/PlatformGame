#include <iostream>
#include <SDL.h>
#include "TextureManager.h"

SDL_Texture* Texture::GetTexture() { return texture; }

void Texture::SetTexture(SDL_Texture* temptex) { texture = temptex; }

std::string Texture::GetName() { return name; }

void Texture::SetName(std::string temp) { name = temp; }
