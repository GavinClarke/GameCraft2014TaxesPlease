#include "Level.h"
#include "BasicPlatform.h"
#include "PrismaticPlatform.h"
class Level7 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
	PrismaticPlatform* pp;
	PrismaticPlatform* pp2;
public:
	Level7(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		pp = new PrismaticPlatform(w,r,300,450,500 - (count * CONSTANTS::LEVEL_HEIGHT),30);
		pp2 = new PrismaticPlatform(w,r,200,400,200 - (count * CONSTANTS::LEVEL_HEIGHT),30);
	}

	~Level7()
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
		pp->Draw(r,offset);
		pp2->Draw(r,offset);
	}
};