#ifndef PLAYER_H
#define PLAYER_H

#include <SDL_image.h>
#include <SDL.h>
#include "Box2D/Box2D.h"
#include "KeyboardManager.h"
#include "SoundManager.h"

class Player {
public:
	Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimentions);
	~Player();
	void Render(SDL_Renderer* gRenderer, b2Vec2 offset );
	void Update();
	b2Vec2 GetPosition();
private:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2PolygonShape playerShape;
	b2Fixture* mFix;
	b2FixtureDef fixtureDef;
	SDL_Texture * m_texture;
	SDL_Rect rect;
	SoundManager* sm;
	bool isSpaceDown;
	KeyboardManager* m_KeyboardMan;
	void moveLeft();
	void moveRight();
	void jump();
};

#endif
