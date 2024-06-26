#include <iostream>
#include <SDL.h>
#include "ParticlesManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

ParticlesManager::ParticlesManager(SDL_Renderer * renderer) {
    this->renderer = renderer;
}

//Getteers and setters

SDL_Rect* Particle::GetRectangle() {
    return &rectangle;
}

SDL_Texture* Particle::GetTexture() {
    return texture;
}
void Particle::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

int Particle::GetDirection() {
    return direction;
}
void Particle::SetDirection(int temp) {
    direction = temp;
}

int Particle::GetSpeedX() {
    return speedX;
}
void Particle::SetSpeedX(int temp) {
    speedX = temp;
}

int Particle::GetSpeedY() {
    return speedY;
}
void Particle::SetSpeedY(int temp) {
    speedY = temp;
}

double Particle::GetAngle() {
    return angle;
}
void Particle::SetAngle(double temp) {
    angle = temp;
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

//Particles Functions
void Particle::Move() {
    GetRectangle()->x += speedX;
    GetRectangle()->y += speedY;
}
//

void ParticlesManager::LoadTextures() {
    std::string directory = "Textures/Particles";
    LoadMultipleTextures(Textures, directory, renderer);
}

void ParticlesManager::Render(SDL_Rect camRect) {
    SDL_Rect temp;
    for (int i = 0; i < PlayerParticles.size(); i++) {
        if (PlayerParticles[i].GetRenderable()) {
            temp.x = PlayerParticles[i].GetRectangle()->x - camRect.x;
            temp.y = PlayerParticles[i].GetRectangle()->y - camRect.y;
            temp.w = PlayerParticles[i].GetRectangle()->w;
            temp.h = PlayerParticles[i].GetRectangle()->h;
            switch (PlayerParticles[i].GetDirection()) {
            case 1:
                SDL_RenderCopyEx(renderer, PlayerParticles[i].GetTexture(), NULL, &temp, PlayerParticles[i].GetAngle(), NULL, SDL_FLIP_NONE);
                break;
            case 2:
                SDL_RenderCopyEx(renderer, PlayerParticles[i].GetTexture(), NULL, &temp, PlayerParticles[i].GetAngle(), NULL, SDL_FLIP_HORIZONTAL);
                break;
            }
        }
    }

    for (int i = 0; i < EnemyParticles.size(); i++) {
        if (EnemyParticles[i].GetRenderable()) {
            temp.x = EnemyParticles[i].GetRectangle()->x - camRect.x;
            temp.y = EnemyParticles[i].GetRectangle()->y - camRect.y;
            temp.w = EnemyParticles[i].GetRectangle()->w;
            temp.h = EnemyParticles[i].GetRectangle()->h;
            switch (EnemyParticles[i].GetDirection()) {
            case 1:
                SDL_RenderCopyEx(renderer, EnemyParticles[i].GetTexture(), NULL, &temp, EnemyParticles[i].GetAngle(), NULL, SDL_FLIP_NONE);
                break;
            case 2:
                SDL_RenderCopyEx(renderer, EnemyParticles[i].GetTexture(), NULL, &temp, EnemyParticles[i].GetAngle(), NULL, SDL_FLIP_HORIZONTAL);
                break;
            }
        }
    }
}

void ParticlesManager::CreatePlayerParticle(SDL_Rect rect, int direction, int speedX, int speedY, int lifeTime, std::string textureName, double angle) {
    PlayerParticle temp(rect,direction,speedX,speedY,lifeTime,angle);
    for (auto& it : Textures) {
        if (textureName == it.GetName()) {
            temp.SetTexture(it.GetTexture());
        }
    }
    PlayerParticles.push_back(temp);
}

void ParticlesManager::CreateEnemyParticle(SDL_Rect rect, int direction, int speedX, int speedY, int lifeTime, std::string textureName, double angle) {
    EnemyParticle temp(rect,direction,speedX,speedY,lifeTime,angle);
    for (auto& it : Textures) {
        if (textureName == it.GetName()) {
            temp.SetTexture(it.GetTexture());
        }
    }
    EnemyParticles.push_back(temp);
}

void ParticlesManager::CheckColision(Mobs* mobs, Player* player, SDL_Rect camRect) {
    CheckColisionMobs(mobs, camRect);
    CheckColisionPlayer(player, camRect);
}

void ParticlesManager::CheckColisionMobs(Mobs* mobs,SDL_Rect camRect) {
    for (int i = 0; i < PlayerParticles.size(); i++)
    {
        if (SimpleCollision(camRect, *PlayerParticles[i].GetRectangle())) {
            PlayerParticles[i].SetRenderable(true);
            for (int j = 0; j < mobs->getEnemies().size(); j++)
            {
                if (mobs->getEnemies()[j]->getInvTime() < 1) {
                    if (SimpleCollision(*PlayerParticles[i].GetRectangle(), *mobs->getEnemies()[j]->GetRectangle())) {
                        mobs->getEnemies()[j]->setHitPoints(mobs->getEnemies()[j]->getHitPoints() - 10);
                        mobs->getEnemies()[j]->setInvTime(20);
                        mobs->getEnemies()[j]->MakeAgressive();
                        PlayerParticles[i].SetLifeTime(0);
                    }
                }
            }
        }
        else
        {
            PlayerParticles[i].SetRenderable(false);
        }
    }
}

void ParticlesManager::CheckColisionPlayer(Player * player, SDL_Rect camRect) {
    for (int i = 0; i < EnemyParticles.size(); i++)
    {
        if (SimpleCollision(camRect, *EnemyParticles[i].GetRectangle())) {
            EnemyParticles[i].SetRenderable(true);
            if (SimpleCollision(*EnemyParticles[i].GetRectangle(), *player->GetRectangle())) {
                player->SetDamage(true);
            }
        }
        else
        {
            EnemyParticles[i].SetRenderable(false);
        }
    }
}

void ParticlesManager::EndLifeTime() {
    for (int i = 0; i < PlayerParticles.size(); i++) {
        PlayerParticles[i].SetLifeTime(PlayerParticles[i].GetLifeTime()- 1);
        if (PlayerParticles[i].GetLifeTime() < 1) {
            PlayerParticles.erase(PlayerParticles.begin() + i);
        }
    }
    for (int i = 0; i < EnemyParticles.size(); i++) {
        EnemyParticles[i].SetLifeTime(EnemyParticles[i].GetLifeTime() - 1);
        if (EnemyParticles[i].GetLifeTime() < 1) {
            EnemyParticles.erase(EnemyParticles.begin() + i);
        }
    }
}

void ParticlesManager::MoveParticles(const Uint8* state, Player* player) {
    MoveParticlesPlayer(state, player);
    MoveParticlesEnemy(state, player);
}

void ParticlesManager::MoveParticlesPlayer(const Uint8* state, Player* player) {
    if (PlayerParticles.empty()) {
        return;
    }
    for (auto &particle: PlayerParticles)
    {
        particle.Move();
    }
}

void ParticlesManager::MoveParticlesEnemy(const Uint8* state, Player* player) {
    if (EnemyParticles.empty()) {
        return;
    }
    for (int i = 0; i < EnemyParticles.size(); i++)
    {
        EnemyParticles[i].Move();
    }
}



ParticlesManager::~ParticlesManager() {
    for (auto &it:Textures)
    {
        SDL_DestroyTexture(it.GetTexture());
    }

}

