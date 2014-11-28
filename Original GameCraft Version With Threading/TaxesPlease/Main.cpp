#include <iostream>
#include <SDL.h>
#include "Box2D\Box2D.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ctime>
#include <SDL_mixer.h>
#include "Game.h"
#include "KeyboardManager.h"
#include "Constants.h"
#include "ContactListener.h"
//Screen dimension constants 
const int SCREEN_WIDTH = 1280; 
const int SCREEN_HEIGHT = 720;
//The window we'll be rendering to 
SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL; 

SDL_Event eHandler;
Game* game;
Constants * c;
void gameLoop();

SDL_Thread* drawMenuThread;
SDL_Thread* drawLevelThread;
SDL_Thread* update;
SDL_sem* drawLock = NULL;

int DrawMenu(void* data) {
	while (c->QUIT) {
		SDL_SemWait( drawLock );
		game->DrawMenu();
		SDL_SemPost( drawLock );
	}
	return 0;
}

int DrawLevel(void* data) {
	while(c->QUIT) {
		SDL_SemWait( drawLock );
		game->DrawLevel();
		SDL_SemPost( drawLock );
	}
	return 0;
}

int Updat(void* data) {
	while(c->QUIT) {
		SDL_SemWait( drawLock );
		game->update(0);
		SDL_SemPost( drawLock );
	}
	return 0;
}


int main(int argc, char **argv){
	c =  new Constants();
	c->QUIT = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Initialize SDL
	if( SDL_Init( SDL_INIT_AUDIO ) < 0 ){
		std::cout <<( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	//Initialize SDL_mixer
	//if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
	//std::cout <<( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	//}
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
	window = SDL_CreateWindow( "TaxesPlease", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 

	//Initialize PNG loading 
	if(!( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG )){ 		
		std::cout <<( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	} 
	TTF_Init();




	b2Vec2 gravity =  b2Vec2(0.0f,9.81f);
	bool doSleep = true;
	b2World* world = new b2World(gravity);
	world->SetContactListener(ContactListener::getListener());
	game = new Game(renderer,world,c);

//	double mClock = SDL_GetTicks();


	drawLock = SDL_CreateSemaphore( 1 );
	drawMenuThread = SDL_CreateThread(DrawMenu, "MenuThread", (void*)0);
	drawLevelThread = SDL_CreateThread(DrawLevel, "LevelThread", (void*)1);
	update = SDL_CreateThread(Updat, "UpdateThread", (void*)2);


	while(c->QUIT){
		KeyboardManager::getKeys()->Update(eHandler);
	//	double deltaTime = SDL_GetTicks() - mClock;
	//	game->update(0);
	//	mClock += deltaTime;
	}
	SDL_Quit();

	return 0;
}