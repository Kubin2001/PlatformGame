#include <iostream>
#include <SDL.h>
#include <string>
#include <fstream> 
#include "LevelEditor.h"
#include "UI.h"
#include "Colision.h"

extern SDL_Texture* load(const char* file, SDL_Renderer* ren);

LevelEditor::LevelEditor(SDL_Renderer* renderer) {
    this->renderer = renderer;
    ui = new UI(renderer);
    ui->font->LoadText(36, 29, 29);
    ui->CreateSingleButton(300, 0, 200, 50, "TERRAIN", 26, 27);
    ui->CreateSingleButton(600, 0, 200, 50, "MOBS", 29, 30);
    ui->CreateSingleButton(900, 0, 200, 50, "EQUIPMENT", 20, 21);

    ui->CreateSingleButton(1150, 100, 200, 50, "CLOSE", 20, 21);

    ui->CreateSingleButton(50, 100, 200, 50, "RESET", 20, 21);

    ui->CreateSingleButton(50, 200, 200, 50, "CREATE", 20, 21);
}

void LevelEditor::LoadTextures() {
    ui->SetTextureButton(load("Textures/Interface/button.png", renderer));
    ui->font->SetTexture(load("Textures/Interface/font.png", renderer));
    ui->SetTextureButtonInfo(load("Textures/Interface/buttonInfo.png", renderer));

    texturePlayer = load("Textures/player.png", renderer);

    texturesMap.push_back(load("Textures/Terrain/grass.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/platform.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/pillar.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/flag.png", renderer));

    texturesMobs.push_back(load("Textures/Mobs/charger.png", renderer));
    texturesMobs.push_back(load("Textures/Mobs/wolf.png", renderer));

    texturesEquipment.push_back(load("Textures/Equipment/shortSword.png", renderer));
}

void LevelEditor::OnClick(SDL_Event event) {
    ui->OnClickEditor(menu,event);
    SDL_Rect rect;
    int posX = 200;
    int posY = 400;
    if (menu != -1) {
        SDL_Rect rect;
        int posX = 200;
        int posY = 400;
        rectangles.clear();
        switch (menu)
        {
            case 0:
            {
                for (int i = 0; i < texturesMap.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 100;
                    rectangles[rectangles.size() - 1].h = 100;
                    posX += 200;
                }
            }
            break;
            case 1:
            {
                for (int i = 0; i < texturesMobs.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 100;
                    rectangles[rectangles.size() - 1].h = 100;
                    posX += 200;
                }
            }
            break;
            case 2:
            {
                for (int i = 0; i < texturesEquipment.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 100;
                    rectangles[rectangles.size() - 1].h = 100;
                    posX += 200;
                }
            }
            break;
            case 4:
            {
                for (size_t i = 0; i < objects.size(); i++)
                {
                    objects[i].rect.x += xTrue;
                    objects[i].rect.y += yTrue;
                }
                rectanglePlayer.x += xTrue;
                rectanglePlayer.y += yTrue;
                xTrue = 0;
                yTrue = 0;
                menu = -1;
            }
            break;
            case 5:
            {
                ConvertToFile();
                std::cout << "test";
                menu = -1;
            }
            break;
        }
        if (clickBuffer == 0) {
            switch (menu)
            {
                case 0:
                    MouseCollison(event, texturesMap, rectangles);
                    break;
                case 1:
                    MouseCollison(event, texturesMobs, rectangles);
                    break;
                case 2:
                    MouseCollison(event, texturesEquipment, rectangles);
                    break;
            }
        }

    }
    
    if (clicked && clickBuffer == 0) {
        Pleace(event);

    }
    if (!clicked && clickBuffer == 0) {
        MouseCollisonObjects(event, objects);
    }
    Settings(event);
    Move(event);
    ChangeScales(event);
    UpdateKeyboard(event);
    DeleteObject(event);
    
}

