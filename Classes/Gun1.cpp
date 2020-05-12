#include "Gun1.h"
#include "Define.h"

USING_NS_CC;
Gun1::Gun1(Layer* layer, int owner, Sprite* spriteOwner)
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

Gun1::~Gun1()
{
}
