#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class EntityMangager
{
public:
	const int max = 4;
	static int ticket [max];
	EntityMangager(void);
	
	~EntityMangager(void);
	void CreateEntity(SDL_Texture * mTexture, std::string name, SDL_Rect sizeRect, SDL_Rect imageSourceRect,float rotation);
	void SetEntitiesRect(SDL_Rect value);
	void Draw(int i);
	void CheckDraw();
	void Lock(int pid);
	void Unlock(int pid);
	int getMax(int * ticketA);
};

