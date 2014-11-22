#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Player.h"

Player::Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimentions) : isSpaceDown(false) {
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x , position.y );
	myBodyDef.userData = (void*)0;
	myBodyDef.angularDamping = 2;
	dynamicBody = world->CreateBody(&myBodyDef);
	playerShape.SetAsBox(dimentions.x, dimentions.y);
	fixtureDef.shape = &playerShape;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.density = 0.1;
	dynamicBody->CreateFixture(&fixtureDef);
	m_KeyboardMan = KeyboardManager::getKeys();
	m_texture = IMG_LoadTexture(gRenderer,"Player.png");
	rect = SDL_Rect();
	rect.h = dimentions.x*2;
	rect.w = dimentions.y*2;
}

void Player::Update() {
	if (KeyboardManager::getKeys()->Key_Left) {
		moveLeft();
	}
	else if (KeyboardManager::getKeys()->Key_Right) {
		moveRight();
	}
	if (KeyboardManager::getKeys()->Key_Up) {
		jump();
	}
	else { isSpaceDown = false; }
}

void Player::moveLeft(){
	dynamicBody->ApplyLinearImpulse(b2Vec2(-250,0),GetPosition(),true);
}

void Player::moveRight(){
	dynamicBody->ApplyLinearImpulse(b2Vec2(250,0),GetPosition(),true);
}


b2Vec2 Player::GetPosition() {
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}

void Player::Render(SDL_Renderer* gRenderer, b2Vec2 offset) {

	rect.x = dynamicBody->GetPosition().x -(rect.w/2.0f)- offset.x;
	rect.y = dynamicBody->GetPosition().y -(rect.h/2.0f)+ offset.y;
	SDL_RenderCopy( gRenderer, m_texture, NULL, &rect );
}

void Player::jump(){

		dynamicBody->ApplyLinearImpulse(b2Vec2(0,-40), dynamicBody->GetPosition(), true);
}