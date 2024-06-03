#pragma once
#include <iostream>
#include <SDL.h>
#include "SDL_mixer.h"



class SoundManager
{
    private:
        //Player
        static Mix_Chunk* soundJump;
        static Mix_Chunk* soundAttack;
        static Mix_Chunk* soundHurt;
        static Mix_Chunk* soundLose;
        //Player
        //Mobs
        static Mix_Chunk* soundGrowl;
        static Mix_Chunk* soundDeath;
        static Mix_Chunk* soundPirateAttack;


    public:
        SoundManager();

        static void Load();

        static void PlayPlayerJumpSound();

        static void PlayPlayerAttackSound();

        static void PlayPlayerHurtSound();

        static void PlayPlayerLoseSound();

        static void PlayEnemyDeathSound();

        static void PlayWolfGrowlSound();

        static void PlayPirateAttackSound();

        static void UnLoad();

        ~SoundManager();
};
