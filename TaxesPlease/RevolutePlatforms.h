#ifndef REVOLUTEPLATFORMS_H
#define REVOLUTEPLATFORMS_H

#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

class RevolutePlatforms {
public:
	RevolutePlatforms(b2World* world, SDL_Renderer* renderer, b2Vec2 position, b2Vec2 dimensions, float radius, float speed);
	void Draw(SDL_Renderer* renderer, b2Vec2 offset);
private:
	~RevolutePlatforms();
	b2BodyDef myBodyDef;
	b2Body* platformOne;
	b2Body* platformTwo;
	b2Body* centre;
	b2Body* pivotPoint;
	b2PolygonShape polyShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
//	LTexture mTexture;
	b2RevoluteJointDef jD;
	b2RevoluteJoint* m_centreJoint;
	b2RevoluteJoint* m_platformJoint1;
	b2RevoluteJoint* m_platformJoint2;
	b2Vec2 size;
	SDL_Texture* m_texture;
};

#endif