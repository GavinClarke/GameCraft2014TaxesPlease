#include "Level.h"
#include "BasicPlatform.h"
#include "FallingPlatform.h"

class Level5 : public Level
{
private:
	std::vector<FallingPlatform*> m_fallingPlatforms;
	std::vector<BasicPlatform*> m_platforms;
public:
	Level5(int count, b2World* w, SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0 ,800 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_fallingPlatforms.push_back(new FallingPlatform(w,r,b2Vec2(410, 540 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_fallingPlatforms.push_back(new FallingPlatform(w,r,b2Vec2(750, 380 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_fallingPlatforms.push_back(new FallingPlatform(w,r,b2Vec2(300, 100 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
	}

	~Level5()
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~BasicPlatform();
		}
			for (int i = 0; i < m_platforms.size(); i++)
		{
			m_fallingPlatforms[i]->~FallingPlatform();
		}
	}

	void Level::Update(Player* p)
	{			
		for (int i = 0; i < m_fallingPlatforms.size(); i++)
		{
			m_fallingPlatforms[i]->Update();
		}
	}

	void Level::Render(SDL_Renderer* r, b2Vec2 offset)
	{		
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}
		for (int i = 0; i <m_fallingPlatforms.size(); i++)
		{
			m_fallingPlatforms[i]->Draw(r,offset);
		}
	}
};