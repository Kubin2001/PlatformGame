#include <iostream>
#include "Player.h"
#include "UI.h"

extern int windowtype;

Player::Player(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
//Getters and setters
SDL_Texture* Player::GetTexture() {
	return texture;
}

void Player::SetTexture(SDL_Texture* temptex) {texture = temptex;}

SDL_Rect* Player::GetRectangle() {return &rectangle;}

void Player::setJumpBuffer(int temp) {JumpBuffer = temp;}

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

void Player::setanimation(int value) {animation = value;}

int Player::getanimation() {return animation;}


bool Player::GetDamage() {return damage;}

void Player::SetDamage(bool temp) {damage = temp;}
//Getters and setters
void Player::Render() {
	if (damageBuffer % 10 == 0 && damageBuffer > 0) {

	}
	else
	{
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
	
}

void Player::Jump(const Uint8* state) {
	if (JumpBuffer <= 0 && getColison(1) == true) {
		if (state[SDL_SCANCODE_UP]) {
			JumpBuffer += 60;
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
	if (JumpBuffer < 0) {
		JumpBuffer = 0;
	}
}


void Player::CheckDamage(UI * ui) {
	if (damage == true && damageBuffer < 0) {
		ui->RemoveHearths();
		damageBuffer = 200;
		if (ui->getHP().size() == 0) {
			ui->CreateButtonInfo(550, 250, 300, 100, "YOU LOST", 30, 31);
			SDL_Delay(5000);
			windowtype = 1;
		}
	}
	damage = false;
	damageBuffer--;
}


Player::~Player() {
	SDL_DestroyTexture(texture);
}