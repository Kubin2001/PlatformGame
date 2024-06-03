#include <iostream>
#include "Player.h"
#include "UI.h"
#include "Mobs.h"
#include "Colision.h"

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

int AttackParticle::GetAnimation() {
	return animation;
}
void AttackParticle::SetAnimation(int temp) {
	animation = temp;
}

SDL_Rect* AttackParticle::GetRectangle() { return &rectangle; }

Player::Player(SDL_Renderer* renderer) {
	this->renderer = renderer;
}
//Getters and setters
SDL_Texture* Player::GetTexture() {
	return texture;
}

void Player::SetTexture(SDL_Texture* temptex) {texture = temptex;}

SDL_Texture* Player::GetTextureAttackParticle() {
	return textureAttackParticle;
}

void Player::SetTextureAttackParticle(SDL_Texture* temptex) { textureAttackParticle = temptex; }

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
	if (weapon != nullptr) {
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
		switch (animation)
		{
		case 1:
			switch (weapon->GetAnimation())
			{
				case 1:
					SDL_RenderCopy(renderer, weapon->GetTexture(), NULL, weapon->GetRectangle());
					break;
				case 2:
					SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, weapon->GetRectangle(), 30.0, NULL, SDL_FLIP_NONE);
					break;
			}
			if (attackBuffer > 0) {
				if (weapon->attackParticle.direction == 1) {
					SDL_RenderCopy(renderer, textureAttackParticle, NULL, weapon->attackParticle.GetRectangle());
				}
				else
				{
					SDL_RenderCopyEx(renderer, textureAttackParticle, NULL, weapon->attackParticle.GetRectangle(), 0.0, NULL, flip);
				}
			}
			break;
		case 2:
			switch (weapon->GetAnimation())
			{
			case 1:
				SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, weapon->GetRectangle(), 0.0, NULL, flip);
				break;
			case 2:
				SDL_RenderCopyEx(renderer, weapon->GetTexture(), NULL, weapon->GetRectangle(), -30.0, NULL, flip);
				break;
			}
			if (attackBuffer > 0) {
				if (weapon->attackParticle.direction == 1) {
					SDL_RenderCopy(renderer, textureAttackParticle, NULL, weapon->attackParticle.GetRectangle());
				}
				else
				{
					SDL_RenderCopyEx(renderer, textureAttackParticle, NULL, weapon->attackParticle.GetRectangle(), 0.0, NULL, flip);
				}
			}
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
			localWindow = 1;
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
			weapon->GetRectangle()->x = GetRectangle()->x + GetRectangle()->w * 0.7;
			weapon->GetRectangle()->y = GetRectangle()->y + GetRectangle()->h * 0.2;
			break;
		case 2:
			weapon->GetRectangle()->x = GetRectangle()->x - 10;
			weapon->GetRectangle()->y = GetRectangle()->y + GetRectangle()->h * 0.2;
			break;
		}
	}
}


void Player::Attack(const Uint8* state, Mobs* mobs) {
	if (armed) {
		if (attackBuffer <= 0) {
			if (state[SDL_SCANCODE_SPACE]) {
				attackBuffer = 60;
				weapon->SetAnimation(2);
				weapon->attackParticle.GetRectangle()->x = weapon->GetRectangle()->x;
				weapon->attackParticle.GetRectangle()->y = GetRectangle()->y;
				weapon->attackParticle.GetRectangle()->w = 30;
				weapon->attackParticle.GetRectangle()->h = 80;
				if (animation == 1) {
					weapon->attackParticle.direction = 1;
				}
				else
				{
					weapon->attackParticle.direction = 2;
				}

			}
		}
		else
		{
			attackBuffer--;
			if (attackBuffer < 30) {
				weapon->SetAnimation(1);
			}
			for (int i = 0; i < mobs->getEnemies().size(); i++)
			{
				if (mobs->getEnemies()[i]->getInvTime() < 1) {
					if (SimpleCollision(*weapon->attackParticle.GetRectangle(), *mobs->getEnemies()[i]->GetRectangle()) == 1) {
						mobs->getEnemies()[i]->setHitPoints(mobs->getEnemies()[i]->getHitPoints() - 10);
						mobs->getEnemies()[i]->setInvTime(20);
						if (mobs->getEnemies()[i]->getHitPoints() < 1) {
							mobs->getEnemies().erase(mobs->getEnemies().begin() + i);
						}
					}
				}
				
			}
			if (weapon->attackParticle.direction == 1) {
				weapon->attackParticle.GetRectangle()->x += 8;
			}
			else
			{
				weapon->attackParticle.GetRectangle()->x -= 8;
			}
			if (attackBuffer == 0) {
				weapon->attackParticle.GetRectangle()->w = -2;
				weapon->attackParticle.GetRectangle()->h = -2;
			}

			if (!getColison(1) && JumpBuffer < 20) {//Góra
				weapon->attackParticle.GetRectangle()->y -=5;
			}
			else if (!getColison(3) && JumpBuffer > 25) {//Dó³
				weapon->attackParticle.GetRectangle()->y += 5;
			}
		}
	}
}

Player::~Player() {
	SDL_DestroyTexture(texture);
	if (weapon != nullptr) {
		delete weapon;
	}
}