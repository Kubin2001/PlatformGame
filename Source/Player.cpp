#include <iostream>
#include "SDL_mixer.h"
#include "Player.h"
#include "UI.h"
#include "Mobs.h"
#include "Colision.h"
#include "ParticlesManager.h"
#include "Camera.h"
#include "SoundManager.h"

extern int windowtype;
extern int localWindow;


Weapon::Weapon(int w, int h, int tempdamage, SDL_Texture* temptext) {
	GetRectangle()->w = w;
	GetRectangle()->h = h;
	damage = tempdamage;
	texture = temptext;
}

SDL_Rect* Weapon::GetRectangle() { return &rectangle; }

SDL_Texture* Weapon::GetTexture() { return texture; }

void Weapon::Move(SDL_Rect rect) {
	GetRectangle()->x = rect.x;
	GetRectangle()->y = rect.y;
}


int Weapon::GetAnimation() {
	return animation;
}
void Weapon::SetAnimation(int temp) {
	animation = temp;
}

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

int Player::getJumpBuffer() { return JumpBuffer; }

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

void Player::setattackBuffer(int value) { attackBuffer = value; }

int Player::getattackBuffer() { return attackBuffer; }


bool Player::GetDamage() {return damage;}

void Player::SetDamage(bool temp) {damage = temp;}


int Player::getDamageBuffer() {
	return damageBuffer;
}

void Player::setDamageBuffer(int value) {
	damageBuffer = value;
}
//Getters and setters
void Player::Render(SDL_Rect camRect) {
	SDL_Rect temp;
	temp.x = GetRectangle()->x - camRect.x;
	temp.y = GetRectangle()->y - camRect.y;
	temp.w = GetRectangle()->w;
	temp.h = GetRectangle()->h;

	if (damageBuffer % 10 == 0 && damageBuffer > 0) {

	}
	else
	{
		switch (animation)
		{
		case 1:
			SDL_RenderCopy(renderer, texture, NULL, &temp);
			break;
		case 2:
			SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
			SDL_RenderCopyEx(renderer, texture, NULL, &temp, 0.0, NULL, flip);
			break;
		}
	}
	if (weapon != nullptr) {
		SDL_Rect temp2;
		temp2.x = weapon->GetRectangle()->x - camRect.x;
		temp2.y = weapon->GetRectangle()->y - camRect.y;
		temp2.w = weapon->GetRectangle()->w;
		temp2.h = weapon->GetRectangle()->h;
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		switch (animation)
		{
		case 1:
			switch (weapon->GetAnimation())
			{
				case 1:
					SDL_RenderCopy(renderer, weapon->GetTexture(), NULL, &temp2);
					break;
				case 2:
					SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, &temp2, 30.0, NULL, SDL_FLIP_NONE);
					break;
			}
			
			break;
		case 2:
			switch (weapon->GetAnimation())
			{
			case 1:
				SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, &temp2, 0.0, NULL, flip);
				break;
			case 2:
				SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, &temp2, -30.0, NULL, flip);
				break;
			}
			
			break;
		}
	}
}

void Player::Move(const Uint8* state) {

	int speed = 4;
	if (state[SDL_SCANCODE_LEFT] && !getColison(0))
	{
		GetRectangle()->x -= speed;
		setanimation(2);
	}
	else if (state[SDL_SCANCODE_RIGHT] && !getColison(2))
	{
		GetRectangle()->x += speed;
		setanimation(1);
	}
}

void Player::Jump(const Uint8* state) {
	if (JumpBuffer <= 0 && getColison(1) && !getColison(3)) {
		if (state[SDL_SCANCODE_UP]) {
			JumpBuffer = 30;
			SoundManager::PlayPlayerJumpSound();
		}
	}
	else
	{
		JumpBuffer--;
		if (JumpBuffer < 0) {
			JumpBuffer = 0;
		}
	}
	if (!getColison(3)) {
		if (getJumpBuffer() > 6) {
			GetRectangle()->y -= 12;
		}
		else if (getJumpBuffer() > 3) {
			GetRectangle()->y -= 8;
		}
		else if (getJumpBuffer() > 0) {
			GetRectangle()->y -= 6;
		}
	}
	else
	{
		JumpBuffer = 0;
	}


	if (!getColison(1)) {
		GetRectangle()->y += 5;
	}
}


void Player::CheckDamage(UI * ui) {
	if (damage && damageBuffer < 0) {
		ui->RemoveHearths();
		damageBuffer = 100;
		if (ui->getHP().size() == 0) {
			SoundManager::PlayPlayerLoseSound();
			ui->CreateButtonInfo(550, 250, 300, 100, "YOU LOST", 30, 31);
			SDL_Delay(5000);
			localWindow = 1;
		}
		else
		{
			SoundManager::PlayPlayerHurtSound();
		}
	}
	damage = false;
	damageBuffer--;
}

void Player::SetWeapon(int w, int h, int tempdamage, SDL_Texture* temptext) {
	if (weapon == nullptr) {
		weapon = new Weapon(w, h, tempdamage, temptext);
	}
	else
	{
		delete weapon;
		weapon = new Weapon(w, h, tempdamage, temptext);
	}

	armed = true;
	
}

void Player::UpdateWeapon() {
	if (weapon != nullptr) {
		switch (animation)
		{
		case 1:
			weapon->GetRectangle()->x = GetRectangle()->x + (GetRectangle()->w - 10);
			weapon->GetRectangle()->y = (GetRectangle()->y + 30) - weapon->GetRectangle()->h;
			break;
		case 2:
			weapon->GetRectangle()->x = GetRectangle()->x - weapon->GetRectangle()->w + 10;
			weapon->GetRectangle()->y = (GetRectangle()->y + 30) - weapon->GetRectangle()->h;
			break;
		}
	}
}


void Player::Attack(const Uint8* state, ParticlesManager* particleManager) {
	if (armed) {
		if (attackBuffer <= 0) {
			if (state[SDL_SCANCODE_SPACE]) {
				SoundManager::PlayPlayerAttackSound();
				attackBuffer = 60;
				weapon->SetAnimation(2);
				SDL_Rect rect{ weapon->GetRectangle()->x ,GetRectangle()->y ,30,80 };
				if (animation == 1) {
					particleManager->CreatePlayerAttackParticles(rect, 1, 8, 40);
				}
				else
				{
					particleManager->CreatePlayerAttackParticles(rect, 2, -8, 40);
				}
			}
		}
		else
		{
			attackBuffer--;
			if (attackBuffer < 30) {
				weapon->SetAnimation(1);
			}
		}
	}
}


Player::~Player() {
	SDL_DestroyTexture(texture);

	if (weapon != nullptr) {
		delete weapon;
		weapon = nullptr;
	}
}