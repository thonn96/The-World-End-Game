#include "Gun3.h"
#include "Define.h"
#include "InGameScene.h"

USING_NS_CC;
Gun3::Gun3(Layer* layer, int owner, Sprite* spriteOwner)
{
	maxBullet = 3;
	runStep = 10;

	auto sprite = Sprite::create("bullet.png", Rect(158, 214, 15, 12));
	sprite->setScale(2.0f);
	mSpriteOwner = spriteOwner;
	mSprite = sprite;
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(40, 40), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setMass(200);
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCollisionBitmask(owner);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	setAlive(false);
	layer->addChild(mSprite);
}

Gun3::~Gun3()
{
}
