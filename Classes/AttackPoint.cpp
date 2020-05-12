#include "AttackPoint.h"

AttackPoint::AttackPoint(Layer* layer, int type, int category, int range) 
{
	mSprite = Sprite::create("1.png");
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	mPhysicsBody = PhysicsBody::createBox(Size(2, range), PhysicsMaterial(1, 0, 1));
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(type);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	mSprite->setVisible(false);
	mIsALive = false;
	mPhysicsBody->setEnabled(false);

	layer->addChild(mSprite);
}

void AttackPoint::rotateToAttack(bool isRight) 
{
	RotateBy* rotate;
	if (mSprite->getNumberOfRunningActions() == 0)
	{
		if (isRight) 
		{
			rotate = RotateBy::create(0.63f, 180);
		}
		else
		{
			rotate = RotateBy::create(0.63f, -180);
		}
		mSprite->runAction(rotate);
		mSprite->getPhysicsBody()->setEnabled(true);
		mIsALive = true;
	}
}

void AttackPoint::isSkillFinish(Vec2 position) 
{
	//log("atkP  %f %f", position.x, position.y);
	mSprite->setPosition(position);
	if (mSprite->getNumberOfRunningActions() == 0 && mIsALive == true)
	{
		mSprite->getPhysicsBody()->setEnabled(false);
		auto rotate = RotateBy::create(0.01f, 180);
		mIsALive = false;
		isFinish = true;
		mSprite->runAction(rotate);
	}
	else isFinish = false;
}

bool AttackPoint::isAttackFinish() 
{
	return this->isFinish;
}