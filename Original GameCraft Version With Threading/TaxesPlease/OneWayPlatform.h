#ifndef ONEWAYPLATFORM_H
#define ONEWAYPLATFORM_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class OneWayPlatform {
public:
	OneWayPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	~OneWayPlatform();
	b2Fixture* GetFixture();
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	void CanCollideWithPlayer(bool toggle);
	b2Vec2 GetPosition();
private:

	b2Body* staticBody;
	b2Vec2 mSize;
	SDL_Texture *m_texture;
};

#endif