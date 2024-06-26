#include <SDL.h>
#include <iostream>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SoundManager.h"
#include "TextureManager.h"

#include "Game.h"

extern int windowtype;
extern int localWindow;
extern bool status;
extern int windowWidth;
extern int windowHeight;
extern long long int framesCounter;

Game::Game() {
    window = nullptr;
    renderer = nullptr;

    camera = nullptr;
    player = nullptr;
    map = nullptr;
    mobs = nullptr;
    ui = nullptr;
    collectables = nullptr;
    levelEditor = nullptr;
    particlesManager = nullptr;
}

void Game::SetUpWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Platform", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    textback = (load("Textures/background.png", renderer));
}

void Game::Start() {

    switch (windowtype)
    {
        case 1:
            ui = new UI(renderer);
            LoadTextures();
            ui->font->LoadText(29, 29);
            ui->CreateButton();
            break;
        case 2:
            camera = new Camera;
            ui = new UI(renderer);
            ui->font->LoadText(29, 29);
            map = new Map(renderer);
            mobs = new Mobs(renderer);
            player = new Player(renderer);
            collectables = new Collectables(renderer);
            particlesManager = new ParticlesManager(renderer);
            LoadTextures();
            player->LoadAnimations(48);
            map->CreateLevel();
            mobs->LoadMobs();
            ui->CreateHearths();
            collectables->LoadEquipment();
            SoundManager::LoadGame();
            break;
        case 3:
            levelEditor = new LevelEditor(renderer);
            LoadTextures();
            break;
    }

}

void Game::LoadTextures() {
    switch (windowtype)
    {
    case 1:
        ui->SetTextureButton(load("Textures/Interface/button.png", renderer));
        ui->font->SetTexture(load("Textures/Interface/font.png", renderer));
        ui->SetTextureButtonInfo(load("Textures/Interface/buttonInfo.png", renderer));
        break;
    case 2:
        player->SetTexture(load("Textures/player.png", renderer));
        map->LoadTextures();
        mobs->LoadTextures();
        particlesManager->LoadTextures();
        ui->SetTextureHearth(load("Textures/Interface/hearth.png", renderer));
        ui->font->SetTexture(load("Textures/Interface/font.png", renderer));
        collectables->LoadTextures();
        ui->SetTextureButtonInfo(load("Textures/Interface/buttonInfo.png", renderer));
        break;
    case 3:
        levelEditor->LoadTextures();
        break;
    }
}

void Game::Exit() {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            switch (windowtype) {
            case 1:
                status = false;
                localWindow = 0;
                break;
            case 2:
                localWindow = 1;
                break;
            case 3:
                localWindow = 1;
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
            framesCounter++;
            if (framesCounter % 60 == 0 && ui->GetScore() > 0) {
                ui->SetScore(ui->GetScore() - 1);
            }
            player->setColison(false, 0);
            player->setColison(false, 1);
            player->setColison(false, 2);
            player->setColison(false, 3);
            player->CheckDamage(ui);
            map->DetectColison(player,ui,camera);
            mobs->DetectColison(player, map,*camera->GetRectangle());
            particlesManager->CheckColision(mobs,player,*camera->GetRectangle());
            particlesManager->EndLifeTime();
            collectables->DetectCollison(ui,player,*camera->GetRectangle());
            player->UpdateWeapon();
            break;
        case 3:
            levelEditor->UpdateMouse();
            break;
    }

    while (SDL_PollEvent(&event)) {
        switch (windowtype) {
        case 1:
            ui->OnClick(event);
            break;
        case 2:
            break;
        case 3:
            levelEditor->OnClick(event);
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
        player->Move(state);
        camera->UpdatePosition(*player->GetRectangle());
        player->Attack(state,particlesManager);
        mobs->MoveMobs(state, player,map,particlesManager);
        particlesManager->MoveParticles(state,player);
        break;
    case 3:

        break;
    }
}


void Game::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textback, NULL, &rectback);
    switch (windowtype) {
    case 1:
        ui->Render();
        break;
    case 2:
        map->Render(*camera->GetRectangle());
        player->Render(*camera->GetRectangle());
        map->RenderObjectsPostPlayer(*camera->GetRectangle());
        mobs->Render(*camera->GetRectangle());
        ui->Render();
        collectables->Render(*camera->GetRectangle());
        particlesManager->Render(*camera->GetRectangle());
        break;
    case 3:
        levelEditor->Render();
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::Clear() {
    switch (windowtype) {
    case 1:
        delete ui;
        ui = nullptr;
        break;
    case 2:
        framesCounter = 0;
        delete camera;
        camera = nullptr;
        delete ui;
        ui = nullptr;
        delete player;
        player = nullptr;
        delete map;
        map = nullptr;
        delete mobs;
        mobs = nullptr;
        delete collectables;
        collectables = nullptr;
        delete particlesManager;
        particlesManager = nullptr;
        SoundManager::UnLoadGame();
        break;
    case 3:
        delete levelEditor;
        break;
    }
}

void Game::SetWindow() {
    windowtype = localWindow;
}


Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    std::cout << "Resources Destroyed";
}

