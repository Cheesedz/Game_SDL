#include "SoundEffect.h"

Sound::Sound()
{
	gMusic = Mix_LoadMUS("sound effect/");
	gFire = Mix_LoadWAV("sound effect/fire.wav");
	gOption = Mix_LoadWAV("sound effect/opt.wav");
	gExplosion = Mix_LoadWAV("sound effect/boom.wav");
	gHurt = Mix_LoadWAV("sound effect/boom.wav");
	gRing = Mix_LoadWAV("sound effect/get_energy.wav");
	gWin = Mix_LoadWAV("sound effect/win.wav");
	gLose = Mix_LoadWAV("sound effect/lose.wav");
}

void Sound::FreeSound()
{
    //Free the sound effects
    Mix_FreeChunk(gFire);
    Mix_FreeChunk(gWin);
    Mix_FreeChunk(gLose);
    Mix_FreeChunk(gHurt);
    Mix_FreeChunk(gOption);
    Mix_FreeChunk(gRing);
    Mix_FreeChunk(gExplosion);
    
	gFire = NULL;
	gOption = NULL;
	gExplosion = NULL;
	gHurt = NULL;
	gRing = NULL;
	gWin = NULL;
	gLose = NULL;

    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
}