#ifndef WATER_H
#define WATER_H

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"

class Water {
public:
	Water(b2World* world, SDL_Renderer* renderer);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
	float getYPos();
private:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2Body* leftBody;
	b2Body* rightBody;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;
	b2ParticleSystem* pS;
	b2ParticleGroup* pG;
};

#endif