#ifndef SPINNER_H
#define SPINNER_H

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"

class Spinner {
public:
	Spinner(b2World* world, SDL_Renderer* renderer, b2Vec2 position, float speed);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
private:
	~Spinner();
	b2BodyDef myBodyDef;
	b2Body* platformOne;
	b2Body* platformTwo;
	b2Body* pivotPoint;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture mTexture;
	b2RevoluteJointDef rJD;
	b2WeldJointDef wJD;
	b2WeldJoint* m_weldJoint;
	b2RevoluteJoint* m_revoluteJoint;
};

#endif