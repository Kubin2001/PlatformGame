#include <SDL.h>
#include <iostream>
#include "SDL_image.h"

#include "Game.h"

Game::Game() {
    player = new Player();
    map = new Map();
    mobs = new Mobs();
    window = nullptr;
    renderer = nullptr;

}

void Game::StartGame() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1400, 800, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    rectback.x = 0;
    rectback.y = 0;
    rectback.w = 1400;
    rectback.h = 800;

    map->CreateFloor();
    map->CreateLevel();
    mobs->LoadMobs();
    LoadTextures();
    
}

void Game::LoadTextures() {
    player->SetTexture(load("Textures/player.png", renderer));
    map->SetTextureGrass(load("Textures/Terrain/grass.png", renderer));
    map->SetTexturePlatform(load("Textures/Terrain/platform.png", renderer));
    map->SetTexturePilar(load("Textures/Terrain/pillar.png", renderer));
    mobs->SetTextureCharger(load("Textures/charger.png", renderer));
    textback = (load("Textures/background.png", renderer));

}

void Game::Exit(bool& status, const Uint8* state) {
    if (state[SDL_SCANCODE_ESCAPE]) {
        status = false;
    }
}

void Game::Events() {
    player->setColison(false, 0);
    player->setColison(false, 1);
    player->setColison(false, 2);
    player->setColison(false, 3);
    map->DetectColison(player);
    mobs->DetectColison(player);
}

void Game::Movement(bool &status) {
    SDL_PumpEvents();
    const Uint8* state = SDL_GetKeyboardState(NULL);
    Exit(status,state);
    player->Jump(state);
    map->MoveMap(state,player);
    mobs->MoveMobs(state,player);

   
}


void Game::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textback, NULL, &rectback);
    player->Render(renderer);
    map->Render(renderer);
    mobs->Render(renderer);
    SDL_RenderPresent(renderer);
}

SDL_Texture* Game::load(const char* file, SDL_Renderer* ren) {
    SDL_Surface* tmpSurface = IMG_Load(file);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;

}


Game::~Game() {
    delete player;
    delete map;
    delete mobs;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    std::cout << "Resources Destroyed";
}

