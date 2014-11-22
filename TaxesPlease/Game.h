#include <SDL_image.h>
#include "Box2D\Box2D.h"


#pragma once
class Game
{
private:
	SDL_Renderer* mRenderer;
	b2World* mWorld;	

public:
	Game(SDL_Renderer* renderer, b2World* bworld);
	~Game(void);
	void update(double deltaTime);
};

