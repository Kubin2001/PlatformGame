#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include "UI.h"
#include "Colision.h"
#include "Font.h"

extern int windowtype;
extern std::string levelName;

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

std::vector<Hearth>& UI::getHP() {
    return HP;
}

std::string Button::GetText() {
    return text;
}
void Button::SetText(std::string temptext){
    text = temptext;
}

void UI::Render(SDL_Renderer * renderer) {
    if (windowtype == 1) {
        RenderButton(renderer);
        switch (menuType) {
            case 0:
                for (int  i = 0; i < Buttons.size(); i++)
                {
                    font->RenderText(renderer, Buttons[i].GetText(), Buttons[i].GetRectangle()->x, Buttons[i].GetRectangle()->y,29,29,31);
                }
                break;
            case 1:
                for (int i = 0; i < Buttons.size(); i++)
                {
                    font->RenderText(renderer, Buttons[i].GetText(), Buttons[i].GetRectangle()->x, Buttons[i].GetRectangle()->y,20,20,21);
                }
                
                break;
        }
    }
    if (windowtype == 2) {
        RenderHP(renderer);
    }

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
    int xPos = 0;
    int yPos = 0;
    Button button;
    switch (menuType)
    {
        case 0: { //Main menu
            std::ifstream levelFile("Data/menu_main.txt");
            std::string line;
            xPos = 600;
            yPos = 200;
            for (int i = 0; i < 3; i++)
            {
                Buttons.push_back(button);
                Buttons[i].GetRectangle()->x = xPos;
                Buttons[i].GetRectangle()->y = yPos;
                Buttons[i].GetRectangle()->w = 200;
                Buttons[i].GetRectangle()->h = 50;
                if (std::getline(levelFile, line)) {
                    Buttons[i].SetText(line);
                }
                else
                {
                    Buttons[i].SetText(" ");
                }

                yPos += 200;
            }
        }
            break;
        case 1: { //Levels Selector
            std::ifstream levelFile("Data/menu_levels.txt");
            std::string line;
            xPos = 100;
            yPos = 200;
            for (int i = 0; i < 11; i++)
            {
                Buttons.push_back(button);
                Buttons[i].GetRectangle()->x = xPos;
                Buttons[i].GetRectangle()->y = yPos;
                Buttons[i].GetRectangle()->w = 200;
                Buttons[i].GetRectangle()->h = 100;
                if (std::getline(levelFile, line)) {
                    Buttons[i].SetText(line);
                }
                else
                {
                    Buttons[i].SetText(" ");
                }

                xPos += 250;
                if (i == 4) {
                    xPos = 100;
                    yPos += 300;
                }
                if (i == 9) {
                    xPos = 600;
                    yPos = 650;
                }

            }
        }
            break;
    }
}

void UI::OnClick(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Rect mouse;
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        switch (menuType)
        {
            case 0:
                if (SimpleCollision(mouse, *Buttons[0].GetRectangle()) == 1) {
                    windowtype = 2;
                }
                else if (SimpleCollision(mouse, *Buttons[1].GetRectangle()) == 1) {
                    menuType = 1;
                    Buttons.clear();
                    CreateButton();
                }
                break;
            case 1:
                if (SimpleCollision(mouse, *Buttons[0].GetRectangle()) == 1) {
                    levelName = "Levels/level1.txt";
                }
                if (SimpleCollision(mouse, *Buttons[1].GetRectangle()) == 1) {
                    levelName = "Levels/level2.txt";
                }
                if (SimpleCollision(mouse, *Buttons[2].GetRectangle()) == 1) {
                    levelName = "Levels/level3.txt";
                }
                if (SimpleCollision(mouse, *Buttons[3].GetRectangle()) == 1) {
                    levelName = "Levels/level4.txt";
                }
                if (SimpleCollision(mouse, *Buttons[4].GetRectangle()) == 1) {
                    levelName = "Levels/level5.txt";
                }
                if (SimpleCollision(mouse, *Buttons[5].GetRectangle()) == 1) {
                    levelName = "Levels/level6.txt";
                }
                if (SimpleCollision(mouse, *Buttons[6].GetRectangle()) == 1) {
                    levelName = "Levels/level7.txt";
                }
                if (SimpleCollision(mouse, *Buttons[7].GetRectangle()) == 1) {
                    levelName = "Levels/level8.txt";
                }
                if (SimpleCollision(mouse, *Buttons[8].GetRectangle()) == 1) {
                    levelName = "Levels/level9.txt";
                }
                if (SimpleCollision(mouse, *Buttons[9].GetRectangle()) == 1) {
                    levelName = "Levels/level10.txt";
                }
                if (SimpleCollision(mouse, *Buttons[10].GetRectangle()) == 1) {
                    menuType = 0;
                    Buttons.clear();
                    CreateButton();
                }
                break;
        }
        
    }

}

SDL_Rect* Hearth::GetRectangle() {
    return &rectangle;
}

SDL_Rect* Button::GetRectangle() {
    return &rectangle;
}



UI::~UI() {
    delete font;
}