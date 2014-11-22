#pragma once

#include <Box2D/Box2D.h>
#include <SDL_image.h>
#include <iostream>

static class ObjectFactory {
public:
	static ObjectFactory* m_instance;
	static ObjectFactory* instance();
	ObjectFactory(void) {}
	~ObjectFactory(void) {}

	static b2Body* createPlatform(b2World* world, b2Vec2 psoition, b2Vec2 dimensions, float angle, int userData);

	static b2Joint* createPulleyJointb2World* world, b2Body* body1, b2Body* body2, b2Vec2 groundAnchorA, b2Vec2 groundAnchorB, b2Vec2 anchorA, b2Vec2 anchorB);

	static b2RevoluteJoint* createRevoluteJoint(b2World* world, b2Vec2 pos, b2Body* body,b2Body* ground);

	static b2PrismaticJoint* createPrismaticJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 position, b2Vec2 translation);

	static b2PrismaticJoint* createRevoluteJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 position, b2Vec2 translation);
};