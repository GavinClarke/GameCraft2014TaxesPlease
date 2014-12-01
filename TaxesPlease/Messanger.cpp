#include "Messanger.h"


Messanger::Messanger(int ID, float x, float y, float width, float height, SDL_Renderer* renderer, std::string* messagePoint, int* passCounter): m_id(ID), m_renderer(renderer), m_messagePoint(messagePoint), externalPassCounter(passCounter)
{
	internalPassCounter = 0;
	m_font = TTF_OpenFont("calibri.ttf", 24); //this opens a font style and sets a size

	SDL_Color temp = {255, 0, 0};
	m_textColour = temp;  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	setPosition(x,y);
	Message_rect.w = width; // controls the width of the rect
	Message_rect.h = height; // controls the height of the rect

	unlock();

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
}


void Messanger::run(){
	while(true){
		//int i = 0;
		
			setText(*m_messagePoint);
			V();
	}
}

Messanger::~Messanger(void)
{
}

void Messanger::render(){
	SDL_RenderCopy(m_renderer, MessageText, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}

void Messanger::setPosition(float x, float y){//set the position of the text
	Message_rect.x = x;
	Message_rect.y = y;
}

void Messanger::setText(std::string message){//change the message
	surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), m_textColour); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	MessageText = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage); //now you can convert it into a texture
}

void Messanger::P(){
	render();
	internalPassCounter = *externalPassCounter;
}

bool Messanger::V(){
	if(internalPassCounter < *externalPassCounter){
		unlock();
		P();
		return true;
	}
	else{
		if(!locked){
			lock();
		}
		return false;
	}
}

void Messanger::lock(){
	locked = true;
}

void Messanger::unlock(){
	locked = false;
}