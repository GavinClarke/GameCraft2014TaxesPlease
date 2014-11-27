#ifndef PLAYER_H
#define PLAYER_H

#include <SDL_image.h>
#include <SDL.h>
#include "Box2D/Box2D.h"
#include "KeyboardManager.h"
#include "SoundManager.h"
#include <SDL_thread.h>

class Player {
protected:
	/*static void StaticThreadProc(void* pParam)
   {
	   return ((Player*)pParam)->moveLeft();
   }*/
public:
	Player(b2World* world, SDL_Renderer* gRenderer, b2Vec2 position, b2Vec2 dimentions);
	~Player();
	void Render(SDL_Renderer* gRenderer, b2Vec2 offset );
	void Update();
	b2Vec2 GetPosition();
	int count;
	void moveLeft();
	void moveRight();
	void jump();
	void Death();
	
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
	

	//The thread that will be used 
	SDL_Thread *thread;
	SDL_Thread *thread2;
	SDL_Thread *thread3;

	//The protective semaphore 
	SDL_sem *Lock;
};

#endif
