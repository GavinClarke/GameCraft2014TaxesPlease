#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)
#include "BasicPlatform.h"
BasicPlatform::BasicPlatform(){}

BasicPlatform::BasicPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians) {
	
<<<<<<< HEAD
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "BasicPlatform.png"  ));
=======
	m_texture = IMG_LoadTexture(gRenderer,"Quit.png");//loadFromFile( "Platform.png", gRenderer );
>>>>>>> c72104e0011bbe600c3c24110b3795a2e7fad7f7
	
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
<<<<<<< HEAD
	//Render to screen
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float rotation = (staticBody->GetAngle()*180.0/3.14159265);

	stretchRect.x = dynamicBody->GetPosition().x-(mSize.x/2.0f);
	stretchRect.y = dynamicBody->GetPosition().y-(mSize.y/2.0f);

	stretchRect.w = mSize.x; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
=======

	SDL_RenderCopy(gRenderer,m_texture,NULL,&rect);
>>>>>>> c72104e0011bbe600c3c24110b3795a2e7fad7f7
}