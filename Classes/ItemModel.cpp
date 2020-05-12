#include "ItemModel.h"

void ItemModel::setIsAlive(bool isAlive, Vec2 pos)
{
	mSprite->stopAllActions();
	this->mIsALive = isAlive;
	mSprite->setVisible(isAlive);
	mSprite->getPhysicsBody()->setContactTestBitmask(isAlive);
	mSprite->getPhysicsBody()->setEnabled(isAlive);
}
ItemModel::ItemModel()
{

}

ItemModel::~ItemModel(){}