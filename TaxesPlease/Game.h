#include <SDL_image.h>
#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "Menu.h"
#include "Constants.h"
#include "LevelManager.h"
#pragma once

class Game
{
private:
	SDL_Renderer* mRenderer;
	b2World* mWorld;	
	Menu * menu;
	Constants * c;
	bool runGame;
	LevelManager * level;

public:
	Game(SDL_Renderer* renderer, b2World* bworld,Constants * con);
	~Game(void);
	void update(double deltaTime);
};

