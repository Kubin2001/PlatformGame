#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>   
#include "Mobs.h"
#include "Player.h"

class Mobs;

class Player;

class Particle {
    protected:
        SDL_Rect rectangle;
        int direction = 1;
        int speed = 0;
        int lifeTime = 0;
        bool renderable = false;
    public:
        SDL_Rect* GetRectangle();
        int GetDirection();
        void SetDirection(int temp);
        int GetSpeed();
        void SetSpeed(int temp);
        int GetLifeTime();
        void SetLifeTime(int temp);

        bool GetRenderable();

        void SetRenderable(bool temp);

};

class EnemyAttackParticle : public Particle {
    public:
        EnemyAttackParticle(SDL_Rect rect, int direction, int speed, int lifeTime) {
            this->direction = direction;
            this->speed = speed;
            this->lifeTime = lifeTime;
            this->rectangle = rect;
        }
};


class PlayerAttackParticle : public Particle {
    public:
        PlayerAttackParticle(SDL_Rect rect, int direction, int speed, int lifeTime) {
            this->direction = direction;
            this->speed = speed;
            this->lifeTime = lifeTime;
            this->rectangle = rect;
        }
};

class ParticlesManager
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture * textureWayve = nullptr;
        std::vector<PlayerAttackParticle> PlayerAttackParticles;
        std::vector<EnemyAttackParticle> EnemyAttackParticles;

    public:
        ParticlesManager(SDL_Renderer* renderer);

        SDL_Texture *GetTexture();

        void SetTexture(SDL_Texture* temptex);

        void Render(SDL_Rect camRect);

        void CreatePlayerAttackParticles(SDL_Rect rect, int direction, int speed, int lifeTime);

        void CreateEnemyAttackParticles(SDL_Rect rect, int direction, int speed, int lifeTime);

        void CheckColision(Mobs* mobs,Player* player, SDL_Rect camRect);

        void CheckColisionMobs(Mobs * mobs, SDL_Rect camRect);

        void CheckColisionPlayer(Player* player, SDL_Rect camRect);

        void EndLifeTime();

        void MoveParticles(const Uint8* state, Player* player);

        void MoveParticlesPlayer(const Uint8* state, Player* player);

        void MoveParticlesEnemy(const Uint8* state, Player* player);

        ~ParticlesManager();
};
