#include "BasicPlatform.h"
#include "Player.h"
#include "AnglePlatform.h"
#include "RevolutePlatforms.h"
#include "entity.h"
#include <SDL_thread.h>

#pragma once
class LevelManager
{
public:
	b2World * mWorld;
	SDL_Renderer * mRenderer;
	BasicPlatform * plat;
	entity * platEntity;
	BasicPlatform * plat2;
	entity * plat2Entity;
	BasicPlatform * plat3;
	entity * plat3Entity;
	AnglePlatform * angPlat;
	entity * angEntity;
	entity * water;
	SDL_Rect rect;
	b2Vec2 position;
	RevolutePlatforms * revol;
	Player * player;
	b2Vec2 Cam;
	SDL_Thread *thread;
	int * ticket;
	LevelManager(b2World * world,SDL_Renderer * renderer);
	~LevelManager(void);
	void CollisionWithWater();
	void Update();
	void CreateObjects();
	void CreatePlatForms();
	void Draw();
};

