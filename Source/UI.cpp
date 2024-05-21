#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>
#include "UI.h"
#include "Colision.h"
#include "Font.h"

extern int windowtype;
extern int localWindow;
extern std::string levelName;

UI::UI(SDL_Renderer *renderer){
    font = new Font();
    buttonInfo = new ButtonInfo();
    this->renderer = renderer;
}

SDL_Texture* UI::GetTextureHearth() {return texturehearth;}

void UI::SetTextureHearth(SDL_Texture * temptex) {texturehearth = temptex;}


SDL_Texture* UI::GetTextureButton() {return textureButton;}

void UI::SetTextureButton(SDL_Texture* temptex) {textureButton = temptex;}

SDL_Texture* UI::GetTextureButtonInfo() {return textureButtonInfo;}

void UI::SetTextureButtonInfo(SDL_Texture* temptex) {textureButtonInfo = temptex;}

std::vector<Hearth>& UI::getHP() {return HP;}

void UI::Render() {
    if (windowtype == 1) {
        RenderButton();
        for (size_t  i = 0; i < Buttons.size(); i++)
        {
            int size = Buttons[i].GetRectangle()->w / Buttons[i].GetText().length() - 2;
            font->RenderText(renderer, Buttons[i].GetText(), Buttons[i].GetRectangle()->x, Buttons[i].GetRectangle()->y, size, size, size + 2);
        }
    }
    else if (windowtype == 2) {
        RenderHP();
    }

}

void UI::RenderHP() {
    for (int i = 0; i < HP.size(); i++) {
        SDL_RenderCopy(renderer, texturehearth, NULL, HP[i].GetRectangle());
    }
}

void UI::RenderButton() {
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
            for (int i = 0; i < 4; i++)
            {
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 50, line, 29, 30);
                yPos += 150;
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
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 100, line, 29, 30);
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
        case 2: { //Player Levels Selector 
            std::ifstream levelFile("Data/menu_player_levels.txt");
            std::string line;
            xPos = 100;
            yPos = 200;
            for (int i = 0; i < 11; i++)
            {
                std::getline(levelFile, line);
                CreateSingleButton(xPos, yPos, 200, 100, line, 29, 30);
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

void UI::CreateSingleButton(int x, int y, int w, int h, std::string text, int textSize, int textStep) {
    Button button;
    Buttons.push_back(button);
    Buttons[Buttons.size() -1].GetRectangle()->x = x;
    Buttons[Buttons.size() - 1].GetRectangle()->y = y;
    Buttons[Buttons.size() - 1].GetRectangle()->w = w;
    Buttons[Buttons.size() - 1].GetRectangle()->h = h;
    Buttons[Buttons.size() - 1].SetText(text);
    Buttons[Buttons.size() - 1].SetTextSize(textSize);
    Buttons[Buttons.size() - 1].SetTextStep(textStep);
}

void UI::RenderSingleButton(int index, int textureType) {
    switch (textureType)
    {
        case 1:
            SDL_RenderCopy(renderer, textureButton, NULL, Buttons[index].GetRectangle());
            break;
        case 2:
            SDL_RenderCopy(renderer, textureButtonInfo, NULL, Buttons[index].GetRectangle());
            break;
    }
    if (Buttons[index].GetText() != "") {
        font->RenderText(renderer, Buttons[index].GetText(), Buttons[index].GetRectangle()->x,
            Buttons[index].GetRectangle()->y, Buttons[index].GetTextSize(), Buttons[index].GetTextSize(), Buttons[index].GetTextStep());
    }
}


void UI::CreateButtonInfo(int x, int y , int w, int h,std::string text,int textSize, int textStep) {
    buttonInfo->GetRectangle()->x = x;
    buttonInfo->GetRectangle()->y = y;
    buttonInfo->GetRectangle()->w = w;
    buttonInfo->GetRectangle()->h = h;
    buttonInfo->SetText(text);

    SDL_RenderCopy(renderer, textureButtonInfo, NULL, buttonInfo->GetRectangle());
    font->RenderText(renderer, buttonInfo->GetText(), buttonInfo->GetRectangle()->x, buttonInfo->GetRectangle()->y, textSize, textSize, textStep);
    SDL_RenderPresent(renderer);
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
                    localWindow = 2;
                }
                else if (SimpleCollision(mouse, *Buttons[1].GetRectangle()) == 1) {
                    menuType = 1;
                    Buttons.clear();
                    CreateButton();
                }
                else if (SimpleCollision(mouse, *Buttons[2].GetRectangle()) == 1) {
                    menuType = 2;
                    Buttons.clear();
                    CreateButton();
                }
                else if (SimpleCollision(mouse, *Buttons[3].GetRectangle()) == 1) {
                    localWindow = 3;
                    Buttons.clear();
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
            case 2:
                if (SimpleCollision(mouse, *Buttons[10].GetRectangle()) == 1) {
                    menuType = 0;
                    Buttons.clear();
                    CreateButton();
                }
                break;
        }
        
    }

}

void UI::OnClickEditor(int &number,SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_Rect mouse;
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        for (int i = 0; i < Buttons.size(); i++)
        {
            if (SimpleCollision(mouse, *Buttons[i].GetRectangle()) == 1) {
                number = i;
            }
        }
    }
}


SDL_Rect* Hearth::GetRectangle() {
    return &rectangle;
}

SDL_Rect* Button::GetRectangle() {
    return &rectangle;
}

void Button::SetText(std::string temptext) {
    text = temptext;
}

std::string Button::GetText() {
    return text;
}

int Button::GetTextSize() {
    return textSize;
}
void Button::SetTextSize(int temp) {
    textSize = temp;
}
int Button::GetTextStep() {
    return textStep;
}
void Button::SetTextStep(int temp) {
    textStep = temp;
}

SDL_Rect* ButtonInfo::GetRectangle() {
    return &rectangle;
}

void ButtonInfo::SetText(std::string temptext) {
    text = temptext;
}

std::string ButtonInfo::GetText() {
    return text;
}

UI::~UI() {
    delete font;
    delete buttonInfo;
    SDL_DestroyTexture(texturehearth);
    SDL_DestroyTexture(textureButton);
    SDL_DestroyTexture(textureButtonInfo);
}
