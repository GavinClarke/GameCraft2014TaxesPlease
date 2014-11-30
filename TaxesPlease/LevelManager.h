#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_

#include "Level.h"
#include "Level1.cpp"
#include "Level2.cpp"
#include "Level3.cpp"
#include "Level4.cpp"
#include "Level5.cpp"
#include "Level6.cpp"
#include "Level7.cpp"
#include "Level8.cpp"
#include "Level9.cpp"
#include "Player.h"
#include "CONSTANTS.h"
#include <random>
#include <time.h>
#include "SDL_thread.h"

using namespace std;

class LevelManager{
private:
	b2World* m_world;
	Player* m_player;
	SDL_Renderer* m_renderer;
	Level* m_levels[50];

	Level* m_previousLevel;
	Level* m_currentLevel;
	Level* m_nextLevel1;
	Level* m_nextLevel2;

	SDL_Thread* PreviousLevel;
	SDL_Thread* CurrentLevel;
	SDL_Thread* NextLevel1;
	SDL_Thread* NextLevel2;
	SDL_sem* lock;

	b2Vec2 OSet;

	int m_count;

	Level* GetCurrentLevel();
	Level* CreateRandomLevel();
public:
	LevelManager(b2World*, SDL_Renderer*, Player*,b2Vec2 offset);
	~LevelManager();
	void Initialize();
	void Update(b2Vec2 os);
	int UpdatePrevLevel(void*);
	int UpdateCurLevel(void*);
	int UpdateNextLevel1(void*);
	
};

#endif