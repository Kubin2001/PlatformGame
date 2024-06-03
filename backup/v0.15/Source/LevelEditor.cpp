#include <iostream>
#include <SDL.h>
#include "LevelEditor.h"

extern SDL_Texture* load(const char* file, SDL_Renderer* ren);

LevelEditor::LevelEditor(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void LevelEditor::LoadTextures() {
    texturesUI.push_back(load("Textures/Interface/button.png", renderer));
    texturesUI.push_back(load("Textures/Interface/font.png", renderer));

    texturePlayer = load("Textures/Interface/font.png", renderer);

    texturesMap.push_back(load("Textures/Terrain/grass.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/platform.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/pillar.png", renderer));
    texturesMap.push_back(load("Textures/Terrain/flag.png", renderer));

    texturesMobs.push_back(load("Textures/Mobs/charger.png", renderer));
    texturesMobs.push_back(load("Textures/Mobs/wolf.png", renderer));

    texturesEquipment.push_back(load("Textures/Equipment/shortSword.png", renderer));
}

void LevelEditor::Render() {

}

LevelEditor::~LevelEditor() {
}
