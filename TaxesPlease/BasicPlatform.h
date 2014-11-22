#ifndef _BASICPLATFORM_H_
#define _BASICPLATFORM_H_

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include <SDL_image.h>
#include <SDL.h>
#include "ObjectFactory.h"

class BasicPlatform {
public:
	BasicPlatform();
	BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	~BasicPlatform ();
private:
	b2Body* staticBody;
<<<<<<< HEAD
	b2Vec2 mSize;
	SDL_Texture* m_texture;
=======
	SDL_Texture *  m_texture;
	SDL_Rect rect;
>>>>>>> c72104e0011bbe600c3c24110b3795a2e7fad7f7
};

#endif