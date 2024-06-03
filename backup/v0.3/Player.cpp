#include <iostream>
#include "Player.h"
#include "Map.h"

SDL_Texture* Player::GetTexture() {
	return texture;
}

void Player::SetTexture(SDL_Texture* temptex) {
	texture = temptex;
}

SDL_Rect* Player::GetRectangle() {
	return &rectangle;
}


void Player::setJumpBuffer(int temp) {
	JumpBuffer = temp;
}

void Player::setColison(bool temp) {
	Colison = temp;
}

void Player::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}

void Player::Jump(const Uint8* state) {
	if (JumpBuffer <= 0) {
		if (state[SDL_SCANCODE_UP]) {
			JumpBuffer += 50;
		}
	}
	else
	{
		JumpBuffer--;
		if (JumpBuffer < 20) {}
		else {GetRectangle()->y -= 5;}
	}
	if (GetRectangle()->y < 660 && Colison == 0 && JumpBuffer < 20) {
		GetRectangle()->y += 5;
	}
}