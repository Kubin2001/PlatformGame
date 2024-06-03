#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "Font.h"
class Button {
    private:
        SDL_Rect rectangle;
        std::string text;

    public:
        std::string GetText();
        void SetText(std::string temptext);
        SDL_Rect* GetRectangle();

};

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
        SDL_Texture* textureButton = nullptr;
        std::vector<Hearth> HP;
        std::vector<Button> Buttons;
        int menuType = 0;

    public:
        Font* font;

        UI();

        SDL_Texture *GetTextureHearth();
        void SetTextureHearth(SDL_Texture* temptex);
        SDL_Texture* GetTextureButton();
        void SetTextureButton(SDL_Texture* temptex);

        std::vector<Hearth> &getHP();
        void CreateHearths();
        void RemoveHearths();

        void CreateButton();

        void Render(SDL_Renderer* renderer);
        void RenderHP(SDL_Renderer* renderer);
        void RenderButton(SDL_Renderer* renderer);

        void OnClick(SDL_Event event);

        ~UI();
};
