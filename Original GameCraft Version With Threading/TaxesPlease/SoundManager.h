#include "SDL_dev\SDL2_mixer-2.0.0\include\SDL_mixer.h"
#pragma once
//Sound manager class will play all sounds in the game
class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	void PlayJumpSound();//Plays the jump sound
	void PlayBackground();//Plays the background music
	void PlayDeathSound();//Plays the player death sound
	void PlayMenuSound();//Plays a button pressed sound
	void PauseBackground(bool);
private:
	Mix_Chunk* jump;//jump sound
	Mix_Music* background;//background music
	Mix_Chunk* death;//death sound
	Mix_Chunk* menu;//button press sound

};

