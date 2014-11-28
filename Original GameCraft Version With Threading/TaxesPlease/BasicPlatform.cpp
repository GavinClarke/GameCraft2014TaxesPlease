#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "BasicPlatform.h"
BasicPlatform::BasicPlatform(){}
BasicPlatform::BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "images/pipePlatform.png"  ));
	
	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody,1);
	staticBody->SetUserData((void*)-2);
	
}

BasicPlatform::~BasicPlatform(){
	staticBody->GetWorld()->DestroyBody(staticBody);
}

void BasicPlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	//Render to screen
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float rotation = (staticBody->GetAngle()*180.0/3.14159265);

	stretchRect.x = (staticBody->GetPosition().x ) -(mSize.x/2.5f) - offset.x;
	stretchRect.y = (staticBody->GetPosition().y ) /*-(mSize.y/2.0f)*/ + offset.y;

	stretchRect.w = mSize.x *2; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}