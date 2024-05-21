#include <iostream>
#include <SDL.h>
#include "SoundManager.h"
#include "SDL_mixer.h"

extern int windowtype;

Mix_Chunk* SoundManager::soundJump = nullptr;
Mix_Chunk* SoundManager::soundAttack = nullptr;
Mix_Chunk* SoundManager::soundHurt = nullptr;
Mix_Chunk* SoundManager::soundLose = nullptr;
Mix_Chunk* SoundManager::soundWin = nullptr;


Mix_Chunk* SoundManager::soundGrowl = nullptr;
Mix_Chunk* SoundManager::soundDeath = nullptr;
Mix_Chunk* SoundManager::soundPirateAttack = nullptr;

SoundManager::SoundManager() {
}

void SoundManager::LoadMenu() {

}

void SoundManager::LoadGame() {
	//Player
	soundJump = Mix_LoadWAV("Sounds/Player/jump.wav");
	soundAttack = Mix_LoadWAV("Sounds/Player/attack.wav");
	soundHurt = Mix_LoadWAV("Sounds/Player/hurt.wav");
	soundLose = Mix_LoadWAV("Sounds/Player/lose.wav");
	soundWin = Mix_LoadWAV("Sounds/Player/win.wav");
	//Player
	//Mobs
	soundGrowl = Mix_LoadWAV("Sounds/Mobs/wolfGrowl.wav");
	soundDeath = Mix_LoadWAV("Sounds/Mobs/mobDeath.wav");
	soundPirateAttack = Mix_LoadWAV("Sounds/Mobs/pirateAttack.wav");
	//Mobs
}

void SoundManager::LoadEditor() {

}


void SoundManager::PlayPlayerJumpSound() {
	Mix_PlayChannel(-1, soundJump, 0);
}

void SoundManager::PlayPlayerAttackSound() {
	Mix_PlayChannel(-1, soundAttack, 0);
}

void SoundManager::PlayPlayerHurtSound() {
	Mix_PlayChannel(-1, soundHurt, 0);
}

void SoundManager::PlayPlayerLoseSound() {
	Mix_PlayChannel(-1, soundLose, 0);
}


void SoundManager::PlayPlayerWinSound() {
	Mix_PlayChannel(-1, soundWin, 0);
}


void SoundManager::PlayEnemyDeathSound() {
	Mix_PlayChannel(-1, soundDeath, 0);
}

void SoundManager::PlayWolfGrowlSound() {
	Mix_PlayChannel(-1, soundGrowl, 0);
}

void SoundManager::PlayPirateAttackSound() {
	Mix_PlayChannel(-1, soundPirateAttack, 0);
}

void SoundManager::UnLoadMenu() {

}

void SoundManager::UnLoadGame() {
	Mix_FreeChunk(soundDeath);
	soundDeath = nullptr;
	Mix_FreeChunk(soundGrowl);
	soundGrowl = nullptr;
	Mix_FreeChunk(soundJump);
	soundJump = nullptr;
	Mix_FreeChunk(soundAttack);
	soundAttack = nullptr;
	Mix_FreeChunk(soundHurt);
	soundHurt = nullptr;
	Mix_FreeChunk(soundLose);
	soundLose = nullptr;
	Mix_FreeChunk(soundPirateAttack);
	soundPirateAttack = nullptr;
	Mix_FreeChunk(soundWin);
	soundWin = nullptr;
}

void SoundManager::UnLoadEditor() {

}

SoundManager::~SoundManager() {
}

