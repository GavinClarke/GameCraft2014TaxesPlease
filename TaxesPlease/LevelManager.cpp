#define  METRESTOPIXELS 30
#define PIXELSTOMETRES 1/30.0f

#include "LevelManager.h"

using namespace std;


LevelManager::LevelManager(b2World* w, SDL_Renderer* r,Player* p,b2Vec2 offset)
{
	m_world = w;
	m_player = p;
	m_renderer = r;
	OSet = offset;
	srand ( time(NULL) );
}

LevelManager::~LevelManager()
{
}

void LevelManager::Initialize()
{
	m_count = 0;
	for (int i = 0; i < 4; i++)
	{
		m_levels[i] = CreateRandomLevel();
		m_count++;  
	}

	m_previousLevel =  m_levels[0];
	m_currentLevel = m_levels[1];
	m_nextLevel1 = m_levels[2];
	m_nextLevel2 = m_levels[3];

	lock = SDL_CreateSemaphore( 1 );
	PreviousLevel = SDL_CreateThread(UpdatePrevLevel, "PreviousLevelThread", (void*)0);
	CurrentLevel = SDL_CreateThread(UpdateCurLevel, "CurrentLevelThread", (void*)1);
	m_nextLevel1 = SDL_CreateThread(UpdateNextLevel1, "NextLevel1Thread", (void*)2);
	
}

int LevelManager::UpdatePrevLevel(void* data){
	SDL_SemWait( lock );
	m_previousLevel->Update(m_player);
	m_previousLevel->Render(m_renderer,OSet);
	SDL_SemPost( lock );
	
}
int LevelManager::UpdateCurLevel(void* data){
	SDL_SemWait( lock );
	m_currentLevel->Update(m_player);
	m_currentLevel->Render(m_renderer,OSet);
	SDL_SemPost( lock );
}
int LevelManager::UpdateNextLevel1(void* data){
	SDL_SemWait( lock );
	m_nextLevel1->Update(m_player);
	m_nextLevel1->Render(m_renderer,OSet);
	SDL_SemPost( lock );
}


void LevelManager::Update(b2Vec2 offset){
	OSet = offset;
	if(m_nextLevel1 == GetCurrentLevel())
	{
		m_previousLevel->~Level();
		
		m_previousLevel = m_currentLevel;
		m_currentLevel = m_nextLevel1;
		m_nextLevel1 = m_nextLevel2;
		m_nextLevel2 = CreateRandomLevel();
		m_count++;
	}

	/*m_previousLevel->Update(m_player);
	m_currentLevel->Update(m_player);
	m_nextLevel1->Update(m_player);
	m_nextLevel2->Update(m_player);*/
}


Level* LevelManager::GetCurrentLevel()
{
	if (m_player->GetPosition().y * METRESTOPIXELS < (m_count -3) * CONSTANTS::LEVEL_HEIGHT)
	{
		return m_currentLevel;
	}
	else if(m_player->GetPosition().y * METRESTOPIXELS > (m_count  -3) * CONSTANTS::LEVEL_HEIGHT)
	{
		return m_nextLevel1;
	}
}

Level* LevelManager::CreateRandomLevel()
{
	int newLevel = rand() % 9;

	if (newLevel == 0)
	{
		return new Level1(m_count,m_world,m_renderer);
	}
	else if (newLevel == 1)
	{
		return new Level2(m_count,m_world,m_renderer);
	}
	else if (newLevel == 2)
	{
		return new Level3(m_count,m_world,m_renderer);
	}
	else if (newLevel == 3)
	{
		return new Level4(m_count, m_world, m_renderer);
	}	
	else if (newLevel == 4)
	{
		return new Level5(m_count, m_world, m_renderer);
	}
	else if (newLevel == 5)
	{
        return new Level6(m_count,m_world,m_renderer);
	}
	else if (newLevel == 6)
	{
		return new Level7(m_count,m_world,m_renderer);
	}
	else if (newLevel == 7)
	{
		return new Level8(m_count,m_world,m_renderer);
	}
	else if (newLevel == 8)
	{
		return new Level9(m_count, m_world, m_renderer);
	}	

}