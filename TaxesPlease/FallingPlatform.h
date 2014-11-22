#ifndef FALLINGPLATFORM_H
#define FALLINGPLATFORM_H

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"


//Platform will need its position to be inherited from Base platform
class FallingPlatform // :BasePlatform
{
public:
	FallingPlatform();
	FallingPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians);
	~FallingPlatform();
	
	void Draw(SDL_Renderer* renderer, b2Vec2);

	void Update();


private:
	void CheckPlayerCollision();
	void CheckBombCollision();
	void DropPlatform(bool collided);
	//Box2d varible
	
	b2Body* dynamicBody ;
	b2Vec2 mSize;
	SDL_Texture *m_texture;
};


#endif