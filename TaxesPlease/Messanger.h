#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <chrono>
#include <thread>

class Messanger
{
public:
	Messanger(int ID, float x, float y, float width, float height, SDL_Renderer* renderer, std::string* messagePoint, int* passCounter);
	~Messanger(void);
	void run();
	int m_id;
private:
	TTF_Font* m_font;
	SDL_Color m_textColour;
	SDL_Surface* surfaceMessage;
	SDL_Texture* MessageText;
	SDL_Rect Message_rect; //create a rect
	SDL_Renderer* m_renderer;
	void render();
	void setPosition(float x, float y);
	void setText(std::string message);
	bool renderSurfaceOpen;
	std::string* m_messagePoint;
	void P();
	bool V();
	int* externalPassCounter;
	int internalPassCounter;	
	bool locked;
	void lock();
	void unlock();
};

