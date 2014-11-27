#include "Level.h"
#include "BasicPlatform.h"
#include "Spinner.h"
class Level9 : public Level
{
private:
	std::vector<BasicPlatform*> m_platforms;
	Spinner * m_spinner;
public:
	Level9(int count, b2World * w,SDL_Renderer* r)
	{
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(0,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_platforms.push_back(new BasicPlatform(w,r,b2Vec2(900,800 -  (count * CONSTANTS::LEVEL_HEIGHT)),0));
		m_spinner = new Spinner(w,r, b2Vec2(300, 400-  (count * CONSTANTS::LEVEL_HEIGHT)),-30);
	}

	~Level9()
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
		m_spinner->Draw(r,offset);
	}
};