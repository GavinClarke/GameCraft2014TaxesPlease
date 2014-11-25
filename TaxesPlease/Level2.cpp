#include "Level.h"
#include "BasicPlatform.h"
//#include "Pulley.h"
#include "AnglePlatform.h"

class Level2 : public Level
{
	std::vector<BasicPlatform*> m_platforms;

	AnglePlatform* m_anglePlatform;
	AnglePlatform* m_anglePlatform1;
//	Pulley* m_pulley;
public:
	Level2(int count, b2World * w,SDL_Renderer* r)
	{
		m_anglePlatform = new AnglePlatform(w, r, b2Vec2(500, 270-  (count * CONSTANTS::LEVEL_HEIGHT)), 0.5f);
		m_anglePlatform1 = new AnglePlatform(w, r, b2Vec2(-100, 500-  (count * CONSTANTS::LEVEL_HEIGHT)), -0.5f);
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
	}

	~Level2(){
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->~BasicPlatform();
		}
	}

	void Level::Update(Player* p){

	}

	void Level::Render(SDL_Renderer* r,b2Vec2 offset){
		for (int i = 0; i < m_platforms.size(); i++)
		{
			m_platforms[i]->Draw(r,offset);
		}
		m_anglePlatform->Draw(r,offset);
		m_anglePlatform1->Draw(r,offset);
	//	m_pulley->Draw(r,offset);
	}
};