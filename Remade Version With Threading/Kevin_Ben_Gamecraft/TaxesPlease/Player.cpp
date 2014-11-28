#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Player.h"

Player::Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius) : isSpaceDown(false) {
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(position.x * PIXELSTOMETRES, -position.y * PIXELSTOMETRES);
	myBodyDef.userData = (void*)0;myBodyDef.angularDamping = 2;
	dynamicBody = world->CreateBody(&myBodyDef);
	circleShape.m_radius = radius * PIXELSTOMETRES;
	fixtureDef.shape = &circleShape;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.density = 0.1;
	dynamicBody->CreateFixture(&fixtureDef);

	texture.loadFromFile( "Player.png", gRenderer );
}

void Player::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) {
	texture.render((dynamicBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x, 
		-(dynamicBody->GetPosition().y * METRESTOPIXELS) - (texture.getWidth() / 2) + offset.y, 
		NULL, dynamicBody->GetAngle() * TORADIANS, NULL, SDL_FLIP_NONE, gRenderer );
}

void Player::Update() {
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::D)) {
		if (dynamicBody->GetContactList()) {
			dynamicBody->ApplyForceToCenter(b2Vec2(10,0),true);
			dynamicBody->ApplyAngularImpulse(-0.01,true);
		}
		else {
			dynamicBody->ApplyForceToCenter(b2Vec2(5,0),true);
		}
	}
	else if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::A)) {
		if (dynamicBody->GetContactList()) {
			dynamicBody->ApplyForceToCenter(b2Vec2(-10,0),true);
			dynamicBody->ApplyAngularImpulse(0.01,true);
		}
		else {
			dynamicBody->ApplyForceToCenter(b2Vec2(-5,0),true);
		}
	}
	if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::SPACE)) {
		if (dynamicBody->GetContactList() && !isSpaceDown) {
			dynamicBody->ApplyLinearImpulse(b2Vec2(0,12.5), dynamicBody->GetPosition(), true);
			isSpaceDown = true;
		}
	}
	else { isSpaceDown = false; }
}

b2Vec2 Player::GetPosition() {
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
}

bool Player::CanCollideWithOneWayPlatforms(float yPos) {
	return (dynamicBody->GetPosition().y - ((texture.getWidth() / 1.25) * PIXELSTOMETRES) <= yPos) ? true : false;
}
