#include "SoundManager.h"


SoundManager::SoundManager(void)
{
	//load the wav files
	jump = Mix_LoadWAV("sfx/Jump.wav");
	background = Mix_LoadMUS("sfx/Background.wav");
	death = Mix_LoadWAV("sfx/Death.wav");
	menu = Mix_LoadWAV("sfx/MenuBeep");
}


SoundManager::~SoundManager(void)
{
	
}

void SoundManager::PlayJumpSound() 
{
	Mix_PlayChannel(-1, jump, 0);
}

void SoundManager::PlayBackground() 
{
	Mix_PlayMusic(background, -1);
}

void SoundManager::PlayDeathSound() 
{
	Mix_PlayChannel(-1, death, 0);
}

void SoundManager::PlayMenuSound() 
{
	Mix_PlayChannel(-1, menu, 0);
}

void SoundManager::PauseBackground(bool b)
{
	//Pauses or unpauses the background music based on bool fed in
	//true = pause music, false = resume music
	if (b == true)
	{
		Mix_PauseMusic();
	}
	else if (b == false)
	{
		Mix_ResumeMusic();
	}
}