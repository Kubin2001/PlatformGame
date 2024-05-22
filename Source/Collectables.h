#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Player.h"


class Pickable {
    protected:
        SDL_Rect rectangle;
        bool renderable = false;
        SDL_Texture* texture;

    public:
        virtual SDL_Rect* GetRectangle();
        virtual bool GetRenderable();
        virtual void SetRenderable(bool temp);
        SDL_Texture* GetTexture();
        void SetTexture(SDL_Texture* temptex);
};

class Point : public Pickable {
    private:
        int value = 10;
    public:
        Point() {}
};



class CollectableWeapon {
    protected:
        SDL_Rect rectangle;
        int damage = 10;
        bool renderable = false;

    public:
        virtual SDL_Rect* GetRectangle();
        virtual bool GetRenderable();
        virtual void SetRenderable(bool temp);
};

class ShortSword : public CollectableWeapon {
    public:
        ShortSword() {damage = 10;}
};


class Collectables
{
    private:
        SDL_Texture *textureShortSword = nullptr;
        SDL_Texture *textureCoin = nullptr;

        SDL_Renderer *renderer = nullptr;
        std::vector<CollectableWeapon*> Weapons;
        std::vector<Pickable*> Pickables;

    public:
        Collectables(SDL_Renderer *renderer);

        SDL_Texture *GetTextureShortSword();
        void SetTextureShortSword(SDL_Texture* temptex);
        SDL_Texture* GetTextureCoin();
        void SetTextureCoin(SDL_Texture* temptex);

        void LoadEquipment();
        void DetectCollison(UI* ui, Player* player, SDL_Rect camRect);

        void Render(SDL_Rect camRect);
        void RenderCollectableWeapon(SDL_Rect camRect);
        void RenderPickables(SDL_Rect camRect);

        ~Collectables();
};
