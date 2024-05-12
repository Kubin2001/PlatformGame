#include <iostream>
#include <SDL.h>
#include "ParticlesManager.h"

ParticlesManager::ParticlesManager(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

//Getteers and setters
SDL_Texture* ParticlesManager::GetTexture() {
    return textureWayve;
}

void ParticlesManager::SetTexture(SDL_Texture * temptex) {
    textureWayve = temptex;
}


SDL_Rect* Particle::GetRectangle() {
    return &rectangle;
}


int Particle::GetDirection() {
    return direction;
}
void Particle::SetDirection(int temp) {
    direction = temp;
}

int Particle::GetSpeed() {
    return speed;
}
void Particle::SetSpeed(int temp) {
    speed = temp;
}
int Particle::GetLifeTime() {
    return lifeTime;
}
void Particle::SetLifeTime(int temp) {
    lifeTime = temp;
}

bool Particle::GetRenderable() { return renderable; }

void Particle::SetRenderable(bool temp) { renderable = temp; }
//Getteers and setters

void ParticlesManager::Render(SDL_Rect camRect) {
    SDL_Rect temp;
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    for (int i = 0; i < PlayerAttackParticles.size(); i++) {
        if (PlayerAttackParticles[i].GetRenderable()) {
            temp.x = PlayerAttackParticles[i].GetRectangle()->x - camRect.x;
            temp.y = PlayerAttackParticles[i].GetRectangle()->y - camRect.y;
            temp.w = PlayerAttackParticles[i].GetRectangle()->w;
            temp.h = PlayerAttackParticles[i].GetRectangle()->h;
            switch (PlayerAttackParticles[i].GetDirection()) {
            case 1:
                SDL_RenderCopy(renderer, textureWayve, NULL, &temp);
                break;
            case 2:
                SDL_RenderCopyEx(renderer, textureWayve, NULL, &temp, 0.0, NULL, flip);
                break;
            }
        }
    }

    for (int i = 0; i < EnemyAttackParticles.size(); i++) {
        if (EnemyAttackParticles[i].GetRenderable()) {
            temp.x = EnemyAttackParticles[i].GetRectangle()->x - camRect.x;
            temp.y = EnemyAttackParticles[i].GetRectangle()->y - camRect.y;
            temp.w = EnemyAttackParticles[i].GetRectangle()->w;
            temp.h = EnemyAttackParticles[i].GetRectangle()->h;
            switch (EnemyAttackParticles[i].GetDirection()) {
            case 1:
                SDL_RenderCopy(renderer, textureWayve, NULL, &temp);
                break;
            case 2:
                SDL_RenderCopyEx(renderer, textureWayve, NULL, &temp, 0.0, NULL, flip);
                break;
            }
        }
    }
}

void ParticlesManager::CreatePlayerAttackParticles(SDL_Rect rect, int direction, int speed, int lifeTime) {
    PlayerAttackParticle temp(rect,direction,speed,lifeTime);
    PlayerAttackParticles.push_back(temp);
}

void ParticlesManager::CreateEnemyAttackParticles(SDL_Rect rect, int direction, int speed, int lifeTime) {
    EnemyAttackParticle temp(rect,direction,speed,lifeTime);
    EnemyAttackParticles.push_back(temp);
}

void ParticlesManager::CheckColision(Mobs* mobs, Player* player, SDL_Rect camRect) {
    CheckColisionMobs(mobs, camRect);
    CheckColisionPlayer(player, camRect);
}

void ParticlesManager::CheckColisionMobs(Mobs* mobs,SDL_Rect camRect) {
    for (int i = 0; i < PlayerAttackParticles.size(); i++)
    {
        if (SimpleCollision(camRect, *PlayerAttackParticles[i].GetRectangle())) {
            PlayerAttackParticles[i].SetRenderable(true);
        }
        else
        {
            PlayerAttackParticles[i].SetRenderable(false);
        }
    }
    for (int i = 0; i < PlayerAttackParticles.size(); i++)
    {
        for (int j = 0; j < mobs->getEnemies().size(); j++)
        {
            if (mobs->getEnemies()[j]->getInvTime() < 1) {
                if (SimpleCollision(*PlayerAttackParticles[i].GetRectangle(), *mobs->getEnemies()[j]->GetRectangle())) {
                    mobs->getEnemies()[j]->setHitPoints(mobs->getEnemies()[j]->getHitPoints() - 10);
                    mobs->getEnemies()[j]->setInvTime(20);
                    if (mobs->getEnemies()[j]->getHitPoints() < 1) {
                        mobs->getEnemies().erase(mobs->getEnemies().begin() + j);
                    }
                }
            }
        }
    };
}

void ParticlesManager::CheckColisionPlayer(Player * player, SDL_Rect camRect) {
    for (int i = 0; i < EnemyAttackParticles.size(); i++)
    {
        if (SimpleCollision(camRect, *EnemyAttackParticles[i].GetRectangle())) {
            EnemyAttackParticles[i].SetRenderable(true);
        }
        else
        {
            EnemyAttackParticles[i].SetRenderable(false);
        }
    }
    for (int i = 0; i < EnemyAttackParticles.size(); i++)
    {
        if (SimpleCollision(*EnemyAttackParticles[i].GetRectangle(), *player->GetRectangle())) {
            player->SetDamage(true);
        }           
    }
}

void ParticlesManager::EndLifeTime() {
    for (int i = 0; i < PlayerAttackParticles.size(); i++) {
        PlayerAttackParticles[i].SetLifeTime(PlayerAttackParticles[i].GetLifeTime()- 1);
        if (PlayerAttackParticles[i].GetLifeTime() < 1) {
            PlayerAttackParticles.erase(PlayerAttackParticles.begin() + i);
        }
    }
    for (int i = 0; i < EnemyAttackParticles.size(); i++) {
        EnemyAttackParticles[i].SetLifeTime(EnemyAttackParticles[i].GetLifeTime() - 1);
        if (EnemyAttackParticles[i].GetLifeTime() < 1) {
            EnemyAttackParticles.erase(EnemyAttackParticles.begin() + i);
        }
    }
}

void ParticlesManager::MoveParticles(const Uint8* state, Player* player) {
    MoveParticlesPlayer(state, player);
    MoveParticlesEnemy(state, player);
}

void ParticlesManager::MoveParticlesPlayer(const Uint8* state, Player* player) {
    if (PlayerAttackParticles.empty()) {
        return;
    }
    for (int i = 0; i < PlayerAttackParticles.size(); i++)
    {
        PlayerAttackParticles[i].GetRectangle()->x += PlayerAttackParticles[i].GetSpeed();
    }
}

void ParticlesManager::MoveParticlesEnemy(const Uint8* state, Player* player) {
    if (EnemyAttackParticles.empty()) {
        return;
    }
    for (int i = 0; i < EnemyAttackParticles.size(); i++)
    {
        EnemyAttackParticles[i].GetRectangle()->x += EnemyAttackParticles[i].GetSpeed();
    }
}



ParticlesManager::~ParticlesManager() {
    SDL_DestroyTexture(textureWayve);
}

