#include <iostream>
#include <SDL.h>
#include "UI.h"
SDL_Texture* UI::GetTextureHearth() {
    return texturehearth;
}

void UI::SetTextureHearth(SDL_Texture * temptex) {
    texturehearth = temptex;
}

void UI::Render(SDL_Renderer * renderer) {
    RenderHP(renderer);
}

void UI::RenderHP(SDL_Renderer* renderer) {
    for (int i = 0; i < HP.size(); i++) {
        SDL_RenderCopy(renderer, texturehearth, NULL, HP[i].GetRectangle());
    }
}

void UI::CreateHearths() {
    Hearth tempHP;
    int xCord = 20;
    int yCord = 20;
    for (int i = 0; i < 6; i++)
    {
        HP.push_back(tempHP);
        HP[HP.size() - 1].GetRectangle()->x = xCord;
        HP[HP.size() - 1].GetRectangle()->y = yCord;
        HP[HP.size() - 1].GetRectangle()->w = 40;
        HP[HP.size() - 1].GetRectangle()->h = 40;

        xCord += 50;
    }
}

void UI::RemoveHearths() {
    if (!HP.empty()) {
        HP.pop_back();
    }

}

SDL_Rect* Hearth::GetRectangle() {
    return &rectangle;
}
