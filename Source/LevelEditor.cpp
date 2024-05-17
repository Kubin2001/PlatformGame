#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <fstream> 
#include <filesystem>
#include "LevelEditor.h"
#include "UI.h"
#include "Colision.h"

extern SDL_Texture* load(const char* file, SDL_Renderer* ren);


LevelEditor::LevelEditor(SDL_Renderer* renderer) {
    this->renderer = renderer;
    ui = new UI(renderer);
    ui->font->LoadText(40, 29, 29);
    ui->CreateSingleButton(300, 0, 200, 50, "TERRAIN", 26, 27);
    ui->CreateSingleButton(600, 0, 200, 50, "MOBS", 29, 30);
    ui->CreateSingleButton(900, 0, 200, 50, "EQUIPMENT", 20, 21);

    ui->CreateSingleButton(1150, 100, 200, 50, "CLOSE", 20, 21);

    ui->CreateSingleButton(50, 100, 200, 50, "RESET", 20, 21);

    ui->CreateSingleButton(50, 200, 200, 50, "CREATE", 20, 21);
    ui->CreateSingleButton(50, 300, 200, 50, "LOAD", 20, 21);
}

void LoadHelper(std::vector<PleacedObject>& vector, std::string directory, SDL_Renderer* renderer) {
    PleacedObject obj;
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.path().extension() == ".png") {
            std::string pathString = entry.path().string();
            const char* path = pathString.c_str();
            vector.push_back(obj);
            vector[vector.size() - 1].text = load(path, renderer);
            SDL_QueryTexture(vector[vector.size() - 1].text, NULL, NULL, &vector[vector.size() - 1].rect.w, &vector[vector.size() - 1].rect.h);
            std::string temp = "";
            for (size_t i = directory.length(); i < pathString.length(); i++)
            {
                if (pathString[i + 1] == '.') {
                    break;
                }
                temp += pathString[i + 1];
            }
            vector[vector.size() - 1].name = temp;
            temp = "";
        }

    }
}

