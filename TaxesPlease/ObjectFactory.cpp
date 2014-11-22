#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::m_instance = 0;
ObjectFactory::ObjectFactory() {}

ObjectFactory* ObjectFactory::instance() {
	if (m_instance == 0)
		m_instance = new ObjectFactory();
	return m_instance;
}

b2Body* ObjectFactory::createPlatform(b2World* world, b2Vec2 position, b2Vec2 dimensions, float angle, b2BodyType type) {
	b2Body* box;
	b2BodyDef boxDef;      
	b2PolygonShape boxShape;
	b2FixtureDef boxFixture;

	boxDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	boxDef.type = type;
	boxDef.angle = angle;
	box = world->CreateBody(&boxDef);
	boxShape.SetAsBox((dimensions.x/2) * PIXELSTOMETRES, (dimensions.y/2) * PIXELSTOMETRES);
	boxFixture.shape = &boxShape;
	box->CreateFixture(&boxFixture);

	return box;
}

b2Joint* ObjectFactory::createPulleyJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 groundAnchorA, b2Vec2 groundAnchorB, b2Vec2 anchorA, b2Vec2 anchorB) {
	b2PulleyJointDef pullJoint = b2PulleyJointDef();
	pullJoint.Initialize(body1, body2, b2Vec2(groundAnchorA.x*PIXELSTOMETRES, -groundAnchorA.y*PIXELSTOMETRES), b2Vec2(groundAnchorB.x*PIXELSTOMETRES, -groundAnchorB.y*PIXELSTOMETRES), 
		b2Vec2(anchorA.x*PIXELSTOMETRES, -anchorA.y*PIXELSTOMETRES), b2Vec2(anchorB.x*PIXELSTOMETRES, -anchorB.y*PIXELSTOMETRES), 1);
	pullJoint.collideConnected = false;
	b2Joint* joint = world->CreateJoint(&pullJoint);
	return joint;
}

b2RevoluteJoint* ObjectFactory::createRevoluteJoint(b2World* world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchor){
	b2RevoluteJoint* joint;
	b2RevoluteJointDef revDef;
	revDef.Initialize(bodyA, bodyB, b2Vec2(anchor.x*PIXELSTOMETRES, -anchor.y*PIXELSTOMETRES));
	revDef.collideConnected = false;
	joint = (b2RevoluteJoint*)world->CreateJoint(&revDef);
	return joint;
}

b2PrismaticJoint* ObjectFactory::createPrismaticJoint(b2World* world, b2Body* body1, b2Body* body2, b2Vec2 position, b2Vec2 translation) {
	b2PrismaticJoint* joint;
	b2PrismaticJointDef revDef;
	revDef.Initialize(body1, body2, b2Vec2(position.x*PIXELSTOMETRES, -position.y*PIXELSTOMETRES), translation);
	revDef.collideConnected = false;
	joint = (b2PrismaticJoint*)world->CreateJoint(&revDef);
	return joint;
}