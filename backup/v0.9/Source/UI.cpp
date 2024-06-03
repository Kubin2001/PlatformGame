#include <iostream>
#include <string>
#include <SDL.h>
#include "UI.h"
#include "Colision.h"

extern int windowtype;

UI::UI(){
    font = new Font();
}

SDL_Texture* UI::GetTextureHearth() {
    return texturehearth;
}

void UI::SetTextureHearth(SDL_Texture * temptex) {
    texturehearth = temptex;
}


SDL_Texture* UI::GetTextureButton() {
    return textureButton;
}

void UI::SetTextureButton(SDL_Texture* temptex) {
    textureButton = temptex;
}


SDL_Texture* Font::GetTexture() {
    return texture;
}

void Font::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

std::vector<Hearth>& UI::getHP() {
    return HP;
}

void UI::Render(SDL_Renderer * renderer) {
    RenderHP(renderer);
}

void UI::RenderHP(SDL_Renderer* renderer) {
    for (int i = 0; i < HP.size(); i++) {
        SDL_RenderCopy(renderer, texturehearth, NULL, HP[i].GetRectangle());
    }
}

void UI::RenderButton(SDL_Renderer* renderer) {
    for (int i = 0; i < Buttons.size(); i++)
    {
        SDL_RenderCopy(renderer, textureButton, NULL, Buttons[i].GetRectangle());
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

void UI::CreateButton() {
    Button button;
    Buttons.push_back(button);
    Buttons[0].GetRectangle()->x = 600;
    Buttons[0].GetRectangle()->y = 200;
    Buttons[0].GetRectangle()->w = 200;
    Buttons[0].GetRectangle()->h = 50;
    Buttons.push_back(button);
    Buttons[1].GetRectangle()->x = 600;
    Buttons[1].GetRectangle()->y = 400;
    Buttons[1].GetRectangle()->w = 200;
    Buttons[1].GetRectangle()->h = 50;
    Buttons.push_back(button);
    Buttons[2].GetRectangle()->x = 600;
    Buttons[2].GetRectangle()->y = 600;
    Buttons[2].GetRectangle()->w = 200;
    Buttons[2].GetRectangle()->h = 50;
}

void UI::OnClick(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Rect mouse;
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 2;
        mouse.h = 2;
        if (SimpleCollision(mouse, *Buttons[0].GetRectangle()) == 1) {
            windowtype = 2;
        }
    }

}

SDL_Rect* Hearth::GetRectangle() {
    return &rectangle;
}

SDL_Rect* Button::GetRectangle() {
    return &rectangle;
}

SDL_Rect* Font::GetRectangle() {
    return &rectangle;
}

void Font::LoadText() {
    int xCord = 1;
    int yCord = 1;
    for (int i = 0; i < 26; i++)
    {
        sourceRectangle[i].x = xCord;
        sourceRectangle[i].y = yCord;
        sourceRectangle[i].w = 29;
        sourceRectangle[i].h = 29;
        xCord += 31;
    }
}

void Font::Render(SDL_Renderer* renderer) {
    RenderText(renderer,"START ",620,210);
    RenderText(renderer, "SOON", 620, 410);
    RenderText(renderer, "SOON", 620, 610);
}

void Font::RenderText(SDL_Renderer* renderer, std::string text,int x,int y) {
    rectangle.x = x;
    rectangle.y = y;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        switch (text[i])
        {
            case 'A':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[0], &rectangle);
                break;
            case 'B':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[1], &rectangle);
                break;
            case 'C':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[2], &rectangle);
                break;
            case 'D':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[3], &rectangle);
                break;
            case 'E':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[4], &rectangle);
                break;
            case 'F':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[5], &rectangle);
                break;
            case 'G':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[6], &rectangle);
                break;
            case 'H':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[7], &rectangle);
                break;
            case 'I':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[8], &rectangle);
                break;
            case 'J':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[9], &rectangle);
                break;
            case 'K':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[10], &rectangle);
                break;
            case 'L':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[11], &rectangle);
                break;
            case 'M':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[12], &rectangle);
                break;
            case 'N':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[13], &rectangle);
                break;
            case 'O':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[14], &rectangle);
                break;
            case 'P':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[15], &rectangle);
                break;
            case 'Q':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[16], &rectangle);
                break;
            case 'R':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[17], &rectangle);
                break;
            case 'S':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[18], &rectangle);
                break;
            case 'T':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[19], &rectangle);
                break;
            case 'U':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[20], &rectangle);
                break;
            case 'V':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[21], &rectangle);
                break;
            case 'W':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[22], &rectangle);
                break;
            case 'X':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[23], &rectangle);
                break;
            case 'Y':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[24], &rectangle);
                break;
            case 'Z':
                SDL_RenderCopy(renderer, texture, &sourceRectangle[25], &rectangle);
                break;
            default:
                break;

        }
        rectangle.x += 31;
    }
    rectangle.x = temp;
}


UI::~UI() {
    delete font;
}