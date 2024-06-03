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
        static Mix_Chunk* soundWin;
        //Player
        //Mobs
        static Mix_Chunk* soundGrowl;
        static Mix_Chunk* soundDeath;
        static Mix_Chunk* soundPirateAttack;
        static Mix_Chunk* soundArrowShoot;
        //Mobs
        //Collectables
        static Mix_Chunk* soundCoin;
        static Mix_Chunk* soundMedKit;
        //Collectables

    public:
        SoundManager();

        static void LoadMenu();

        static void LoadGame();

        static void LoadEditor();

        static void PlayPlayerJumpSound();

        static void PlayPlayerAttackSound();

        static void PlayPlayerHurtSound();

        static void PlayPlayerLoseSound();

        static void PlayPlayerWinSound();

        static void PlayEnemyDeathSound();

        static void PlayWolfGrowlSound();

        static void PlayPirateAttackSound();

        static void PlayArrowShootSound();

        static void PlayCoinSound();

        static void PlayMedKitSound();

        static void UnLoadMenu();

        static void UnLoadGame();

        static void UnLoadEditor();

        ~SoundManager();
};
