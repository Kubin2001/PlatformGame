#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>

class Font {
    private:
        SDL_Rect rectangle{0,0,29,29};
        SDL_Rect sourceRectangle[26];
        SDL_Texture* texture = nullptr;

    public:
        SDL_Rect* GetRectangle();

        SDL_Texture* GetTexture();

        void SetTexture(SDL_Texture* temptex);

        void LoadText();

        void Render(SDL_Renderer *renderer);

        void RenderText(SDL_Renderer* renderer, std::string text, int x, int y);
};

class Button {
    private:
        SDL_Rect rectangle;

    public:
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

        void OnClick(int &windowtype);

        ~UI();
};
