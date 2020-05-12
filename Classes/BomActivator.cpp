#include "BomActivator.h"
#include "Define.h"
USING_NS_CC;
BomActivator::BomActivator(Layer* layer, int type, float mMinPos, float mMaxPos)
{

	BomActivatorType = 667;
	mSprite = Sprite::create("bomActivator.png");
	mSprite->setAnchorPoint(Vec2(0, 0));
	mSprite->setScale(0.3f);

	//Physics body
	mPhysicsBody = PhysicsBody::createEdgeBox(Size(15, 15), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setRotationEnable(false);

	mPhysicsBody->setDynamic(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setMass(10);

	mPhysicsBody->setCollisionBitmask(667);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);
}
BomActivator::~BomActivator()
{
}
void BomActivator::update()
{
}
int BomActivator::getType()
{
	return BomActivatorType;
}