#include "Model.h"
USING_NS_CC;

Model::Model()
{
	mIsALive = true;
}

Model::~Model()
{
}

void Model::setAlive(bool alive)
{
	mIsALive = alive;
	mSprite->setVisible(mIsALive);
	mPhysicsBody->setEnabled(alive);
}

bool Model::isAlive()
{
	return mIsALive;
}

void Model::setIndex(int index)
{
	mPhysicsBody->setGroup(index);
}

int Model::getIndex()
{
	return mPhysicsBody->getGroup();
}

bool Model::isMoveRight()
{
	return mIsRunLeftToRight;
}

void Model::setPosition(cocos2d::Vec2 pos)
{
	mSprite->setPosition(pos);
}

void Model::setScale(float scale)
{
	mSprite->setScale(scale);
}

Vec2 Model::getPosition()
{
	return mSprite->getPosition();
}

Size Model::getContentSize()
{
	return mSprite->getContentSize();
}
void Model::setHP(int mBlood)
{
	this->mBlood = mBlood;
}

cocos2d::Sprite* Model::getSprite()
{
	return mSprite;
}