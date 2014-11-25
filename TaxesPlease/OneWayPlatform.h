#ifndef ONEWAYPLATFORM_H
#define ONEWAYPLATFORM_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class OneWayPlatform {
public:
	OneWayPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float angleRadians);
	~OneWayPlatform();
	b2Fixture* GetFixture();
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	void CanCollideWithPlayer(bool toggle);
	b2Vec2 GetPosition();
private:

	b2Body* staticBody;
	b2Vec2 mSize;
	SDL_Texture *m_texture;
	b2Vec2 dimensions;
};

#endif


//#ifndef ONEWAYPLATFORM_H
//#define ONEWAYPLATFORM_H
//
//#include "Box2D\Box2D.h"
//#include "LTexture.h"
//#include "KeyboardManager.h"
//
//class OneWayPlatform {
//public:
//	OneWayPlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position);
//	~OneWayPlatform();
//	b2Fixture* GetFixture();
//	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
//	void CanCollideWithPlayer(bool toggle);
//	b2Vec2 GetPosition();
//private:
//
//	b2BodyDef myBodyDef;
//	b2Body* staticBody;
//	b2PolygonShape polyShape;
//	b2Fixture* mFix;
//	b2FixtureDef fixtureDef;
//	LTexture mTexture;
//};
//
//#endif