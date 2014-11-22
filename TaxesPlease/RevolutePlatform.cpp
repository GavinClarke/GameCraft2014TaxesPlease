#define PIXELSTOMETRES 1/30.0f
#define METRESTOPIXELS 30
#define TORADIANS (-180/3.1415926536f)

#include "RevolutePlatform.h"

SDL_Point* RevolutePlatform::rotatePoint = new SDL_Point();

RevolutePlatform::RevolutePlatform(b2World* world, SDL_Renderer* gRenderer,b2Vec2 pos1, b2Vec2 pos2)
	:mAnchorPos(pos1),mPlatformPos(pos2)
{
	texture.loadFromFile( "Block.png", gRenderer );
	mAnchorPos *= PIXELSTOMETRES;
	mPlatformPos *= PIXELSTOMETRES;
	myBodyDef.userData = (void*)-7;

	/////////////////////////////////////////////////////////////Anchor
	myBodyDef.type = b2_staticBody;
	b2PolygonShape squareShapeA;
	squareShapeA.SetAsBox((100* PIXELSTOMETRES)/2,(100* PIXELSTOMETRES)/2);

	myBodyDef.position.Set(mAnchorPos.x, mAnchorPos.y);

	fixtureDef.shape = &squareShapeA;
	anchorBody = world->CreateBody( &myBodyDef );
	anchorBody->CreateFixture( &fixtureDef );

	/////////////////////////////////////////////////////////////Platform
	myBodyDef.type = b2_dynamicBody;
	b2PolygonShape squareShapeB;
	squareShapeB.SetAsBox((100* PIXELSTOMETRES)/2,(100* PIXELSTOMETRES)/2);

	myBodyDef.position.Set( mPlatformPos.x, mPlatformPos.y);
	fixtureDef.shape = &squareShapeB;

	world->CreateBody( &myBodyDef );
	platformBody = world->CreateBody( &myBodyDef );
	platformBody->CreateFixture( &fixtureDef );

	/////////////////////////////////////////////////////////////Revolute Joint
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = anchorBody;
	revoluteJointDef.bodyB = platformBody;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0,0);
	revoluteJointDef.localAnchorB.Set(0,0);
	revoluteJoint = (b2RevoluteJoint*)world->CreateJoint( &revoluteJointDef );

	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 20;
	revoluteJointDef.motorSpeed = 360 * TORADIANS; //1 turn per second counter-clockwise
}


RevolutePlatform::~RevolutePlatform(void)
{
}

void RevolutePlatform::Draw(SDL_Renderer* gRenderer, b2Vec2 offset)
{
	//Anchor
	texture.render((anchorBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x,
		-(anchorBody->GetPosition().y * METRESTOPIXELS) - (texture.getHeight() / 2) + offset.y,NULL, 
		anchorBody->GetAngle() * (-180/3.1415926536f), NULL, SDL_FLIP_NONE, gRenderer );

	//Platform
	texture.render((platformBody->GetPosition().x * METRESTOPIXELS) - (texture.getWidth() / 2) - offset.x,
		-(platformBody->GetPosition().y * METRESTOPIXELS) - (texture.getHeight() / 2) + offset.y, NULL, 
		platformBody->GetAngle() * (-180/3.1415926536f), NULL, SDL_FLIP_NONE, gRenderer );


}