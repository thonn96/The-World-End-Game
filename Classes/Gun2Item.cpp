#include "Gun2Item.h"

Gun2Item::Gun2Item(Layer* layer)
{
	mSprite = Sprite::create("item/gun2.png");
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1, 0, 1));
	mPhysicsBody->setGravityEnable(true);
	mPhysicsBody->setContactTestBitmask(true);
	mPhysicsBody->setCollisionBitmask(BITMASK_ITEM);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);
	mSprite->setScale(0.2f);
	auto zoomIn = ScaleTo::create(0.5f, 0.3f);
	auto zoomOut = ScaleTo::create(0.5f, 0.2f);
	mSprite->runAction(RepeatForever::create(Sequence::createWithTwoActions(zoomIn, zoomOut)));
	mIsALive = true;
}
Gun2Item::Gun2Item(){}
Gun2Item::~Gun2Item(){}