#ifndef _BASICPLATFORM_H_
#define _BASICPLATFORM_H_

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class BasicPlatform {
public:
	BasicPlatform();
	BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~BasicPlatform ();
	b2Body* staticBody;
private:
	
	SDL_Renderer * mRenderer;
	b2Vec2 mSize;
	SDL_Texture* m_texture;
};

#endif