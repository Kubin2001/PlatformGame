#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
class Hearth {
    private:
        SDL_Rect rectangle;

    public:
        SDL_Rect* GetRectangle();

};

class UI
{
    private:
        SDL_Texture * texturehearth = nullptr;
        std::vector<Hearth> HP;

    public:
        SDL_Texture *GetTextureHearth();
        void SetTextureHearth(SDL_Texture* temptex);
        void CreateHearths();
        void RemoveHearths();

        void Render(SDL_Renderer* renderer);
        void RenderHP(SDL_Renderer* renderer);
};
