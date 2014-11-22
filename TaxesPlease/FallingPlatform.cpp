#include "FallingPlatform.h"
#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

FallingPlatform::FallingPlatform(){}

FallingPlatform::FallingPlatform(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position,b2Vec2 dimensions, float angleRadians)
{
	
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( gRenderer, IMG_Load( "FallingPlatform.png"  ));
	
	//m_BodyDef.userData = (void*)-7;
	dynamicBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angleRadians, b2_staticBody);
	dynamicBody->SetType(b2_dynamicBody);
	dynamicBody->SetUserData((void*)-7);
}

FallingPlatform::~FallingPlatform()
{
	dynamicBody->GetWorld()->DestroyBody(dynamicBody);
}

void FallingPlatform::Update()
{
	CheckBombCollision();
	CheckPlayerCollision();
}

void FallingPlatform::Draw(SDL_Renderer* renderer, b2Vec2 offset){
	//Render to screen
	SDL_Rect stretchRect; 
	//SDL_RenderDrawLine
	float rotation = (dynamicBody->GetAngle()*180.0/3.14159265);

	stretchRect.x = (dynamicBody->GetPosition().x  * METRESTOPIXELS) -(mSize.x/2.0f) - offset.x;
	stretchRect.y = (dynamicBody->GetPosition().y  * METRESTOPIXELS) -(mSize.y/2.0f) + offset.y;

	stretchRect.w = mSize.x; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( renderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );	
}

void FallingPlatform::CheckPlayerCollision()//b2Body* PlayerBody)
{
	if ((int)dynamicBody->GetUserData() == -200) {
		dynamicBody->SetGravityScale(1);//apply gravity
		dynamicBody->SetLinearVelocity(b2Vec2(0,-9.81f));
	}	
}

void FallingPlatform::CheckBombCollision()
{
	if ((int)dynamicBody->GetUserData() == -300) {
		dynamicBody->SetLinearVelocity(b2Vec2_zero);
	}	
}