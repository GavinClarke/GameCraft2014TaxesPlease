#include "Level.h"
#include "BasicPlatform.h"
//#include "PoolPlatform.h"
//#include "Pulley.h"

class Level5 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
public:
	Level5(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(100,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(600,600 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(400,300 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
	}

	~Level5()
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~BasicPlatform();
		}
	}

	void Level::Update(Player* p){
	}

	void Level::Render(SDL_Renderer* r, b2Vec2 offset){
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}
	}
};