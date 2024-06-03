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

void Player::setColison(bool value, int index) {
	if (index < 4) {
		colision[index] = value;
	}
	
}

bool Player::getColison(int index) {
	if (index < 4) {
		return colision[index];
	}

}


void Player::setanimation(int value) {
	animation = value;
}

int Player::getanimation() {
	return animation;
}

void Player::Render(SDL_Renderer* renderer) {

	switch (animation)
	{
	case 1:
		SDL_RenderCopy(renderer, texture, NULL, &rectangle);
		break;
	case 2:
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		SDL_RenderCopyEx(renderer, texture, NULL, &rectangle, 0.0, NULL, flip);
		break;
	}
}

void Player::Jump(const Uint8* state) {
	if (JumpBuffer <= 0 && getColison(1) == true) {
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
	if (GetRectangle()->y < 660 && colision[1] == 0 && JumpBuffer < 20) {
		GetRectangle()->y += 5;
		
	}
}