#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)
#include "Spinner.h"

Spinner::Spinner(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimensions, float speed) {
	mTexture.loadFromFile( "Spinner.png", gRenderer );

	pivotPoint = ObjectFactory::instance()->createPlatform(world, position, b2Vec2(0.01,0.01), 0, b2_staticBody, 0.1f);
	pivotPoint->SetUserData((void*)-2);
	b2Filter f; f.groupIndex = -1; pivotPoint->GetFixtureList()[0].SetFilterData(f);
	platformOne = ObjectFactory::instance()->createPlatform(world, position, dimensions, 0, b2_dynamicBody, 1.0f);
	platformTwo = ObjectFactory::instance()->createPlatform(world, position, b2Vec2((dimensions.x/2) * PIXELSTOMETRES, (dimensions.y/2) * PIXELSTOMETRES), 1.57f, b2_dynamicBody, 1.0f);
	m_weldJoint = ObjectFactory::instance()->createWeldJoint(world, platformOne, platformTwo, platformOne->GetWorldCenter());

	rJD.Initialize(pivotPoint, platformTwo, pivotPoint->GetWorldCenter());
	rJD.collideConnected = false;
	rJD.maxMotorTorque = 10000;
	rJD.enableMotor = true;
	rJD.motorSpeed = speed * PIXELSTOMETRES;
	m_revoluteJoint = ObjectFactory::instance()->createRevoluteJoint(world, pivotPoint, platformTwo, pivotPoint->GetWorldCenter());
	m_revoluteJoint->SetMaxMotorTorque(10000);
	m_revoluteJoint->EnableMotor(true);
	m_revoluteJoint->SetMotorSpeed(speed*PIXELSTOMETRES);
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