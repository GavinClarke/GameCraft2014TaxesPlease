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

int LoadPipeImage(void * data)
{
	bool once = false;
	while(true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->platEntity->LoadImage("images/pipePlatform.png",game->level->platEntity);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
	}
	return 0;
}
int LoadPipe2Image(void * data)
{
	bool once = false;
	while(true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->plat2Entity->LoadImage("images/pipePlatform.png",game->level->plat2Entity);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
	}
	return 0;
}
int LoadPipe3Image(void * data)
{
	bool once = false;
	while(true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->plat3Entity->LoadImage("images/pipePlatform.png",game->level->plat3Entity);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
	}
	return 0;
}
int LoadPipe4Image(void * data)
{
	bool once = false;
	while(true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->angEntity->LoadImage("images/pipePlatform.png",game->level->angEntity);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
	}
	return 0;
}

int LoadPlayerImage(void * data)
{
	bool once = false;
	while (true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->playEnt->LoadImage("images/player.png",game->level->playEnt);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
	}
	return 0;
}
int LoadWaterImage(void * data)
{
	bool once = false;
	while (true)
	{
		if(game->level->canLoadImages == true)
		{
			game->level->water->LoadImage("images/BackGround.png",game->level->water);
			if(once == false)
			{
				game->level->count++;
				once = true;
			}
		}
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

	double mClock = SDL_GetTicks();
	SDL_Thread * thread = SDL_CreateThread(&LoadWaterImage, NULL, NULL);
	SDL_Thread * thread2 = SDL_CreateThread(&LoadPlayerImage, NULL, NULL);
	SDL_Thread * thread3 = SDL_CreateThread(&LoadPipeImage, NULL, NULL);
	SDL_Thread * thread4 = SDL_CreateThread(&LoadPipe2Image, NULL, NULL);
	SDL_Thread * thread5 = SDL_CreateThread(&LoadPipe3Image, NULL, NULL);
	SDL_Thread * thread6 = SDL_CreateThread(&LoadPipe4Image, NULL, NULL);
	while(c->QUIT){
		//thread->join();
		KeyboardManager::getKeys()->Update(eHandler);
		double deltaTime = SDL_GetTicks() - mClock;
		game->update(deltaTime/1000.0f);
		mClock += deltaTime;
	}
	SDL_Quit();

	return 0;
}