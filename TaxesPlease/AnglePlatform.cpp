#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "AnglePlatform.h"
AnglePlatform::AnglePlatform(){}

AnglePlatform::AnglePlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	mTexture.loadFromFile( "AnglePlatform.png", gRenderer );
	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody);
	//myBodyDef.userData = (void*)-2;
	staticBody->SetUserData((void*)-2);
}

void AnglePlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	mTexture.render((staticBody->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
		-(staticBody->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
		staticBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}