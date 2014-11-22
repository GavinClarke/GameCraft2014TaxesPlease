#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Messanger
{
public:
	Messanger(void);
	~Messanger(void);
	void render(SDL_Surface* screen);
	void exit();
	void setPosition(float x, float y);
	void setText(std::String message);
private:
	SDL_Surface* textSurface;
	TTF_Font* font;
	SDL_Rect textLocation;
	std::String text;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;
};

