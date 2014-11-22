#include "Level.h"
#include "BasicPlatform.h"
#include "FallingPlatform.h"

class Level10 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
	std::vector<FallingPlatform*> m_fallingPlatforms;

public:
	Level10(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_fallingPlatforms.push_back(new FallingPlatform(w,r,b2Vec2(300,600 -  (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(450 ,400 -  (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(600 ,200 -  (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
	}

	~Level10()
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~BasicPlatform();
		}
		for (int i = 0; i < m_fallingPlatforms.size(); i++)
		{
			
			m_fallingPlatforms[i]->~FallingPlatform();
		}
	}

	void Level::Update(Player* p){
		for (int i = 0; i < m_fallingPlatforms.size(); i++)
		{
			m_fallingPlatforms[i]->Update();
		}
	}

	void Level::Render(SDL_Renderer* r, b2Vec2 offset){
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}

		for (int i = 0; i < m_fallingPlatforms.size(); i++)
		{
			m_fallingPlatforms[i]->Draw(r,offset);
		}
	}
};