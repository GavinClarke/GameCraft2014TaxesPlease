#include "SDL_dev\SDL2_mixer-2.0.0\include\SDL_mixer.h"
#pragma once

class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	void PlayJumpSound();
	void PlayBackground();
	void PlayDeathSound();
	void PlayMenuSound();
	void PauseBackground(bool);
private:
	Mix_Chunk* jump;
	Mix_Music* background;
	Mix_Chunk* death;
	Mix_Chunk* menu;

};

