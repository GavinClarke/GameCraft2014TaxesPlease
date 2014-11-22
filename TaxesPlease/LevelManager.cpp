#include "LevelManager.h"


LevelManager::LevelManager(b2World * world,SDL_Renderer * renderer)
{
	mRenderer = renderer;
	plat = new BasicPlatform(world,renderer,b2Vec2(0,600),b2Vec2(800,50),0);
	plat2 = new BasicPlatform(world,renderer,b2Vec2(0,350),b2Vec2(200,50),0);
	plat3 = new BasicPlatform(world,renderer,b2Vec2(640,250),b2Vec2(200,50),0);
	angPlat = new AnglePlatform(world,renderer,b2Vec2(640,400),b2Vec2(200,25),-0.5);
	player = new Player(world,renderer,b2Vec2(50,550),b2Vec2(25,25));
	Cam = b2Vec2(player->GetPosition().x - 640,player->GetPosition().y - 360); 
	
	water = IMG_LoadTexture(renderer,"images/Background.png");
	SDL_Rect rect = SDL_Rect();
	rect.x =0;
	rect.y = 500;
	rect.h = 100;
	rect.w = 1280;
	position = b2Vec2(650,100);
}


LevelManager::~LevelManager(void)
{

}

void LevelManager::Update()
{
	player->Update();
	position.x -= 0.01;
	position.y+= 0.01;
	CollisionWithWater();
}

void LevelManager::CreatePlatForms()
{

}

void LevelManager::CollisionWithWater()
{
	if(player->GetPosition().y > position.x)
	{
		player->Death();
	}
}

void LevelManager::Draw()
{
	plat->Draw(mRenderer,b2Vec2(0,0));
	plat2->Draw(mRenderer,b2Vec2(0,0));
	plat3->Draw(mRenderer,b2Vec2(0,0));
	angPlat->Draw(mRenderer,b2Vec2(0,0));
	player->Render(mRenderer,b2Vec2(0,0));

	rect.x =0;
	rect.y = position.x;
	rect.h = position.y;
	rect.w = 1280;
	SDL_RenderCopy(mRenderer,water,NULL,&rect);
}