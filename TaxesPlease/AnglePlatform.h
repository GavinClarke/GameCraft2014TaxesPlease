#ifndef ANGLEPLATFORM_H
#define ANGLEPLATFORM_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"
#include <SDL_image.h>
#include <SDL.h>

class AnglePlatform {
public:
	AnglePlatform();
	AnglePlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~AnglePlatform ();
private:

	b2Body* staticBody;
<<<<<<< HEAD
	b2Vec2 mSize;
	SDL_Texture* m_texture;
=======
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	SDL_Texture * m_texture;
	SDL_Rect rect;
>>>>>>> c72104e0011bbe600c3c24110b3795a2e7fad7f7
};

#endif