#include "BomItem.h"
#include "Define.h"
USING_NS_CC;
BomItem::BomItem(Layer* layer, int type, float mMinPos, float mMaxPos)
{

	BomType = 666;

	mSprite = Sprite::create("bom_ngang.png");
	mSprite->setAnchorPoint(Vec2(0, 0));
	mSprite->setScale(0.1f);

	//Physics body
	mPhysicsBody = PhysicsBody::createEdgeBox(Size(15, 15), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setRotationEnable(false);

	mPhysicsBody->setDynamic(false);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setMass(10);

	mPhysicsBody->setCollisionBitmask(666);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);
}
BomItem::~BomItem()
{
}
void BomItem::update()
{ 
}
int BomItem::getType()
{
	return BomType;
}