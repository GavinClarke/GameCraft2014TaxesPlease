#ifndef FALLINGPLATFORM_H
#define FALLINGPLATFORM_H

#include "Box2D\Box2D.h"
#include "LTexture.h"
#include "KeyboardManager.h"
#include "ObjectFactory.h"

//Platform will need its position to be inherited from Base platform
class FallingPlatform // :BasePlatform
{
public:
	FallingPlatform();
	FallingPlatform(b2World* world, SDL_Renderer* renderer,b2Vec2 position, float angle);
	~FallingPlatform();
	
	void Draw(SDL_Renderer* renderer, b2Vec2);

	void Update();

	//gets and sets
	b2Fixture* GetFixture();
	void SetFixture(b2Fixture *fixture);

private:
	void CheckPlayerCollision();
	void CheckBombCollision();
	void DropPlatform(bool collided);
	//Box2d varibles
	b2World* m_world;
	SDL_Renderer* m_renderer ;
	b2Body* m_DynamicBody ;
	b2BodyDef m_BodyDef;
	b2PolygonShape m_platformShape;
	b2Fixture * m_fixture;
	b2FixtureDef m_fixtureDef;
	float m_Width;
	float m_Height;
	b2Vec2 dimensions;
		b2Vec2 mSize;
	SDL_Texture *m_texture;

	//Falling varibles
	bool collided;


};


#endif