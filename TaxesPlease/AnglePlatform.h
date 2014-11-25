#ifndef ANGLEPLATFORM_H
#define ANGLEPLATFORM_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class AnglePlatform {
public:
	AnglePlatform();
	AnglePlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~AnglePlatform ();
private:
	b2Vec2 dimensions;
	b2Body* staticBody;
	b2Vec2 mSize;
	SDL_Texture* m_texture;
};

#endif


//#ifndef ANGLEPLATFORM_H
//#define ANGLEPLATFORM_H
//
//#include "Box2D\Box2D.h"
//#include "LTexture.h"
//#include "KeyboardManager.h"
//
//class AnglePlatform {
//public:
//	AnglePlatform();
//	AnglePlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position, float angleRadians);
//	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
//	~AnglePlatform ();
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