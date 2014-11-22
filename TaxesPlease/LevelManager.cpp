#include "LevelManager.h"


LevelManager::LevelManager(b2World * world,SDL_Renderer * renderer)
{
	mRenderer = renderer;
	plat = new BasicPlatform(world,renderer,b2Vec2(0,600),b2Vec2(800,50),0);
	angPlat = new AnglePlatform(world,renderer,b2Vec2(640,400),b2Vec2(200,25),-0.5);
	player = new Player(world,renderer,b2Vec2(50,550),b2Vec2(25,25));
	Cam = b2Vec2(player->GetPosition().x - 640,player->GetPosition().y - 360); 
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
	angPlat->Draw(mRenderer,b2Vec2(0,0));
	player->Render(mRenderer,b2Vec2(0,0));
	rightWall->Draw(mRenderer,b2Vec2(0,0));
}