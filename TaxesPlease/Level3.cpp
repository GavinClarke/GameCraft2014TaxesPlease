#include "Level.h"
#include "OneWayPlatform.h"

class Level3 : public Level
{
private:
	std::vector<OneWayPlatform*> m_platforms;
public:
	Level3(int count, b2World* w, SDL_Renderer* r)
	{
		m_platforms.push_back(new OneWayPlatform(w,r,b2Vec2(100 ,800 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_platforms.push_back(new OneWayPlatform(w,r,b2Vec2(300,600 -  (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_platforms.push_back(new OneWayPlatform(w,r,b2Vec2(450 ,400 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
		m_platforms.push_back(new OneWayPlatform(w,r,b2Vec2(600 ,200 - (count * CONSTANTS::LEVEL_HEIGHT)),b2Vec2(300,60),0));
	}

	~Level3()
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~OneWayPlatform();
		}
	}

	void Level::Update(Player* p)
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->CanCollideWithPlayer(p->CanCollideWithOneWayPlatforms(m_platforms[i]->GetPosition().y));
		}
	}

	void Level::Render(SDL_Renderer* r, b2Vec2 offset)
	{
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}
	}
};