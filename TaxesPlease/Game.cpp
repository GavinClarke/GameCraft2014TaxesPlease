#include "Game.h"


Game::Game(SDL_Renderer* renderer,b2World* bworld,Constants * con) : mRenderer(renderer), mWorld(bworld){
	c = con;
	menu = new Menu(renderer,c);
}


Game::~Game(void){}

void Game::update(double deltaTime){	
	float32 timeStep = deltaTime;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mWorld->Step(timeStep, velocityIterations, positionIterations);	

	SDL_RenderClear( mRenderer );

	
	menu->Update();
	
	
	if(KeyboardManager::getKeys()->Key_R){
		c->QUIT = false;
	}
	menu->Draw();
	SDL_RenderPresent( mRenderer );
}
