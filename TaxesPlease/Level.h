#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SDL.h>
#include "CONSTANTS.h"
#include <Box2D\Box2D.h>
#include "Player.h"
#include <vector>

class Level{
public:
	Level();
	Level(int, b2World*, SDL_Renderer*);
	virtual ~Level() = 0;
	virtual void Update(Player*) = 0;
	virtual void Render(SDL_Renderer*,b2Vec2) = 0;
};

#endif