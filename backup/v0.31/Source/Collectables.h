#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Player.h"
#include "TextureManager.h"


class Pickable {
    protected:
        SDL_Rect rectangle;
        bool renderable = false;
        SDL_Texture* texture;

    public:
        virtual SDL_Rect* GetRectangle();
        virtual bool GetRenderable();
        virtual void SetRenderable(bool temp);
        virtual SDL_Texture* GetTexture();
        virtual void SetTexture(SDL_Texture* temptex);

        virtual bool CollisionPlayer(Player* player, UI* ui) = 0;
};

class Point : public Pickable {
    private:
        int value = 10;
    public:
        Point() {}

        bool CollisionPlayer(Player * player, UI * ui)override;
};

class MedKit : public Pickable {
    public:
        MedKit() {}

        bool CollisionPlayer(Player* player, UI* ui)override;

};



class CollectableWeapon {
    protected:
        SDL_Rect rectangle;
        int damage = 10;
        bool renderable = false;
        SDL_Texture* texture;

    public:
        virtual SDL_Rect* GetRectangle();
        virtual bool GetRenderable();
        virtual void SetRenderable(bool temp);
        virtual SDL_Texture* GetTexture();
        virtual void SetTexture(SDL_Texture* temptex);
};

class ShortSword : public CollectableWeapon {
    public:
        ShortSword() {damage = 10;}
};


class Collectables
{
    private:
        SDL_Renderer *renderer = nullptr;
        std::vector<CollectableWeapon*> Weapons;
        std::vector<Pickable*> Pickables;

        std::vector<Texture> Textures;

    public:
        Collectables(SDL_Renderer *renderer);

        std::vector<Texture>& getTextures();

        void LoadTextures();
        void LoadEquipment();
        void DetectCollison(UI* ui, Player* player, SDL_Rect camRect);

        void Render(SDL_Rect camRect);
        void RenderCollectableWeapon(SDL_Rect camRect);
        void RenderPickables(SDL_Rect camRect);

        ~Collectables();
};
