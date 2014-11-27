#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "Water.h"

Water::Water(b2World* world, SDL_Renderer* gRenderer) {
	mTexture.loadFromFile( "waterParticle.png", gRenderer );

	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;
	myBodyDef.position.Set(540*PIXELSTOMETRES, -1080*2*PIXELSTOMETRES);
	myBodyDef.gravityScale = 0;
	dynamicBody = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(1100*PIXELSTOMETRES, 1);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 10;
	fixtureDef.filter.groupIndex = -100;
	dynamicBody->CreateFixture(&fixtureDef);

	myBodyDef.fixedRotation = true;
	myBodyDef.position.Set(1540*PIXELSTOMETRES, -1080*2*PIXELSTOMETRES);
	myBodyDef.gravityScale = 0;
	myBodyDef.angle = 1.57f;
	leftBody = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(1000*PIXELSTOMETRES, 1);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 10000;
	fixtureDef.filter.groupIndex = -100;
	leftBody->CreateFixture(&fixtureDef);

	myBodyDef.fixedRotation = true;
	myBodyDef.position.Set(-540*PIXELSTOMETRES, -1080*2*PIXELSTOMETRES);
	myBodyDef.gravityScale = 0;
	myBodyDef.angle = 1.57f;
	rightBody = world->CreateBody(&myBodyDef);
	polyShape.SetAsBox(1000*PIXELSTOMETRES, 1);
	fixtureDef.shape = &polyShape;
	fixtureDef.density = 10000;
	fixtureDef.filter.groupIndex = -100;
	rightBody->CreateFixture(&fixtureDef);

	b2Vec2 a = dynamicBody->GetPosition();

	b2ParticleSystemDef pD;
	pD.gravityScale = 0.4f;
	//pD.density = 0.1f;
	pD.radius = (mTexture.getWidth()/2) * PIXELSTOMETRES;
	//pD.dampingStrength = 0.2f;
	pS = world->CreateParticleSystem(&pD);

	b2ParticleDef pd1;
	pd1.flags = b2_elasticParticle;
	for (int i = 0; i < 300; i+=8) {
		for (int j = 0; j < 300; j+=8) {
			pd1.position.Set(i*PIXELSTOMETRES, (-j*PIXELSTOMETRES)-40);
			pS->CreateParticle(pd1);
		}
	}
}

void Water::Draw(SDL_Renderer* gRenderer, b2Vec2 offset) { 
	b2Vec2* parts = pS->GetPositionBuffer();
	for (int i = 0; i < pS->GetParticleCount(); ++i) {
		mTexture.render((parts[i].x * METRESTOPIXELS) - (mTexture.getWidth() / 2) - offset.x,
			-(parts[i].y * METRESTOPIXELS) - (mTexture.getHeight() / 2) + offset.y, NULL, 
			0, NULL, SDL_FLIP_NONE, gRenderer );
		
	}
//	pS->ApplyLinearImpulse(0,5000,b2Vec2(0,200));
	dynamicBody->SetLinearVelocity(b2Vec2(0, 2.5f));
	leftBody->SetLinearVelocity(b2Vec2(0, 2.5f));
	rightBody->SetLinearVelocity(b2Vec2(0, 2.5f));
}

float Water::getYPos() {
	return dynamicBody->GetPosition().y + 12.5;
}