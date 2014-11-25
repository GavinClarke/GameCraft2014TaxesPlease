#ifndef PLAYER_H
#define PLAYER_H

#include "Box2D/Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
class Player {
public:
	Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, float radius);
	~Player();
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset );
	void Update();
	b2Vec2 GetPosition();
	bool CanCollideWithOneWayPlatforms(float yPos);
private:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2CircleShape circleShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	LTexture texture;
	bool isSpaceDown;
};

#endif
