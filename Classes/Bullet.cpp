#include "Bullet.h"
#include "Define.h"
#include "InGameScene.h"

USING_NS_CC;
Bullet::Bullet(Layer* layer, Sprite *sprite, int owner, Sprite* spriteOwner)
{
	mSpriteOwner = spriteOwner;
	mSprite = sprite;
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(40, 40), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(owner);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	setAlive(false);
	layer->addChild(mSprite);
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(int runStep)
{
	if (isAlive())
	{
		if (mIsRunLeftToRight)
		{
			setPosition(getPosition() + Vec2(runStep, 0));
		}
		else
		{
			setPosition(getPosition() - Vec2(runStep, 0));
		}
		Rect rect;
		if (mSpriteOwner->getPosition().x <= 400)
		{
			rect = Rect(0, 0, 800, 10000);
		}
		else
		{
			rect = Rect(mSpriteOwner->getPosition().x - 400, 0, 800, 10000);
		}
		
		//out of screen
		if (!rect.containsPoint(getPosition()))
		{
			setAlive(false);
		}
		log("mc  %f", mSpriteOwner->getPosition().x);
	}
}

void Bullet::explode(bool isRight)
{
	mIsRunLeftToRight = isRight;
	if (isRight)
	{
		mSprite->setFlippedX(false);
	}
	else
	{
		mSprite->setFlippedX(true);
	}

}