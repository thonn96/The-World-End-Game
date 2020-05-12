#include "Fireball.h"
#include "Define.h"

USING_NS_CC;
Fireball::Fireball(Layer* layer, int owner, Sprite* spriteOwner)
{
	maxBullet = 7;
	runStep = 15;

	auto sprite = Sprite::create("bullet.png", Rect(21, 67, 11, 8));
	sprite->setScale(2.0f);
	mSpriteOwner = spriteOwner;
	mSprite = sprite;
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(10, 10), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setMass(200);
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(owner);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	setAlive(false);
	layer->addChild(mSprite);
}

Fireball::~Fireball()
{
}

void Fireball::update()
{
	if (isAlive())
	{
		if (mIsRunLeftToRight)
		{
			setPosition(getPosition() + Vec2(runStep, -20));
		}
		else
		{
			setPosition(getPosition() - Vec2(runStep, -20));
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