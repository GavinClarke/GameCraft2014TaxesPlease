#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "OneWayPlatform.h"

OneWayPlatform::OneWayPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "OneWayPlatformPlatform.png"  ));

	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody,1);
	staticBody->SetUserData((void*)-6);
	
}

OneWayPlatform::~OneWayPlatform()
{
}

void OneWayPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	//Render to screen
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float rotation = (staticBody->GetAngle()*180.0/3.14159265);

	stretchRect.x = (staticBody->GetPosition().x ) -(mSize.x/2.0f) - offset.x;
	stretchRect.y = (staticBody->GetPosition().y ) -(mSize.y/2.0f) + offset.y;

	stretchRect.w = mSize.x; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

void OneWayPlatform::CanCollideWithPlayer(bool toggle) {
	b2Filter filter; 
	(toggle == true) ? filter.groupIndex = -1 : filter.groupIndex = 0;
	staticBody->GetFixtureList()[0].SetFilterData(filter);
}

b2Vec2 OneWayPlatform::GetPosition() {
	return staticBody->GetPosition();
}