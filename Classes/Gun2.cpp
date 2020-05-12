#include "Gun2.h"
#include "Define.h"
#include "InGameScene.h"

Gun2::Gun2(Layer* layer, int owner, Sprite* spriteOwner)
{
	maxBullet = 20;
	runStep = 15;

	auto sprite = Sprite::create("bullet.png", Rect(63, 186, 32, 10));
	sprite->setScale(1.0f);
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

Gun2::~Gun2()
{
}
