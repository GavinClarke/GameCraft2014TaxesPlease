#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)
#include "Spinner.h"

Spinner::Spinner(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float speed) {
	mTexture.loadFromFile( "Spinner.png", gRenderer );

	myBodyDef.userData = (void*)-2;

	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	pivotPoint = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(0.01, 0.01);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 0.1f;
	fixtureDef.filter.groupIndex = -1;
	pivotPoint->CreateFixture(&fixtureDef);
	
	myBodyDef.type = b2_dynamicBody;
	fixtureDef.filter.groupIndex = 0;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	platformOne = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox((mTexture.getWidth()/2) * PIXELSTOMETRES, (mTexture.getHeight()/2) * PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	platformOne->CreateFixture(&fixtureDef);

	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	myBodyDef.angle = 1.57f;
	platformTwo = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox((mTexture.getWidth()/2) * PIXELSTOMETRES, (mTexture.getHeight()/2) * PIXELSTOMETRES);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 1.0f;
	platformTwo->CreateFixture(&fixtureDef);

	wJD.Initialize(platformOne, platformTwo, platformOne->GetWorldCenter());
	wJD.collideConnected = false;
	m_weldJoint = (b2WeldJoint*)world->CreateJoint(&wJD);

	rJD.Initialize(pivotPoint, platformTwo, pivotPoint->GetWorldCenter());
	rJD.collideConnected = false;
	rJD.maxMotorTorque = 10000;
	rJD.enableMotor = true;
	rJD.motorSpeed = speed * PIXELSTOMETRES;
	m_revoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&rJD);
}

Spinner::~Spinner() {
	platformOne->GetWorld()->DestroyJoint(m_weldJoint);
	platformOne->GetWorld()->DestroyJoint(m_revoluteJoint);
	platformOne->GetWorld()->DestroyBody(platformOne);
	platformTwo->GetWorld()->DestroyBody(platformTwo);
	pivotPoint->GetWorld()->DestroyBody(pivotPoint);
}

void Spinner::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	mTexture.render((platformOne->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(platformOne->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		platformOne->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );

	mTexture.render((platformTwo->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(platformTwo->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		platformTwo->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );

}