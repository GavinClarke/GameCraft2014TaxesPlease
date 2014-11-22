#include "Game.h"


Game::Game(SDL_Renderer* renderer,b2World* bworld) : mRenderer(renderer), mWorld(bworld){
	
}


Game::~Game(void){}

void Game::update(double deltaTime){	
	float32 timeStep = deltaTime;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	//mWorld->Step(timeStep, velocityIterations, positionIterations);	

	SDL_RenderClear( mRenderer );

	

	
	if(KeyboardManager::getKeys()->Key_R){
		
	}

	SDL_RenderPresent( mRenderer );
}
