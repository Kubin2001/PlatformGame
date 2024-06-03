#include <SDL.h>
#include <iostream>
#include "SDL_image.h"

#include "Game.h"

Game::Game() {
    window = nullptr;
    renderer = nullptr;

}

void Game::SetUpWindow(int& windowtype) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    rectback.x = 0;
    rectback.y = 0;
    rectback.w = 1400;
    rectback.h = 800;
}

void Game::Start(int& windowtype) {
    switch (windowtype)
    {
    case 1:
        player = new Player();
        map = new Map();
        mobs = new Mobs();
        ui = new UI();
        ui->CreateButton();
        ui->font->LoadText();
        LoadTextures(windowtype);
        break;
    case 2:
        map->CreateFloor();
        map->CreateLevel();
        mobs->LoadMobs();
        ui->CreateHearths();
        LoadTextures(windowtype);
        break;
    }

}

void Game::LoadTextures(int& windowtype) {
    switch (windowtype)
    {
        case 1:
            textback = (load("Textures/background.png", renderer));
            ui->SetTextureButton(load("Textures/Interface/button.png", renderer));
            ui->font->SetTexture(load("Textures/Interface/font.png", renderer));
            break;
        case 2:
            player->SetTexture(load("Textures/player.png", renderer));
            map->SetTextureGrass(load("Textures/Terrain/grass.png", renderer));
            map->SetTexturePlatform(load("Textures/Terrain/platform.png", renderer));
            map->SetTexturePilar(load("Textures/Terrain/pillar.png", renderer));
            mobs->SetTextureCharger(load("Textures/charger.png", renderer));
            ui->SetTextureHearth(load("Textures/Interface/hearth.png", renderer));
            break;
    }
    
}

void Game::Exit(bool& status, int& windowtype) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { 
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                switch (windowtype) {
                case 1:
                    status = false;
                    windowtype = 0;
                    break;
                case 2:
                    windowtype = 1;
                    break;
                }
            }
        }
    }
}


void Game::Events(bool& status, int& windowtype){
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    switch (windowtype) {
    case 1:
        if (state[SDL_SCANCODE_W]) {
            windowtype = 2;
        }
        ui->OnClick(windowtype);
        break;
    case 2:
        player->setColison(false, 0);
        player->setColison(false, 1);
        player->setColison(false, 2);
        player->setColison(false, 3);
        player->CheckDamage(ui);
        map->DetectColison(player);
        mobs->DetectColison(player, map);
        break;
    }
}

void Game::Movement(int& windowtype) {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    switch (windowtype) {
    case 1:    
        break;
    case 2:
        player->Jump(state);
        map->MoveMap(state, player);
        mobs->MoveMobs(state, player);
        break;
    }
}


void Game::Render(int& windowtype) {
    SDL_RenderClear(renderer);
    switch (windowtype) {
        case 1:
            SDL_RenderCopy(renderer, textback, NULL, &rectback);
            ui->RenderButton(renderer);
            ui->font->Render(renderer);
            break;
        case 2:
            SDL_RenderCopy(renderer, textback, NULL, &rectback);
            player->Render(renderer);
            map->Render(renderer);
            mobs->Render(renderer);
            ui->Render(renderer);
            break;
    }
    SDL_RenderPresent(renderer);
}

void Game:: Clear() {
    delete player;
    delete map;
    delete mobs;
    delete ui;
}


SDL_Texture* Game::load(const char* file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;

}


Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    std::cout << "Resources Destroyed";
}