void LevelEditor::MouseCollison(SDL_Event event, std::vector<SDL_Texture*>& textures, std::vector<SDL_Rect>& rectangles) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        for (int i = 0; i < rectangles.size(); i++)
        {
            if (SimpleCollision(mouse, rectangles[i] ) == 1) {
                clickRectangle = rectangles[i];
                clickTexture = textures[i];
                clicked = true;
                clickBuffer += 10;
                switch (menu) {
                case 0:
                    switch (i)
                    {
                    case 0:
                        currentName = "grass";
                        clickRectangle.w = 200;
                        clickRectangle.h = 40;
                        break;
                    case 1:
                        currentName = "platform";
                        clickRectangle.w = 160;
                        clickRectangle.h = 40;
                        break;
                    case 2:
                        currentName = "pillar";
                        clickRectangle.w = 40;
                        clickRectangle.h = 160;
                        break;
                    case 3:
                        currentName = "flag";
                        clickRectangle.w = 40;
                        clickRectangle.h = 100;
                        break;
                    }
                    break;
                case 1:
                    switch (i)
                    {
                    case 0:
                        currentName = "charger";
                        clickRectangle.w = 30;
                        clickRectangle.h = 30;
                        break;
                    case 1:
                        currentName = "wolf";
                        clickRectangle.w = 86;
                        clickRectangle.h = 50;
                        break;
                    }
                    break;
                case 2:
                    switch (i)
                    {
                    case 0:
                        currentName = "shortSword";
                        clickRectangle.w = 30;
                        clickRectangle.h = 34;
                        break;
                    }
                    break;

                }
                menu = -1;
            }
        }
    }
}

void LevelEditor::MouseCollisonObjects(SDL_Event event, std::vector<PleacedObject>& objects) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        for (int i = 0; i < objects.size(); i++)
        {
            if (SimpleCollision(mouse, objects[i].rect) == 1) {
                clickBuffer = 10;
                clickRectangle = objects[i].rect;
                clickTexture = objects[i].text;
                currentName = objects[i].name;
                objects.erase(objects.begin() + i);
                clicked = true;
                menu = -1;
            }
        }
    }
}

void LevelEditor::UpdateMouse() {
    if (moveType == 0) {
        Uint32 mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);
        clickRectangle.x = mouse.x;
        clickRectangle.y = mouse.y;
    }
}

void LevelEditor::UpdateKeyboard(SDL_Event event) {
    if (clicked) {
        if (moveType == 1) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    clickRectangle.y -= moveSpeed;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    clickRectangle.y += moveSpeed;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    clickRectangle.x -= moveSpeed;
                }
                if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    clickRectangle.x += moveSpeed;
                }
            }
        }

    }
}

void LevelEditor::Pleace(SDL_Event event) {
    PleacedObject obj;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        objects.push_back(obj);
        objects[objects.size() - 1].text = clickTexture;
        objects[objects.size() - 1].rect = clickRectangle;
        objects[objects.size() - 1].name = currentName;
        clicked = false;
        clickBuffer += 10;
    }
}

void LevelEditor::DeleteObject(SDL_Event event) {
    if (event.key.keysym.scancode == SDL_SCANCODE_DELETE) {
        for (size_t i = 0; i < objects.size(); i++)
        {
            if (SimpleCollision(mouse, objects[i].rect) == 1) {
                objects.erase(objects.begin() + i);
            }
        }
    }
    
}

void LevelEditor::Move(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_W) {
            for (int i = 0; i < objects.size(); i++)
            {
                objects[i].rect.y -= moveSpeed;
            }
            rectanglePlayer.y -= moveSpeed;
            yTrue += moveSpeed;

        }
        if (event.key.keysym.scancode == SDL_SCANCODE_S) {
            for (int i = 0; i < objects.size(); i++)
            {
                objects[i].rect.y += moveSpeed;
            }
            rectanglePlayer.y += moveSpeed;
            yTrue -= moveSpeed;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_A) {
            for (int i = 0; i < objects.size(); i++)
            {
                objects[i].rect.x += moveSpeed;
            }
            rectanglePlayer.x += moveSpeed;
            xTrue -= moveSpeed;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_D) {
            for (int i = 0; i < objects.size(); i++)
            {
                objects[i].rect.x -= moveSpeed;
            }
            rectanglePlayer.x -= moveSpeed;
            xTrue += moveSpeed;
        }
    }
}

