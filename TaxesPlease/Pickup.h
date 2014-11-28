#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include "Box2D/Box2D.h"
class Pickup
{
public:
	Pickup(void);
	~Pickup(void);
	Pickup(b2World*, b2Vec2, SDL_Renderer*);
	void InitPickup(b2World*, b2Vec2, SDL_Renderer*);
	int Run(void*);
	b2Body* GetBody();
	void SetAlive(bool isAlive);
	void Draw(SDL_Renderer* gRenderer);

private:
	b2BodyDef m_bodyDef;
	b2Body* m_dynamicBody;
	b2PolygonShape m_pickupShape;
	b2Fixture* m_fix;
	b2FixtureDef m_fixtureDef;
	SDL_Texture * m_texture;
	SDL_Rect m_rect;
	b2Vec2 m_pos;
	bool m_alive;
};

