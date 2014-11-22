#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)
#include "BasicPlatform.h"
BasicPlatform::BasicPlatform(){}

BasicPlatform::BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	
	m_texture = IMG_LoadTexture(gRenderer,"Quit.png");//loadFromFile( "Platform.png", gRenderer );
	
	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody);
	staticBody->SetUserData((void*)-2);
	rect = SDL_Rect();
	rect.x = position.x;
	rect.y = position.y;
	rect.h = dimensions.x;
	rect.w = dimensions.y;

}

BasicPlatform::~BasicPlatform(){
	staticBody->GetWorld()->DestroyBody(staticBody);
}

void BasicPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 

	SDL_RenderCopy(gRenderer,m_texture,NULL,&rect);
}