void LevelEditor::LoadTextures() {
    std::string terrain = "Textures/Terrain";
    std::string mobs = "Textures/MobsEditor";
    std::string equipment = "Textures/Equipment";
    LoadHelper(mapObjects, terrain, renderer);
    LoadHelper(mobsObjects, mobs, renderer);
    LoadHelper(equipmentObjects, equipment, renderer);

    texturePlayer = load("Textures/player.png", renderer);

    ui->SetTextureButton(load("Textures/Interface/button.png", renderer));
    ui->font->SetTexture(load("Textures/Interface/font.png", renderer));
    ui->SetTextureButtonInfo(load("Textures/Interface/buttonInfo.png", renderer));
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
            case 0://Terrain
                for (int i = 0; i < mapObjects.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 70;
                    rectangles[rectangles.size() - 1].h = 70;
                    posX += 80;
                }
                break;
            case 1://Mobs
                for (int i = 0; i < mobsObjects.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 70;
                    rectangles[rectangles.size() - 1].h = 70;
                    posX += 80;
                }
                break;
            case 2://Equipment
                for (int i = 0; i < equipmentObjects.size(); i++)
                {
                    rectangles.push_back(rect);
                    rectangles[rectangles.size() - 1].x = posX;
                    rectangles[rectangles.size() - 1].y = posY;
                    rectangles[rectangles.size() - 1].w = 70;
                    rectangles[rectangles.size() - 1].h = 70;
                    posX += 80;
                }
                break;
            case 4://Reset
                ResetPossition();
                break;
            case 5://Create
                ResetPossition();
                ConvertToFile();
                break;
            case 6://Load
                LoadFile();
                menu = -1;
                break;
        }
        if (clickBuffer == 0) {
            switch (menu)
            {
                case 0:
                    MouseCollison(event, mapObjects);
                    break;
                case 1:
                    MouseCollison(event, mobsObjects);
                    break;
                case 2:
                    MouseCollison(event, equipmentObjects);
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
    CopyObject(event);
    DeleteObject(event);
    
}

void LevelEditor::MouseCollison(SDL_Event event, std::vector<PleacedObject>& object) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_GetMouseState(&mouse.x, &mouse.y);
        mouse.w = 1;
        mouse.h = 1;
        for (int i = 0; i < rectangles.size(); i++)
        {
            if (SimpleCollision(mouse, rectangles[i] ) == 1) {
                clickRectangle = rectangles[i];
                clickTexture = object[i].text;
                currentName = object[i].name;
                clicked = true;
                clickBuffer += 10;
                clickRectangle.w = object[i].rect.w;
                clickRectangle.h = object[i].rect.h;
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

void LevelEditor::CopyObject(SDL_Event event) {
    if (event.key.keysym.scancode == SDL_SCANCODE_C) {
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
                clicked = true;
                menu = -1;
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

void LevelEditor::ResetPossition() {
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
            for (int i = 0; i < mapObjects.size(); i++) {
                SDL_RenderCopy(renderer, mapObjects[i].text, NULL, &rectangles[i]);
            }
        break;
        case 1:
            for (int i = 0; i < mobsObjects.size(); i++) {
                SDL_RenderCopy(renderer, mobsObjects[i].text, NULL, &rectangles[i]);
            }
        break;
        case 2:
            for (int i = 0; i < equipmentObjects.size(); i++) {
                SDL_RenderCopy(renderer, equipmentObjects[i].text, NULL, &rectangles[i]);
            }
        break;
        }
    }
    for (size_t i = 0; i < 7; i++)
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

void LevelEditor::LoadFile() {
    PleacedObject obj;

    std::string directory = "Editor/Input";
    std::string pathString = "";
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.path().extension() == ".txt") {
            pathString = entry.path().string();
            pathString = pathString.substr(directory.length() +1, pathString.length());
            break;
        }
    }
    std::ifstream levelFile(directory + '/' + pathString);
    std::string line;
    objects.clear();
    if (levelFile.is_open()) {
        while (getline(levelFile, line)) {
                objects.push_back(obj);
                for (int i = 0; i < mapObjects.size(); i++)
                {
                    if (line == mapObjects[i].name) {
                        objects[objects.size() - 1].text = mapObjects[i].text;
                        break;
                    }
                }
                for (int i = 0; i < mobsObjects.size(); i++)
                {
                    if (line == mobsObjects[i].name) {
                        objects[objects.size() - 1].text = mobsObjects[i].text;
                        break;
                    }
                }
                for (int i = 0; i < equipmentObjects.size(); i++)
                {
                    if (line == equipmentObjects[i].name) {
                        objects[objects.size() - 1].text = equipmentObjects[i].text;
                        break;
                    }
                }

                objects[objects.size() - 1].name = line;
                getline(levelFile, line);
                objects[objects.size() - 1].rect.x = std::stoi(line);
                getline(levelFile, line);
                objects[objects.size() - 1].rect.y = std::stoi(line);
                getline(levelFile, line);
                objects[objects.size() - 1].rect.w = std::stoi(line);
                getline(levelFile, line);
                objects[objects.size() - 1].rect.h = std::stoi(line);
        }
        std::cout << objects.size()<<"\n";
    }
    else
    {
        std::cout << "Nie mo¿na otworzyæ pliku\n";
    }
}

void LevelEditor::ConvertToFile() {
    std::ofstream file("Editor/Output/level1.txt");
    if (file.is_open()) {
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

    for (size_t i = 0; i < mapObjects.size(); ++i) {
        SDL_DestroyTexture(mapObjects[i].text);
    }

    for (size_t i = 0; i < mobsObjects.size(); ++i) {
        SDL_DestroyTexture(mobsObjects[i].text);
    }

    for (size_t i = 0; i < equipmentObjects.size(); ++i) {
        SDL_DestroyTexture(equipmentObjects[i].text);
    }

    SDL_DestroyTexture(texturePlayer);
}
