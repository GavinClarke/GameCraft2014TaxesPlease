#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "RevolutePlatforms.h"

RevolutePlatforms::RevolutePlatforms(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius, float speed) {
	mTexture.loadFromFile( "RevolutePlatform.png", gRenderer );

	myBodyDef.userData = (void*)-2;

	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	pivotPoint = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(0.01, 0.01);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 0.1f;
	fixtureDef.filter.groupIndex = -1;
	pivotPoint->CreateFixture(&fixtureDef);
	
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	centre = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(radius * PIXELSTOMETRES, 10*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	centre->CreateFixture(&fixtureDef);

	myBodyDef.position.Set((position.x - radius)*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
	fixtureDef.filter.groupIndex = 0;
	myBodyDef.fixedRotation = true;
	platformOne = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 0.1f;
	platformOne->CreateFixture(&fixtureDef);

	myBodyDef.position.Set((position.x + radius)*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
	platformTwo = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 0.1f;
	platformTwo->CreateFixture(&fixtureDef);

	jD.Initialize(pivotPoint, centre, centre->GetWorldCenter());
	jD.collideConnected = false;
	jD.enableMotor = true;
	jD.motorSpeed = speed * PIXELSTOMETRES;
	jD.maxMotorTorque = 1000;
	m_centreJoint = (b2RevoluteJoint*)world->CreateJoint(&jD);

	jD.Initialize(centre, platformOne, platformOne->GetWorldCenter());
	jD.enableMotor = false;
	jD.collideConnected = false;
	m_platformJoint1 = (b2RevoluteJoint*)world->CreateJoint(&jD);

	jD.Initialize(centre, platformTwo, platformTwo->GetWorldCenter());
	jD.collideConnected = false;
	m_platformJoint2 = (b2RevoluteJoint*)world->CreateJoint(&jD);
}

RevolutePlatforms::~RevolutePlatforms() {
	platformOne->GetWorld()->DestroyJoint(m_centreJoint);
	platformOne->GetWorld()->DestroyJoint(m_platformJoint1);
	platformOne->GetWorld()->DestroyJoint(m_platformJoint2);
	platformOne->GetWorld()->DestroyBody(platformOne);
	platformTwo->GetWorld()->DestroyBody(platformTwo);
	centre->GetWorld()->DestroyBody(centre);
}

void RevolutePlatforms::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	mTexture.render((platformOne->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(platformOne->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		platformOne->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );

	mTexture.render((platformTwo->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(platformTwo->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		platformTwo->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );

}