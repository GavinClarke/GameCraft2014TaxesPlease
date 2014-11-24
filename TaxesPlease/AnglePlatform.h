#ifndef ANGLEPLATFORM_H
#define ANGLEPLATFORM_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class AnglePlatform {
public:
	AnglePlatform();
	AnglePlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~AnglePlatform ();
	b2Body* staticBody;
private:

	
	b2Vec2 mSize;
	SDL_Texture* m_texture;
};

#endif