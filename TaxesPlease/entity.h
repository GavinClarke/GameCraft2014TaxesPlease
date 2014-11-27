#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class entity
{
private:
	SDL_Texture * mTexture;
	std::string name;
	SDL_Rect sizeRect;
	SDL_Rect imageSourceRect;
	SDL_Renderer * mRenderer;
	float rotation;
	int m_id;
	int MAX;
	/*public synchronized int  FA( int value)
	{
		 
		int temp = this.number;
		this.number = this.number + value;
		
		return temp;
			
	}*/
public:
	entity(SDL_Renderer * renderer, int i,int * tickets);
	~entity();

	int * ticket;
	void LoadImage();
	
	void Draw();
	void setTextureName(std::string value);
	void setSizeRect(float x, float y, float h, float w);
	void setImageSourceRect(float x, float y, float h, float w);
	void setRotation(float value);
	void Lock(int pid);
	void Unlock(int pid);
	int getMax(int * ticketA);
	int CallDraw();
};

