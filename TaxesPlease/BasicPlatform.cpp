#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "BasicPlatform.h"
BasicPlatform::BasicPlatform(){}
BasicPlatform::BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	
	m_texture.loadFromFile( "Platform.png", gRenderer );
	
	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody);
	staticBody->SetUserData((void*)-2);
	
}

BasicPlatform::~BasicPlatform(){
	staticBody->GetWorld()->DestroyBody(staticBody);
}

void BasicPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	m_texture.render((staticBody->GetPosition().x * METRESTOPIXELS) - (m_texture.getWidth() / 2) - offset.x,
		-(staticBody->GetPosition().y * METRESTOPIXELS) - (m_texture.getHeight() / 2) + offset.y, NULL, 
		staticBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}