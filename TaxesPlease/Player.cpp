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
	m_texture = IMG_LoadTexture(gRenderer,"images/player.png");
	rect = SDL_Rect();
	rect.h = dimentions.x*2;
	rect.w = dimentions.y*2;
	sm = new SoundManager();
	sm->PlayBackground();
	count = 0;

	//thread = SDL_CreateThread( Player::moveLeft, this );
	//thread = NULL;
	Lock = SDL_CreateSemaphore( 1 );
	
	//thread = SDL_CreateThread( &Player::moveLeft, NULL, NULL);//&Player::moveLeft
	//thread2 = SDL_CreateThread( std::ref(this->moveRight), NULL, this);
	//thread3 = SDL_CreateThread(std::ref(this->jump), NULL, this);
}

void Player::Update() {
	if (KeyboardManager::getKeys()->Key_Left) {
		//thread = SDL_CreateThread( &Player::moveLeft, NULL, this );//moveLeft();
	}
	else if (KeyboardManager::getKeys()->Key_Right) {
		//moveRight();
	}
	if (KeyboardManager::getKeys()->Key_Up) {
		//jump();
		//sm->PlayJumpSound();
	}
	else { count =0; }
}

void Player::moveLeft(){
	if (KeyboardManager::getKeys()->Key_Left) {
	//Lock 
	SDL_SemWait( Lock );
	dynamicBody->ApplyForce(b2Vec2(-5000,0),GetPosition(),true);
	//Unlock 
	SDL_SemPost( Lock );
	}
}

void Player::moveRight(){
	if (KeyboardManager::getKeys()->Key_Right) {
	//Lock 
	SDL_SemWait( Lock );
	dynamicBody->ApplyForce(b2Vec2(5000,0),GetPosition(),true);
	//Unlock 
	SDL_SemPost( Lock );
	}
}


b2Vec2 Player::GetPosition() {
	//Lock 
	//SDL_SemWait( Lock );
	return b2Vec2(dynamicBody->GetPosition().x, dynamicBody->GetPosition().y);
	//Unlock 
	//SDL_SemPost( Lock );
}

void Player::Render(SDL_Renderer* gRenderer, b2Vec2 offset) {

	rect.x = dynamicBody->GetPosition().x -(rect.w/2.0f)- offset.x;
	rect.y = dynamicBody->GetPosition().y -(rect.h/2.0f)+ offset.y;
	SDL_Rect h = SDL_Rect();
	h.x =0;
	h.y =0;
	h.w = 165;
	h.h = 230;
	SDL_RenderCopy( gRenderer, m_texture, &h, &rect );
}

void Player::jump(){
	if (KeyboardManager::getKeys()->Key_Up) {
		SDL_SemWait( Lock );
		if(count <=3)
		{
			dynamicBody->ApplyLinearImpulse(b2Vec2(0,-1200), dynamicBody->GetPosition(), true);
			count ++;
		}
		SDL_SemPost( Lock );
	}
}

void Player::Death()
{
	sm->PauseBackground(true);
	sm->PlayDeathSound();
}