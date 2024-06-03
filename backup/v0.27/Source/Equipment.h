#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Player.h"

class ShortSword
{
    private:
        SDL_Rect rectangle;
        int damage = 10;
        bool renderable = false;

    public:
        SDL_Rect* GetRectangle();
        bool GetRenderable();

        void SetRenderable(bool temp);
};


class Equipment
{
    private:
        SDL_Texture * textureShortSword = nullptr;
        SDL_Renderer* renderer = nullptr;
        std::vector<ShortSword> ShortSwords;

    public:
        Equipment(SDL_Renderer *renderer);

        SDL_Texture *GetTextureShortSword();
        void SetTextureShortSword(SDL_Texture* temptex);
        void LoadEquipment();
        void MoveEquipment(const Uint8* state, Player* player);
        void DetectCollison(Player* player, SDL_Rect camRect);
        void Render(SDL_Rect camRect);
        void RenderShortSword(SDL_Rect camRect);

        ~Equipment();
};
