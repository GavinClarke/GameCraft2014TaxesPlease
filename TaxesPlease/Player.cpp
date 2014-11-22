#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Player.h"

Player::Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimentions) : isSpaceDown(false) {
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
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
}

void Player::Update() {
	if (m_KeyboardMan->Key_Left) {
		moveLeft();
	}
	else if (m_KeyboardMan->Key_Right) {
		moveRight();
	}
	if (m_KeyboardMan->Key_Space) {
		jump();
	}
	else { isSpaceDown = false; }
}

void Player::moveLeft(){
			dynamicBody->ApplyForceToCenter(b2Vec2(5,0),true);
}

void Player::moveRight(){
	dynamicBody->ApplyForceToCenter(b2Vec2(-5,0),true);
}


b2Vec2 Player::GetPosition() {
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}

void Player::Render(SDL_Renderer* gRenderer, b2Vec2 offset) {
	SDL_RenderCopyEx ( gRenderer, m_texture, NULL, &m_texture, dynamicBody->GetAngle() * TORADIANS, NULL, SDL_RendererFlip::SDL_FLIP_NONE );
}

void Player::jump(){
	if (dynamicBody->GetContactList() && !isSpaceDown) {
			dynamicBody->ApplyLinearImpulse(b2Vec2(0,12.5), dynamicBody->GetPosition(), true);
			isSpaceDown = true;
	}
}