#include "FlyGround.h"
#include "Define.h"
USING_NS_CC;

FlyGround::FlyGround(Layer* layer, int type, float mMinPos, float mMaxPos)
{

	groundType = 1;
	minPos = mMinPos;
	maxPos = mMaxPos;
	if (type == 1)
	{
		mSprite = Sprite::create("ufo.png");
		mSprite->setAnchorPoint(Vec2(0.5, 0));
		mSprite->setScale(0.25f);
	}
	else
	{
		mSprite = Sprite::create("elevator.png");
		mSprite->setAnchorPoint(Vec2(0, 0));
		mSprite->setScale(0.8f);
	}
	

	//Physics body
	mPhysicsBody = PhysicsBody::createEdgeBox(mSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f), 1);
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setDynamic(false);
	mPhysicsBody->setGravityEnable(false);

	mPhysicsBody->setMass(5);

	mPhysicsBody->setCollisionBitmask(Model::BITMASK_GROUND);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);
}

FlyGround::~FlyGround()
{
}

void FlyGround::update()
{
	if (groundType == GO_UP_DOWN) 
	{
		if (mSprite->getPosition().y <= minPos) 
		{
			isUp = true;
		}
		else if (mSprite->getPosition().y >= maxPos) 
		{
			isUp = false;
		}

		//up
		if (isUp)
		{
			mPhysicsBody->setVelocity(Vec2(0, SPEED_FALL + 40));
		}
		// down
		else 
		{
			mPhysicsBody->setVelocity(Vec2(0, -SPEED_FALL));
		}
	}
	else if (groundType == GO_RIGHT_LEFT) 
	{
		if (mSprite->getPosition().x <= minPos) 
		{
			isUp = true;
		}
		else if (mSprite->getPosition().x >= maxPos) 
		{
			isUp = false;
		}
		//up
		if (isUp)
		{
			mPhysicsBody->setVelocity(Vec2(SPEED_FALL, 0));
		}
		// down
		else
		{
			mPhysicsBody->setVelocity(Vec2(-SPEED_FALL, 0));
		}
	}
}

int FlyGround::getType() 
{
	return groundType;
}