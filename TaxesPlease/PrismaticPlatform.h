#ifndef PRISMATICPLATFORM_H
#define PRISMATICPLATFORM_H

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"

class PrismaticPlatform {
public:
	PrismaticPlatform(b2World* world, SDL_Renderer* renderer, float leftBound, float rightBound, float yPosition, float speed);
	~PrismaticPlatform();	
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
private:
	b2BodyDef myBodyDef;
	b2Body* platform;
	b2Body* anchor;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;
	b2PrismaticJointDef jD;
	b2PrismaticJoint* m_joint;
	float m_rightBound;
	float m_leftBound;
};

#endif