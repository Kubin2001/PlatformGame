#pragma once
#include <SDL.h>

class Player {
private:
	SDL_Texture* texture = nullptr;
	SDL_Rect rectangle{ 620,660,50,100 };
	int JumpBuffer = 0;
	bool colision[4] = { 0,0,0,0 };
	int animation = 1;
public:
	SDL_Texture* GetTexture();

	void setJumpBuffer(int temp);

	void setColison(bool value,int index);

	bool getColison(int index);

	void setanimation(int value);

	int getanimation();

	void SetTexture(SDL_Texture* temptex);

	SDL_Rect* GetRectangle();

	void Render(SDL_Renderer* renderer);

	void Jump(const Uint8* state);

};