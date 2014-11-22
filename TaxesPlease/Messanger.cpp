#include "Messanger.h"


Messanger::Messanger(void)
{
	SDL_Rect temptextLocation = {100, 100, 0, 0 };
	textLocation = temptextLocation;
	TTF_Init();
   // Set the video mode
	font = TTF_OpenFont("calibri.ttf", 12);
	SDL_Color tempCol1 = { 255, 255, 255 };
	foregroundColor = tempCol1;
	SDL_Color tempCol2 =  { 0, 0, 255 };
	backgroundColor = tempCol2;
	textSurface = TTF_RenderText_Shaded(font, ".", foregroundColor, backgroundColor);
}

Messanger::~Messanger(void)
{
}

void Messanger::render(SDL_Surface* screen){
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
}

void Messanger::exit(){// call before exiting prograam
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}

void Messanger::setPosition(float x, float y){//set the position of the text
	SDL_Rect temptextLocation = {x, y, 0, 0 };
	textLocation = temptextLocation;
}

void Messanger::setText(std::String message){//change the message
	textSurface = TTF_RenderText_Shaded(font, message, foregroundColor, backgroundColor);
}