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


void SetupWorld() {
	b2Vec2 gravity(0, -9.81f);
	m_world = new b2World(gravity);
	m_waterWorld = new b2World(gravity);
	m_world->SetContactListener(ContactListener::getListener());
}

void SetupSDL() {
	window = SDL_CreateWindow( "TaxesPlease", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, CONSTANTS::SCREEN_WIDTH,CONSTANTS::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    IMG_Init( IMG_INIT_PNG );
}

void Initialize()
{
	p = new Player(m_world, gRenderer, b2Vec2(0, 600), 50);
	b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH/2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT/2);
	m_levelManager = new LevelManager(m_world,gRenderer,p,offset);
	m_levelManager->Initialize();
	worldPartsStep = m_world->CalculateReasonableParticleIterations(1/30.0f);
	waterPartsStep = m_waterWorld->CalculateReasonableParticleIterations(1/30.0f);
	w = new Water(m_waterWorld, gRenderer);
	m = new Menu(gRenderer);
}

void DrawEntities() {

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( gRenderer );

	if (state==MainMenu) {
		m->Draw();
	} else {
		SDL_RenderCopy( gRenderer, levelTexture, NULL, NULL ); 
		b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH/2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT/2);
		p->Draw( gRenderer, offset );
		w->Draw( gRenderer, offset );
	}
	SDL_RenderPresent( gRenderer );
}

void Quit() {
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer( gRenderer );
	IMG_Quit();
	SDL_Quit();
	isRunning = false;
}

void Update() {
	if (state==MainMenu) {
		DrawEntities();
		if (m->Update() == 0) {
			Quit();
		} else if (m->Update() == 1) {
			state = Play;
		}
	} else {
		m_world->Step(1/30.0f, velocityIterations, positionIterations, worldPartsStep);
		m_waterWorld->Step(1/30.0f, velocityIterations, positionIterations, waterPartsStep);
		DrawEntities();
		b2Vec2 offset = b2Vec2((p->GetPosition().x*METRESTOPIXELS) - CONSTANTS::SCREEN_WIDTH/2, (p->GetPosition().y*METRESTOPIXELS) + CONSTANTS::SCREEN_HEIGHT/2);
		m_levelManager->Update(offset);
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