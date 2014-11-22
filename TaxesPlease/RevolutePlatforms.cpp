#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "RevolutePlatforms.h"

RevolutePlatforms::RevolutePlatforms(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimensions, float radius, float speed) {
	size = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "Platform.png") );

	pivotPoint = ObjectFactory::instance()->createPlatform(world, position, b2Vec2(0.01,0.01), 0, b2_staticBody, 0.1f);
	pivotPoint->SetUserData((void*)-2);
	b2Filter f; f.groupIndex = -1; pivotPoint->GetFixtureList()[0].SetFilterData(f);

	centre = ObjectFactory::instance()->createPlatform(world, position, b2Vec2(radius , 10), 0, b2_dynamicBody, 1.0f);
	
	f.groupIndex = -1; pivotPoint->GetFixtureList()[0].SetFilterData(f);

	platformOne = ObjectFactory::instance()->createPlatform(world, position, dimensions, 0, b2_dynamicBody, 0.1f);
	platformOne->SetFixedRotation(true);

	platformTwo = ObjectFactory::instance()->createPlatform(world, b2Vec2(position.x + radius, position.y), dimensions, 0, b2_dynamicBody, 0.1f);
	platformTwo->SetFixedRotation(true);

	m_centreJoint = ObjectFactory::instance()->createRevoluteJoint(world, pivotPoint, centre, centre->GetWorldCenter());
	m_centreJoint->EnableMotor(true);
	m_centreJoint->SetMotorSpeed(speed);
	m_centreJoint->SetMaxMotorTorque(1000);

	m_platformJoint1 = ObjectFactory::instance()->createRevoluteJoint(world, centre, platformOne, platformOne->GetWorldCenter());
	m_platformJoint2 = ObjectFactory::instance()->createRevoluteJoint(world, centre, platformTwo, platformTwo->GetWorldCenter());
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
	SDL_Rect stretchRect;
	float rotation = platformOne->GetAngle() * TORADIANS;

	stretchRect.x = (platformOne->GetPosition().x ) - (size.x / 2) - offset.x;
	stretchRect.y = (platformOne->GetPosition().y ) - (size.y / 2) + offset.y;
	stretchRect.w = size.x;
	stretchRect.h = size.y;

	SDL_RenderCopyEx(gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_FLIP_NONE);

	stretchRect.x = (platformTwo->GetPosition().x ) - (size.x / 2) - offset.x;
	stretchRect.y = (platformTwo->GetPosition().y ) - (size.y / 2) + offset.y;
	stretchRect.w = size.x;
	stretchRect.h = size.y;

	SDL_RenderCopyEx(gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_FLIP_NONE);
}