void LevelEditor::Settings(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_5) {
            if (scaleWidth == true) {
                scaleWidth = false;
            }
            else
            {
                scaleWidth = true;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_MINUS) {
            if (scaleWidth == true) {
                clickRectangle.w -= scaleSpeed;
            }
            else
            {
                clickRectangle.h -= scaleSpeed;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_EQUALS) {
            if (scaleWidth == true) {
                clickRectangle.w += scaleSpeed;
            }
            else
            {
                clickRectangle.h += scaleSpeed;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_M) {
            if (moveType == 1) {
                moveType = 0;
            }
            else
            {
                moveType = 1;
            }
        }
    }
}

void LevelEditor::ChangeScales(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_1) {
            if (scaleSpeed > 1) {
                scaleSpeed--;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_2) {
            if (scaleSpeed < 100) {
                scaleSpeed++;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_3) {
            if (moveSpeed > 1) {
                moveSpeed--;
            }
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_4) {
            if (moveSpeed < 100) {
                moveSpeed++;
            }
        }
    }
}

void LevelEditor::Render() {
    if (clickBuffer > 0) {
        clickBuffer--;
    }
    SDL_RenderCopy(renderer, texturePlayer, NULL, &rectanglePlayer);
    if (clicked) {
        SDL_RenderCopy(renderer, clickTexture, NULL, &clickRectangle);
    }
    for (size_t i = 0; i < objects.size(); i++)
    {
        SDL_RenderCopy(renderer, objects[i].text, NULL, &objects[i].rect);
    }
    if (menu != -1) {
        SDL_Rect rect;
        int posX = 200;
        int posY = 400;
        switch (menu)
        {
        case 0:
            for (int i = 0; i < texturesMap.size(); i++) {
                SDL_RenderCopy(renderer, texturesMap[i], NULL, &rectangles[i]);
            }
        break;
        case 1:
            for (int i = 0; i < texturesMobs.size(); i++) {
                SDL_RenderCopy(renderer, texturesMobs[i], NULL, &rectangles[i]);
            }
        break;
        case 2:
            for (int i = 0; i < texturesEquipment.size(); i++) {
                SDL_RenderCopy(renderer, texturesEquipment[i], NULL, &rectangles[i]);
            }
        break;
        }
    }
    for (size_t i = 0; i < 6; i++)
    {
        ui->RenderSingleButton(i, 1);
    }
    if (clicked) {
        ui->font->RenderText(renderer, "X " + std::to_string(clickRectangle.x), 1200, 300, 30, 30, 31);
        ui->font->RenderText(renderer, "Y " + std::to_string(clickRectangle.y), 1200, 350, 30, 30, 31);
        ui->font->RenderText(renderer, "W " + std::to_string(clickRectangle.w), 1200, 400, 30, 30, 31);
        ui->font->RenderText(renderer, "H " + std::to_string(clickRectangle.h), 1200, 450, 30, 30, 31);
    }
    ui->font->RenderText(renderer, "SS " + std::to_string(scaleSpeed), 1200, 200, 30, 30, 31);
    ui->font->RenderText(renderer, "MS " + std::to_string(moveSpeed), 1200, 250, 30, 30, 31);
    ui->font->RenderText(renderer, "MT " + std::to_string(moveType), 1200, 500, 30, 30, 31);
    ui->font->RenderText(renderer, "XT " + std::to_string(xTrue), 1200, 550, 30, 30, 31);
    ui->font->RenderText(renderer, "YT " + std::to_string(yTrue), 1200, 600, 30, 30, 31);


}

void LevelEditor::ConvertToFile() {
    std::ofstream file("EditorOutput/level1.txt");
    if (file.is_open()) {
        //file << "player" << "\n";
        //file << rectanglePlayer.x << "\n";
        //file << rectanglePlayer.y << "\n";
        //file << rectanglePlayer.w << "\n";
        //file << rectanglePlayer.h << "\n";
        for (int i = 0; i < objects.size(); i++)
        {
            file << objects[i].name << "\n";
            file << objects[i].rect.x << "\n";
            file << objects[i].rect.y << "\n";
            file << objects[i].rect.w << "\n";
            file << objects[i].rect.h << "\n";
            
        }
    }
    file.close();

}

LevelEditor::~LevelEditor() {
    delete ui;

    for (size_t i = 0; i < texturesMap.size(); ++i) {
        SDL_DestroyTexture(texturesMap[i]);
    }

    for (size_t i = 0; i < texturesMobs.size(); ++i) {
        SDL_DestroyTexture(texturesMobs[i]);
    }

    for (size_t i = 0; i < texturesEquipment.size(); ++i) {
        SDL_DestroyTexture(texturesEquipment[i]);
    }

    SDL_DestroyTexture(texturePlayer);
}
