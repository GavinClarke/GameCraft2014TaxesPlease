#include "Level.h"
#include "BasicPlatform.h"
#include "RevolutePlatforms.h"
class Level8 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
	RevolutePlatforms* rp;
public:
	Level8(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		rp = new RevolutePlatforms(w,r,b2Vec2(700,400 -  (count * CONSTANTS::LEVEL_HEIGHT)),300, -15);
	}

	~Level8()
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
		rp->Draw(r,offset);
	}
};