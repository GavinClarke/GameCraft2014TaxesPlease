#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Box2D\Box2D.h"
#include "KeyboardManager.h"
#include "ContactListener.h"
#include "LevelManager.h"
#include "Player.h"
#include "Water.h"
#include "Menu.h"


//Program Variables
bool isRunning = true;
bool isMouseDown = false;

//Box2D Variables
b2World* m_world;
b2World* m_waterWorld;
int32 velocityIterations = 8;
int32 positionIterations = 3;

//SDL Variables
SDL_Window* window;
SDL_Renderer* gRenderer;
SDL_Event e;

LevelManager* m_levelManager;
Player* p;

enum States{MainMenu,Play};
States state = MainMenu;
SDL_Texture* levelTexture;

Water* w;

float worldPartsStep;
float waterPartsStep;

Menu* m;
SDL_Thread* drawMenuThread;
SDL_Thread* drawWorldThread;
SDL_Thread* drawWaterThread;
SDL_sem* drawLock = NULL;

void SetupWorld() {
	b2Vec2 gravity(0, -9.81f);
	m_world = new b2World(gravity);
	m_waterWorld = new b2World(gravity);
	m_world->SetContactListener(ContactListener::getListener());
}

int DrawMenu(void* data) {
	while (isRunning) {
	SDL_SemWait( drawLock );
		if (state==MainMenu) {
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			m->Draw();
			SDL_RenderPresent( gRenderer );
		}
	SDL_SemPost( drawLock );
	}
	return 0;
}

int DrawWorld(void* data) {
	while (isRunning) {
		SDL_SemWait( drawLock );
		if (state!=MainMenu) {
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			//SDL_RenderClear( gRenderer );
			b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH/2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT/2);
			m_levelManager->Render(gRenderer, offset);
			p->Draw( gRenderer, offset );
			SDL_RenderPresent( gRenderer );
		}
		SDL_SemPost( drawLock );
	}
	return 0;
}

int DrawWater(void* data) {
	while (isRunning) {
		SDL_SemWait( drawLock );
		if (state!=MainMenu) {
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );
			b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH/2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT/2);
			w->Draw( gRenderer, offset );
			//SDL_RenderPresent( gRenderer );
		}
		SDL_SemPost( drawLock );
	}
	return 0;
}

void SetupSDL() {
	window = SDL_CreateWindow( "TaxesPlease", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONSTANTS::SCREEN_WIDTH,CONSTANTS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    IMG_Init( IMG_INIT_PNG );
}

void Initialize()
{
	p = new Player(m_world, gRenderer, b2Vec2(0, 600), 50);
	m_levelManager = new LevelManager(m_world,gRenderer,p);
	m_levelManager->Initialize();
	worldPartsStep = m_world->CalculateReasonableParticleIterations(1/30.0f);
	waterPartsStep = m_waterWorld->CalculateReasonableParticleIterations(1/150.0f);
	w = new Water(m_waterWorld, gRenderer);
	m = new Menu(gRenderer);
	drawLock = SDL_CreateSemaphore( 1 );
	drawMenuThread = SDL_CreateThread(DrawMenu, "MenuThread", (void*)0);
	drawWorldThread = SDL_CreateThread(DrawWorld, "WorldThread", (void*)1);
	drawWaterThread = SDL_CreateThread(DrawWater, "WaterThread", (void*)2);
}



void Quit() {
	isRunning = false;
	SDL_WaitThread( drawMenuThread, NULL );
    SDL_WaitThread( drawWorldThread, NULL );
	SDL_WaitThread( drawWaterThread, NULL );
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( gRenderer );
	IMG_Quit();
	SDL_Quit();
}

void Update() {
	if (state==MainMenu) {
		//DrawEntities();
		if (m->Update() == 0) {
			Quit();
		} else if (m->Update() == 1) {
			state = Play;
		}
	} else {
		m_world->Step(1/150.0f, velocityIterations, positionIterations, worldPartsStep);
		m_waterWorld->Step(1/150.0f, velocityIterations, positionIterations, waterPartsStep);
		//DrawEntities();

		m_levelManager->Update();
		p->Update();

		if (KeyboardManager::instance()->IsKeyDown(KeyboardManager::ESC))
			Quit();

		if (p->GetPosition().y < w->getYPos()) {
			Quit();
		}
	}
}

int main( int argc, char* args[] ) {
	SetupWorld();
	SetupSDL();
	Initialize();
	while (isRunning) Update();
	return 0;
}