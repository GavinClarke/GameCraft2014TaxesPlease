#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "PrismaticPlatform.h"

PrismaticPlatform::PrismaticPlatform(b2World* world, SDL_Renderer* gRenderer, float leftBound, float rightBound, float yPosition, float speed)
	:m_rightBound(rightBound), m_leftBound(leftBound) {
	mTexture.loadFromFile( "PrismaticPlatform.png", gRenderer );

	myBodyDef.userData = (void*)-2;

	myBodyDef.position.Set(leftBound * PIXELSTOMETRES, -yPosition * PIXELSTOMETRES);
	anchor = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(0.01, 0.01);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 0.1f;
	fixtureDef.filter.groupIndex = -1;
	anchor->CreateFixture(&fixtureDef);
	
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(rightBound * PIXELSTOMETRES, -yPosition * PIXELSTOMETRES);
	platform = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox((mTexture.getWidth()/2) * PIXELSTOMETRES, (mTexture.getHeight()/2) * PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.groupIndex = 0;
	platform->CreateFixture(&fixtureDef);

	jD.Initialize(anchor, platform, anchor->GetWorldCenter(), b2Vec2(1,0));
	jD.collideConnected = false;
	jD.enableMotor = true;
	jD.motorSpeed = speed * PIXELSTOMETRES;
	jD.maxMotorForce = 1000;
	m_joint = (b2PrismaticJoint*)world->CreateJoint(&jD);
}

PrismaticPlatform::~PrismaticPlatform() {
	platform->GetWorld()->DestroyJoint(m_joint);
	platform->GetWorld()->DestroyBody(platform);
	anchor->GetWorld()->DestroyBody(anchor);
}

void PrismaticPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	mTexture.render((platform->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(platform->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		platform->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );

	if (platform->GetPosition().x*METRESTOPIXELS > m_rightBound || platform->GetPosition().x*METRESTOPIXELS < m_leftBound) {
		m_joint->SetMotorSpeed(m_joint->GetMotorSpeed()*-1);
	}
}