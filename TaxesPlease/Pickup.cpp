#include "Pickup.h"


Pickup::Pickup(void)
{
}

Pickup::Pickup(b2World* world, b2Vec2 pos, SDL_Renderer* gRenderer)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x , pos.y );
	m_bodyDef.userData = (void*)0;
	m_bodyDef.angularDamping = 2;
	m_dynamicBody = world->CreateBody(&m_bodyDef);
	m_pickupShape.SetAsBox(48, 48);
	m_fixtureDef.shape = &m_pickupShape;
	m_fixtureDef.density = 0.1;
	m_dynamicBody->CreateFixture(&m_fixtureDef);
	m_texture = IMG_LoadTexture(gRenderer,"Player.png");
	m_rect = SDL_Rect();
	m_rect.h = 48;
	m_rect.w = 48;
}


Pickup::~Pickup(void)
{
}

void Pickup::SetAlive(bool isAlive){
	m_alive = isAlive;
}

void Pickup::Draw(SDL_Renderer* gRenderer, b2Vec2 offset){
	m_rect.x = m_dynamicBody->GetPosition().x;
	m_rect.y = m_dynamicBody->GetPosition().y;
	SDL_RenderCopy( gRenderer, m_texture, NULL, &m_rect );
}