#include "BasicPlatform.h"
#include "Player.h"
#include "AnglePlatform.h"
#include "RevolutePlatforms.h"

#pragma once
class LevelManager
{
public:
	b2World * mWorld;
	SDL_Renderer * mRenderer;
	BasicPlatform * plat;
	AnglePlatform * angPlat;

	RevolutePlatforms * revol;
	Player * player;
	b2Vec2 Cam;
	LevelManager(b2World * world,SDL_Renderer * renderer);
	~LevelManager(void);
	void Update();
	void CreatePlatForms();
	void Draw();
};

