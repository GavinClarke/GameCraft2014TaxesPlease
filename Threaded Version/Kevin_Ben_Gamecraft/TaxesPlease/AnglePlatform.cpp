#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "AnglePlatform.h"
AnglePlatform::AnglePlatform(){}

AnglePlatform::AnglePlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float angleRadians) {
	dimensions = b2Vec2(300,60);
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "AnglePlatform.png"  ));
	staticBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody,1);
	staticBody->SetUserData((void*)-2);
}

void AnglePlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	//Render to screen
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float rotation = staticBody->GetAngle()*TORADIANS;

	stretchRect.x = (staticBody->GetPosition().x * METRESTOPIXELS ) -(mSize.x/2.0f) - offset.x;
	stretchRect.y = -(staticBody->GetPosition().y * METRESTOPIXELS ) -(mSize.y/2.0f) + offset.y;

	stretchRect.w = mSize.x; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( gRenderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

//#define PIXELSTOMETRES 1/30.0f
//#define METRESTOPIXELS 30
//#define TORADIANS (-180/3.1415926536f)
//
//#include "AnglePlatform.h"
//AnglePlatform::AnglePlatform(){}
//AnglePlatform::AnglePlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float angleRadians) {
//	mTexture.loadFromFile( "AnglePlatform.png", gRenderer );
//
//	myBodyDef.type = b2_staticBody;
//	myBodyDef.position.Set(position.x*PIXELSTOMETRES, -position.y*PIXELSTOMETRES);
//	myBodyDef.userData = (void*)-2;
//	myBodyDef.angle = angleRadians;
//	staticBody = world->CreateBody(&myBodyDef);
//	polyShape.SetAsBox(mTexture.getWidth()/2*PIXELSTOMETRES, mTexture.getHeight()/2*PIXELSTOMETRES);
//	fixtureDef.shape = &polyShape;
//	staticBody->CreateFixture(&fixtureDef);
//}
//
//void AnglePlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
//	mTexture.render((staticBody->GetPosition().x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
//		-(staticBody->GetPosition().y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
//		staticBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
//}