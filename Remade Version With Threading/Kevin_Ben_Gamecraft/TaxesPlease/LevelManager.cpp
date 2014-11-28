#define  METRESTOPIXELS 30
#define PIXELSTOMETRES 1/30.0f

#include "LevelManager.h"

using namespace std;

LevelManager::LevelManager(b2World* w, SDL_Renderer* r,Player* p)
{
	m_world = w;
	m_player = p;
	m_renderer = r;
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
}

void LevelManager::Update(){
	
	if(m_nextLevel1 == GetCurrentLevel())
	{
		m_previousLevel->~Level();
		
		m_previousLevel = m_currentLevel;
		m_currentLevel = m_nextLevel1;
		m_nextLevel1 = m_nextLevel2;
		m_nextLevel2 = CreateRandomLevel();
		m_count++;
	}

	m_previousLevel->Update(m_player);
	m_currentLevel->Update(m_player);
	m_nextLevel1->Update(m_player);
	m_nextLevel2->Update(m_player);
}

void LevelManager::Render(SDL_Renderer* r, b2Vec2 offset){
	
	m_previousLevel->Render(r,offset);
	m_currentLevel->Render(r,offset);
	m_nextLevel1->Render(r,offset);
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