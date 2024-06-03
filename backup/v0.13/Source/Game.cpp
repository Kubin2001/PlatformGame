#include <SDL.h>
#include <iostream>
#include "SDL_image.h"

#include "Game.h"

extern int windowtype;
extern bool status;

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    player = nullptr;
    map = nullptr;
    mobs = nullptr;
    ui = nullptr;
    equipment = nullptr;
}

void Game::SetUpWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    rectback.x = 0;
    rectback.y = 0;
    rectback.w = 1400;
    rectback.h = 800;
}

void Game::Start() {
    switch (windowtype)
    {
    case 1:
        map = new Map(renderer);
        mobs = new Mobs(renderer);
        ui = new UI(renderer);
        player = new Player(renderer);
        equipment = new Equipment(renderer);
        ui->CreateButton();
        ui->font->LoadText(36,29,29);
        LoadTextures();
        break;
    case 2:
        map->CreateFloor();
        map->CreateLevel();
        mobs->LoadMobs();
        ui->CreateHearths();
        equipment->LoadEquipment();
        LoadTextures();
        break;
    }

}

void Game::LoadTextures() {
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
        map->SetTextureFlag(load("Textures/Terrain/flag.png", renderer));
        mobs->SetTextureCharger(load("Textures/charger.png", renderer));
        ui->SetTextureHearth(load("Textures/Interface/hearth.png", renderer));
        equipment->SetTextureShortSword(load("Textures/Equipment/shortSword.png", renderer));
        break;
    }
    ui->SetTextureButtonInfo(load("Textures/Interface/buttonInfo.png", renderer));

}

void Game::Exit() {
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


void Game::Events() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    switch (windowtype) {
        case 1:
            break;
        case 2:
            player->setColison(false, 0);
            player->setColison(false, 1);
            player->setColison(false, 2);
            player->setColison(false, 3);
            player->CheckDamage(ui);
            map->DetectColison(player,ui);
            mobs->DetectColison(player, map);
            equipment->DetectCollison(player);
            player->UpdateWeapon();
            break;
    }

    while (SDL_PollEvent(&event)) {
        switch (windowtype) {
        case 1:
            ui->OnClick(event);
            break;
        }
        Exit();
    }

}

void Game::Movement() {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    switch (windowtype) {
    case 1:
        break;
    case 2:
        player->Jump(state);
        player->Attack(state,mobs);
        map->MoveMap(state, player);
        mobs->MoveMobs(state, player);
        equipment->MoveEquipment(state, player);
        break;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    switch (windowtype) {
    case 1:
        SDL_RenderCopy(renderer, textback, NULL, &rectback);
        ui->Render();
        break;
    case 2:
        SDL_RenderCopy(renderer, textback, NULL, &rectback);
        player->Render();
        map->Render();
        mobs->Render();
        ui->Render();
        equipment->Render();
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::Clear() {
    delete player;
    delete map;
    delete mobs;
    delete ui;
    delete equipment;
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

