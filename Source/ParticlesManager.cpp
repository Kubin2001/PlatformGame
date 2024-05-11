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
//Getteers and setters

void ParticlesManager::Render() {
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    for (int i = 0; i < PlayerAttackParticles.size(); i++) {
        switch (PlayerAttackParticles[i].GetDirection()) {
            case 1:
                SDL_RenderCopy(renderer, textureWayve, NULL, PlayerAttackParticles[i].GetRectangle());
                break;
            case 2:
                SDL_RenderCopyEx(renderer, textureWayve, NULL, PlayerAttackParticles[i].GetRectangle(), 0.0, NULL, flip);
                break;
        }
    }

    for (int i = 0; i < EnemyAttackParticles.size(); i++) {
        switch (EnemyAttackParticles[i].GetDirection()) {
        case 1:
            SDL_RenderCopy(renderer, textureWayve, NULL, EnemyAttackParticles[i].GetRectangle());
            break;
        case 2:
            SDL_RenderCopyEx(renderer, textureWayve, NULL, EnemyAttackParticles[i].GetRectangle(), 0.0, NULL, flip);
            break;
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

void ParticlesManager::CheckColision(Mobs* mobs, Player* player) {
    CheckColisionMobs(mobs);
    CheckColisionPlayer(player);
}

void ParticlesManager::CheckColisionMobs(Mobs* mobs) {
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

void ParticlesManager::CheckColisionPlayer(Player * player) {
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
    if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
        for (int i = 0; i < PlayerAttackParticles.size(); i++)
        {
            PlayerAttackParticles[i].GetRectangle()->x -= 4;
        }
    }
    if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
        for (int i = 0; i < PlayerAttackParticles.size(); i++)
        {
            PlayerAttackParticles[i].GetRectangle()->x += 4;
        }
    }
    if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
        for (int i = 0; i < PlayerAttackParticles.size(); i++)
        {
            PlayerAttackParticles[i].GetRectangle()->y -= 5;
        }
    }
    if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
        for (int i = 0; i < PlayerAttackParticles.size(); i++)
        {
            PlayerAttackParticles[i].GetRectangle()->y += 5;
        }
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
    if (state[SDL_SCANCODE_RIGHT] && player->getColison(2) == false) {
        for (int i = 0; i < EnemyAttackParticles.size(); i++)
        {
            EnemyAttackParticles[i].GetRectangle()->x -= 4;
        }
    }
    if (state[SDL_SCANCODE_LEFT] && player->getColison(0) == false) {
        for (int i = 0; i < EnemyAttackParticles.size(); i++)
        {
            EnemyAttackParticles[i].GetRectangle()->x += 4;
        }
    }
    if (player->getColison(1) == 0 && player->getJumpBuffer() < 20) {//Góra
        for (int i = 0; i < EnemyAttackParticles.size(); i++)
        {
            EnemyAttackParticles[i].GetRectangle()->y -= 5;
        }
    }
    if (player->getColison(3) == 0 && player->getJumpBuffer() > 25) {//Dó³
        for (int i = 0; i < EnemyAttackParticles.size(); i++)
        {
            EnemyAttackParticles[i].GetRectangle()->y += 5;
        }
    }
    for (int i = 0; i < EnemyAttackParticles.size(); i++)
    {
        EnemyAttackParticles[i].GetRectangle()->x += EnemyAttackParticles[i].GetSpeed();
    }
}



ParticlesManager::~ParticlesManager() {
    SDL_DestroyTexture(textureWayve);
}

