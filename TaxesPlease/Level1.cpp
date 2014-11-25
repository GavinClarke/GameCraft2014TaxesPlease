#include "Level.h"
#include "BasicPlatform.h"
//#include "Barrier.h"

class Level1 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
public:
	Level1(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(300,500 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(100,300 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
	}

	~Level1()
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~BasicPlatform();
		}
	}

	void Level::Update(Player* p){
	}

	void Level::Render(SDL_Renderer* r, b2Vec2 offset){

	//	m_barrier->Draw(r, offset);
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}
	}
};