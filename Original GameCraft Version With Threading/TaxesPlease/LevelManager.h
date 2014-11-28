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
	BasicPlatform * plat2;
	BasicPlatform * plat3;
	AnglePlatform * angPlat;
	SDL_Texture * water;
	SDL_Rect rect;
	b2Vec2 position;
	RevolutePlatforms * revol;
	Player * player;
	b2Vec2 Cam;
	LevelManager(b2World * world,SDL_Renderer * renderer);
	~LevelManager(void);
	void CollisionWithWater();
	void Update();
	void CreatePlatForms();
	void Draw();
};

