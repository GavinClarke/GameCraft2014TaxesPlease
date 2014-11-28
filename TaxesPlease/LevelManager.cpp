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
	
	ticket = new int[4];
	for (int i = 0; i < 4; i++)
	{
		ticket[i] = i;
	}
	lock = SDL_CreateMutex();
	count =new int (0);
	CreateObjects();
	
	
	
	SDL_Rect rect = SDL_Rect();
	rect.x =0;
	rect.y = 650;
	rect.h = 100;
	rect.w = 1280;
	position = b2Vec2(650,100);
	
}

void LevelManager::CreateObjects()
{
	water = new entity(mRenderer,0,ticket,lock);//IMG_LoadTexture(renderer,"images/Background.png");
	water->setTextureName("images/BackGround.png");
	water->setRotation(0.0f);
	water->setImageSourceRect(0, 0, 780, 1280);
	water->LoadImage();
	water->count = count;

	platEntity = new entity(mRenderer, 1, ticket,lock);
	platEntity->setTextureName("images/pipePlatform.png");
	platEntity->setRotation(0.0f);
	platEntity->setImageSourceRect(0, 0, 22, 96);
	platEntity->setSizeRect(0,0,50,800);
	platEntity->LoadImage();
	platEntity->count = count;

	plat2Entity = new entity(mRenderer, 2, ticket,lock);
	plat2Entity->setTextureName("images/pipePlatform.png");
	plat2Entity->setRotation(0.0f);
	plat2Entity->setImageSourceRect(0, 0, 22, 96);
	plat2Entity->setSizeRect(0,0,50,400);
	plat2Entity->LoadImage();
	plat2Entity->count = count;

	plat3Entity = new entity(mRenderer, 3, ticket,lock);
	plat3Entity->setTextureName("images/pipePlatform.png");
	plat3Entity->setRotation(0.0f);
	plat3Entity->setImageSourceRect(0, 0, 22, 96);
	plat3Entity->setSizeRect(0,0,50,400);
	plat3Entity->LoadImage();
	plat3Entity->count = count;

	angEntity = new entity(mRenderer, 4, ticket,lock);
	angEntity->setTextureName("images/pipePlatform.png");
	angEntity->setRotation(-0.5f);
	angEntity->setImageSourceRect(0, 0, 22, 96);
	angEntity->setSizeRect(0,0,25,400);
	angEntity->LoadImage();
	angEntity->count = count;

	
	playEnt = new entity(mRenderer, 4, ticket, lock);
	playEnt->setTextureName("images/player.png");
	playEnt->setRotation(0.0f);
	playEnt->setImageSourceRect(0, 0, player->rect.w, player->rect.h);
	playEnt->setSizeRect(0, 0, player->rect.w, player->rect.h);
	playEnt->LoadImage();
	playEnt->count = count;
}

LevelManager::~LevelManager(void)
{

}

void LevelManager::Update()
{
	player->Update();
	//position.x -= 0.01;
	//position.y+= 0.01;
	platEntity->setSizeRect(plat->staticBody->GetPosition().x-(1750/2.5f),plat->staticBody->GetPosition().y,50,1500);
	plat2Entity->setSizeRect(plat2->staticBody->GetPosition().x,plat2->staticBody->GetPosition().y,50,200);
	plat3Entity->setSizeRect(plat3->staticBody->GetPosition().x  -(500/2.5f),plat3->staticBody->GetPosition().y,50,400);
	angEntity->setSizeRect(angPlat->staticBody->GetPosition().x  -(500/2.5f),angPlat->staticBody->GetPosition().y,25,400);
	water->setSizeRect(0, position.x, position.y, 1280);
	playEnt->setSizeRect(player->dynamicBody->GetPosition().x, player->dynamicBody->GetPosition().y, playEnt->sizeRect.w, playEnt->sizeRect.h);
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
		player->dynamicBody->SetTransform(b2Vec2(50,550),0);
		rect.x =0;
		rect.y = 650;
		rect.h = 100;
		rect.w = 1280;
		position.x = 650;
		position.y = 100;
	}
}

void LevelManager::Draw()
{
	//plat->Draw(mRenderer,b2Vec2(0,0));
	//plat2->Draw(mRenderer,b2Vec2(0,0));
	//plat3->Draw(mRenderer,b2Vec2(0,0));
	//angPlat->Draw(mRenderer,b2Vec2(0,0));
	//player->Render(mRenderer,b2Vec2(0,0));
	//platEntity->Draw();
	//plat2Entity->Draw();
	//plat3Entity->Draw();
	//angEntity->Draw();
	//water->Draw();
	
}