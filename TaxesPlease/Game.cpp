#include "Game.h"


Game::Game(SDL_Renderer* renderer,b2World* bworld,Constants * con) : mRenderer(renderer), mWorld(bworld){
	c = con;
	menu = new Menu(renderer,c);
	runGame = false;
	level = new LevelManager(bworld,renderer);
	
}


Game::~Game(void){}

void Game::update(double deltaTime){	
	float32 timeStep = deltaTime;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mWorld->Step(timeStep, velocityIterations, positionIterations);	

	SDL_RenderClear( mRenderer );
	int i=0;
	if(runGame == false)
	{
	  i = menu->Update();
	}
	else
	{
		level->Update();
	}
	
	if(i == 1)
	{
		runGame = true;
	}
	if(KeyboardManager::getKeys()->Key_R){
		c->QUIT = false;
	}

	if(runGame == false)
	{
		menu->Draw();
	}
	else
	{
		level->Draw();
	}
	
	SDL_RenderPresent( mRenderer );
}
