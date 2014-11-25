#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "PrismaticPlatform.h"

PrismaticPlatform::PrismaticPlatform(b2World* world, SDL_Renderer* gRenderer, float leftBound, float rightBound, float yPosition, float speed, b2Vec2 dimensions)
	:m_rightBound(rightBound), m_leftBound(leftBound) {
	//mTexture.loadFromFile( "PrismaticPlatform.png", gRenderer );

	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "PrismaticPlatform.png") );

	anchor = ObjectFactory::instance()->createPlatform(world, b2Vec2(leftBound, yPosition), b2Vec2(0.01, 0.01), 0, b2_staticBody, 0.1f);
	anchor->SetUserData((void*)-2);
	b2Filter f; f.groupIndex = -1; anchor->GetFixtureList()[0].SetFilterData(f);

	platform = ObjectFactory::instance()->createPlatform(world, b2Vec2(rightBound, yPosition), dimensions, 0, b2_dynamicBody, 1.0f);

	m_joint = ObjectFactory::instance()->createPrismaticJoint(world, anchor, platform, anchor->GetWorldCenter(), b2Vec2(1,0));
	m_joint->EnableMotor(true);
	m_joint->SetMotorSpeed(speed);
	m_joint->SetMaxMotorForce(1000);
}

PrismaticPlatform::~PrismaticPlatform() {
	platform->GetWorld()->DestroyJoint(m_joint);
	platform->GetWorld()->DestroyBody(platform);
	anchor->GetWorld()->DestroyBody(anchor);
}

void PrismaticPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	SDL_Rect stretchRect;
	float rotation = platform->GetAngle() * TORADIANS;

	stretchRect.x = (platform->GetPosition().x ) - (size.x / 2) - offset.x;
	stretchRect.y = -(platform->GetPosition().y ) - (size.y / 2) + offset.y;
	stretchRect.w = size.x;
	stretchRect.h = size.y;

	SDL_RenderCopyEx(gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_FLIP_NONE);

	if (platform->GetPosition().x > m_rightBound || platform->GetPosition().x < m_leftBound) {
		m_joint->SetMotorSpeed(m_joint->GetMotorSpeed()*-1);
	}
}