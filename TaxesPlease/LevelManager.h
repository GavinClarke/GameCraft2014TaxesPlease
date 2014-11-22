#include "BasicPlatform.h"
#include "Player.h"

#pragma once
class LevelManager
{
public:
	b2World * mWorld;
	SDL_Renderer * mRenderer;
	BasicPlatform * plat;
	Player * player;
	LevelManager(b2World * world,SDL_Renderer * renderer);
	~LevelManager(void);
	void Update();
	void CreatePlatForms();
	void Draw();
};

