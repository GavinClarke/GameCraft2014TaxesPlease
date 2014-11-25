#ifndef _BASICPLATFORM_H_
#define _BASICPLATFORM_H_

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class BasicPlatform {
public:
	BasicPlatform();
	BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~BasicPlatform();
private:
	b2Body* staticBody;
	SDL_Renderer * mRenderer;
	b2Vec2 mSize;
	SDL_Texture* m_texture;
	b2Vec2 dimensions;
};

#endif


/*#ifndef _BASICPLATFORM_H_
#define _BASICPLATFORM_H_

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"

class BasicPlatform {
public:
	BasicPlatform();
	BasicPlatform(b2World* world, SDL_Renderer* renderer, b2Vec2 position);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~BasicPlatform ();
private:
	
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_fixtureDef;
	LTexture m_texture;
};

#endif*/