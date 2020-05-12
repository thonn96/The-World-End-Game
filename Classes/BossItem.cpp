#include "BossItem.h"

BossItem::BossItem()
{
}

BossItem::BossItem(cocos2d::Layer* layer)
{
	mSprite = Sprite::create("item/treasure.png");
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1, 0, 1));
	mPhysicsBody->setGravityEnable(true);
	mPhysicsBody->setContactTestBitmask(true);
	mPhysicsBody->setCollisionBitmask(BITMASK_ITEM);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);
	mSprite->setScale(0.4f);
	auto zoomIn = ScaleTo::create(0.5f, 0.3f);
	auto zoomOut = ScaleTo::create(0.5f, 0.2f);
	mSprite->runAction(RepeatForever::create(Sequence::createWithTwoActions(zoomIn, zoomOut)));
	mIsALive = true;
}

BossItem::~BossItem()
{
}