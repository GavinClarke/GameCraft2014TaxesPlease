#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "Constants.h"

class Menu
{
public:
	SDL_Texture * Play;
	SDL_Texture * Quit;

	SDL_Rect playRect;
	SDL_Rect QuitRect;

	SDL_Renderer * mRenderer;

	Menu(SDL_Renderer * renderer);
	~Menu(void);
	int Update();
	void LoadImage();
	bool MouseClick(SDL_Rect rect);
	void Draw();
};

