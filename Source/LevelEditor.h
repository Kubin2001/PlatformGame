#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include "UI.h"

class PleacedObject {
    public:
        SDL_Texture* text;
        SDL_Rect rect;
        std::string name = "";
};


class LevelEditor
{
    private:
        UI* ui;
        SDL_Renderer* renderer;
        std::vector<PleacedObject> mapObjects;
        std::vector<PleacedObject> mobsObjects;
        std::vector<PleacedObject> equipmentObjects;
        PleacedObject mouseObject;
        SDL_Texture* texturePlayer;
        SDL_Rect rectanglePlayer{ 700,400,50,100 };
        int menu = -1;
        std::vector<SDL_Rect> rectangles;
        std::vector<PleacedObject> objects;
        int clickBuffer = 0;

        int xTrue = 0;
        int yTrue = 0;

        SDL_Rect clickRectangle;
        SDL_Rect mouse;
        SDL_Texture* clickTexture;
        bool clicked = false;
        bool scaleWidth = true;
        int scaleSpeed = 1;
        int moveSpeed = 1;
        int moveType = 0;

        std::string currentName;

    public:
        LevelEditor(SDL_Renderer* renderer);

        void LoadTextures();

        void OnClick(SDL_Event event);

        void MouseCollison(SDL_Event event, std::vector<PleacedObject>& object);

        void MouseCollisonObjects(SDL_Event event, std::vector<PleacedObject>& objects);

        void UpdateMouse();

        void UpdateKeyboard(SDL_Event event);

        void Pleace(SDL_Event event);

        void DeleteObject(SDL_Event event);

        void Settings(SDL_Event event);

        void Move(SDL_Event event);

        void ResetPossition();

        void ChangeScales(SDL_Event event);

        void Render();

        void LoadFile();

        void ConvertToFile();

        ~LevelEditor();
};
