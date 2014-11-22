#include "LevelManager.h"


LevelManager::LevelManager(b2World * world,SDL_Renderer * renderer)
{
	mRenderer = renderer;
	plat = new BasicPlatform(world,renderer,b2Vec2(0,600),b2Vec2(800,50),0);
	player = new Player(world,renderer,b2Vec2(0,550),b2Vec2(50,50));
}


LevelManager::~LevelManager(void)
{

}

void LevelManager::Update()
{
	player->Update();
}

void LevelManager::CreatePlatForms()
{

}

void LevelManager::Draw()
{
	plat->Draw(mRenderer,b2Vec2(0,0));
	player->Render(mRenderer,b2Vec2(0,0));
}