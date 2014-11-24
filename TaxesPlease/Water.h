#ifndef WATER_H
#define WATER_H

#include "entity.h"
#include "KeyboardManager.h"

class Water {
public:
	Water(SDL_Renderer* renderer);

	void Draw();
	float getYPos();
private:
	entity * image;
};

#endif