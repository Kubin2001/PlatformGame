#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>


class LevelEditor
{
    private:
        SDL_Renderer* renderer;
        std::vector<SDL_Texture*> texturesUI;
        std::vector<SDL_Texture*> texturesMap;
        std::vector<SDL_Texture*> texturesMobs;
        std::vector<SDL_Texture*> texturesEquipment;
        SDL_Texture* texturePlayer;

    public:
        LevelEditor(SDL_Renderer* renderer);

        void LoadTextures();

        void Render();

        ~LevelEditor();
};
