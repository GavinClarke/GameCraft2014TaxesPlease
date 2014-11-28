#include "FallingPlatform.h"
#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

FallingPlatform::FallingPlatform(){}

FallingPlatform::FallingPlatform(b2World* world, SDL_Renderer* renderer,b2Vec2 position,float angle)
{
	dimensions = b2Vec2(300,60);
	mSize = dimensions;
	m_texture = SDL_CreateTextureFromSurface( renderer, IMG_Load( "FallingPlatform.png"  ));
	
	m_DynamicBody = ObjectFactory::instance()->createPlatform(world, position, dimensions, angle, b2_staticBody,1);
	m_DynamicBody->SetType(b2_dynamicBody);
	m_DynamicBody->SetUserData((void*)-7);
	m_DynamicBody->SetGravityScale(0);//apply gravity
	collided= false;	
}

FallingPlatform::~FallingPlatform()
{
	m_DynamicBody->GetWorld()->DestroyBody(m_DynamicBody);
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
	float rotation = (m_DynamicBody->GetAngle()*-180.0/3.14159265);
	
	stretchRect.x = (m_DynamicBody->GetPosition().x * METRESTOPIXELS ) -(mSize.x/2.0f) - offset.x;
	stretchRect.y = -(m_DynamicBody->GetPosition().y * METRESTOPIXELS ) -(mSize.y/2.0f) + offset.y;

	stretchRect.w = mSize.x; 
	stretchRect.h = mSize.y;
	SDL_RenderCopyEx ( renderer, m_texture, NULL, &stretchRect, rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

void FallingPlatform::CheckPlayerCollision()//b2Body* PlayerBody)
{
	if ((int)m_DynamicBody->GetUserData() == -200) {
		m_DynamicBody->SetGravityScale(1);//apply gravity
		m_DynamicBody->SetLinearVelocity(b2Vec2(0,-9.81f));
	}	
}

void FallingPlatform::CheckBombCollision()
{
	if ((int)m_DynamicBody->GetUserData() == -300) {
		m_DynamicBody->SetLinearVelocity(b2Vec2_zero);
	}	
}