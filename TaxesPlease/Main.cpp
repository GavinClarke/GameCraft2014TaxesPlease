#include <iostream>
#include <SDL.h>
#include "Box2D\Box2D.h"
#include "Pickup.h"
#include <SDL_thread.h>
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
const int size = 3;
SDL_Event eHandler;
Game* game;
Constants * c;
Pickup *pUps[size];
int tickets[size];
int entering[size];
SDL_Thread *thread[size];
void gameLoop();
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
SDL_sem *sem;

int Thread1(void* ptr)
{
	counter1++;
	if (counter1 >= 100)
	{
		SDL_SemWait(sem);
		counter1 = 0;
		b2Vec2 temp = pUps[0]->GetBody()->GetPosition();
		temp.y = temp.y * -1;
		pUps[0]->GetBody()->SetTransform(temp, 0);
		SDL_SemPost(sem);
	}
	
	return 1;
}
int Thread2(void* ptr)
{
	counter2++;
	if (counter2 >= 100)
	{
		SDL_SemWait(sem);
		counter2 = 0;
		b2Vec2 temp = pUps[1]->GetBody()->GetPosition();
		temp.y = temp.y * -1;
		pUps[1]->GetBody()->SetTransform(temp, 0);
		SDL_SemPost(sem);
	}
	return 2;
}
int Thread3(void* ptr)
{
	counter3++;
	if (counter3 >= 100)
	{
		SDL_SemWait(sem);
		counter3 = 0;
		b2Vec2 temp = pUps[2]->GetBody()->GetPosition();
		temp.y = temp.y * -1;
		pUps[2]->GetBody()->SetTransform(temp, 0);
		SDL_SemPost(sem);
	}
	return 3;
}






int main(int argc, char **argv){
	c =  new Constants();
	sem = SDL_CreateSemaphore(3);
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
	pUps[0] = new Pickup();
	pUps[1] = new Pickup();
	pUps[2] = new Pickup();
	pUps[0]->InitPickup(world, b2Vec2(20,20), renderer);
	pUps[1]->InitPickup(world, b2Vec2(70,20), renderer);
	pUps[2]->InitPickup(world, b2Vec2(120,20), renderer);

	game = new Game(renderer,world,c);

	thread[0] = SDL_CreateThread(Thread1, NULL, NULL);
	thread[1] = SDL_CreateThread(Thread2, NULL, NULL);
	thread[2] = SDL_CreateThread(Thread3, NULL, NULL);

	double mClock = SDL_GetTicks();
	while(c->QUIT){
		KeyboardManager::getKeys()->Update(eHandler);
		double deltaTime = SDL_GetTicks() - mClock;
		pUps[0]->Draw(renderer);
		pUps[1]->Draw(renderer);
		pUps[2]->Draw(renderer);
		game->update(deltaTime/1000.0f);
		
		mClock += deltaTime;
	}
	SDL_Quit();

	return 0;
}