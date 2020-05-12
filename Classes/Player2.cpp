#include "Player2.h"
#include "Define.h"
#include <cstdio>
#include <cstdarg>
#include "Bullet.h"
#include "Inventory.h"
#include "InGameScene.h"
USING_NS_CC;

Player2::Player2(cocos2d::Layer* layer)
{
	mCurrentState = STATE_START;
	mLayer = layer;

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mc/mc.plist");

	mSprite = Sprite::create("A4.png", Rect(1114, 1, 65, 102));
	//mSprite = Sprite::createWithSpriteFrameName("A4_01.png");
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	//physics body
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setMass(90);
	//mPhysicsBody->setVelocityLimit(500);
	mPhysicsBody->setCollisionBitmask(Model::BITMASK_PLAYER);
	mPhysicsBody->setContactTestBitmask(true);

	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);

	attackPoint = new AttackPoint(layer, BITMASK_PLAYER_KNIFE, 112, 2);

	

	//create animate
	Vector<SpriteFrame*> animFrames;

	//idle
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1114, 1, 65, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1182, 0, 58, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1243, 0, 63, 105)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1309, 1, 60, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1372, 0, 62, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1437, 0, 62, 104)));

	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_01.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_02.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_03.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_04.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_05.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_06.png"));

	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)), 1);

	//run
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1409, 327, 65, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1067, 212, 60, 102)));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_39.png"));
	//animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("A4_23.png"));
	
	mAnimation[ANIM_RUN] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)), 1);

	//jump
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(167, 116, 70, 86)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(257, 116, 73, 86)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(351, 111, 69, 91)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(432, 115, 84, 86)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(521, 112, 76, 91)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1063, 211, 66, 104)));

	mAnimation[ANIM_JUMP] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//knife
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(72, 450, 106, 87)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(102, 83, 73, 86)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(331, 454, 94, 82)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(452, 432, 83, 106)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(574, 437, 68, 110)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(697, 433, 68, 110)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(815, 440, 63, 105)));

	mAnimation[ANIM_KNIFE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.08f)), 1);

	//idle fire with Gun1
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(619, 105, 78, 105)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(714, 108, 70, 98)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(800, 104, 76, 106)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(890, 106, 66, 101)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(978, 106, 64, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1065, 109, 65, 100)));

	mAnimation[ANIM_IDLE_FIRE_GUN1] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.05f)), 1);

	//idle fire with Gun2
	animFrames.clear();
	/*animFrames.pushBack(SpriteFrame::create("A4.png", Rect(460, 789, 61, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(575, 788, 67, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(689, 787, 70, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(816, 784, 60, 109)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(935, 785, 60, 107)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1051, 786, 70, 105)));*/
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1288, 786, 81, 101)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1412, 787, 74, 99)));

	mAnimation[ANIM_IDLE_FIRE_GUN2] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//idle fire with Gun3
	animFrames.clear();
	/*animFrames.pushBack(SpriteFrame::create("A4.png", Rect(779, 920, 75, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(881, 919, 78, 101)));*/
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(989, 917, 79, 107)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1094, 920, 84, 102)));
	
	mAnimation[ANIM_IDLE_FIRE_GUN3] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	
	// anim damege
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("dame.png", Rect(29, 10, 65, 104)));
	animFrames.pushBack(SpriteFrame::create("dame.png", Rect(104, 12, 65, 103)));

	mAnimation[ANIM_DAMAGE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//anim die
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("die.png", Rect(6, 7, 124, 44)));

	mAnimation[ANIM_DIE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//retain
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);
	CC_SAFE_RETAIN(mAnimation[ANIM_JUMP]);
	CC_SAFE_RETAIN(mAnimation[ANIM_KNIFE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE_FIRE_GUN1]);
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE_FIRE_GUN2]);
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE_FIRE_GUN3]);
	CC_SAFE_RETAIN(mAnimation[ANIM_DAMAGE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_DIE]);

	//create bullet
	loadGun();
}

void Player2::changeGun(bool isRev)
{
	int t;
	if (GameSetting::getInstance()->checkSound)
	{
		GameSetting::getInstance()->playSoundEffect("sounds/sound_changegun.mp3");
	}
	int gun = Inventory::getInstance()->getCurrentGun();
	switch (gun)
	{
	case 1:	
		t = isRev ? 1 : 0;
		if (Inventory::getInstance()->getGun(2 + t))
		{
			Inventory::getInstance()->setCurrentGun(2 + t);
		}
		else if (Inventory::getInstance()->getGun(3 - t))
		{
			Inventory::getInstance()->setCurrentGun(3 - t);
		}
		break;
	case 2:
		t = isRev ? 2 : 0;
		if (Inventory::getInstance()->getGun(3 - t))
		{
			Inventory::getInstance()->setCurrentGun(3 - t);
		}
		else if (Inventory::getInstance()->getGun(1 + t))
		{
			Inventory::getInstance()->setCurrentGun(1 + t);
		}
		break;
	case 3:
		t = isRev ? 1 : 0;
		if (Inventory::getInstance()->getGun(1 + t))
		{
			Inventory::getInstance()->setCurrentGun(1 + t);
		}
		else if (Inventory::getInstance()->getGun(2 - t))
		{
			Inventory::getInstance()->setCurrentGun(2 - t);
		}
		break;
	}
	loadGun();
}

void Player2::loadGun()
{
	for (int i = 0; i < mBullets.size(); i++) {
		bulletHasCollision(i);
	}

	mBullets.clear();
	switch (getTypeGun())
	{
	case 1:
		for (int i = 0; i < WeaponModel::MAX_BULLET_GUN1; i++) {
			auto gun = new Gun1(mLayer, Model::BITMASK_PLAYER_BULLET, mSprite);
			gun->setIndex(i);
			mBullets.push_back(gun);
		}
		break;
	case 2:
		for (int i = 0; i < WeaponModel::MAX_BULLET_GUN2; i++) {
			auto gun = new Gun2(mLayer, Model::BITMASK_PLAYER_BULLET, mSprite);
			gun->setIndex(i);
			mBullets.push_back(gun);
		}
		break;
	case 3:
		for (int i = 0; i < WeaponModel::MAX_BULLET_GUN3; i++) {
			auto gun = new Gun3(mLayer, Model::BITMASK_PLAYER_BULLET, mSprite);
			gun->setIndex(i);
			mBullets.push_back(gun);
		}
		break;
	}
}

int Player2::getTypeGun()
{
	return Inventory::getInstance()->getCurrentGun();;
}

Player2::~Player2()
{
	for (int i = 0; i < ANIM_TOTAl; i++)
	{
		if (mAnimation[i])
		{
			mAnimation[i]->autorelease();
		}
	}

	for (int i = 0; i < mBullets.size(); i++)
	{
		CC_SAFE_DELETE(mBullets[i]);
	}
}

void Player2::fire()
{
	if (mCurrentState != STATE_DAMAGE)
	{
		typeGun = Inventory::getInstance()->getCurrentGun();
		switch (typeGun)
		{
		case 1:
			setState(Player2::STATE_IDLE_FIRE_GUN1);
			break;
		case 2:
			setState(Player2::STATE_IDLE_FIRE_GUN2);
			break;
		case 3:
			setState(Player2::STATE_IDLE_FIRE_GUN3);
			break;
		}
		
		for (int i = 0; i < mBullets.size(); i++)
		{
			if (!mBullets.at(i)->isAlive() && Inventory::getInstance()->getNumBulletGun(typeGun) > 0) {
				mBullets.at(i)->setAlive(true);
				if (getTypeGun() == 1)
				{
					mBullets.at(i)->setPosition(getPosition() + (Vec2((isMoveRight() ? 1 : -1)*getContentSize().width * 2 / 4, getContentSize().height * 2 / 3+15)));
				}
				else
				{
					mBullets.at(i)->setPosition(getPosition() + (Vec2((isMoveRight() ? 1 : -1)*getContentSize().width * 2 / 4, getContentSize().height * 2 / 3+3)));
				}
				mBullets.at(i)->explode(isMoveRight());
				Inventory::getInstance()->useBulletGun(typeGun);
				if (Inventory::getInstance()->getNumBulletGun(typeGun) == 0)
				{
					Inventory::getInstance()->throwGun(typeGun);
				}
				break;
			}
		}
	}
}
void Player2::knife()
{
		setState(Player2::STATE_KNIFE);
		attackPoint->rotateToAttack(mIsRunLeftToRight);
}

void Player2::setState(int nextState)
{
	//change animation, if JUMP: wait finish
	if (!((mCurrentState == STATE_JUMP || mCurrentState == STATE_DAMAGE) && mSprite->getNumberOfRunningActions() > 0))
	{
		switch (nextState) {
		case STATE_START:
			mIsRunLeftToRight = true;
			mBlood = BLOOD_MAX;
			setAlive(true);
			if (InGameScene::mapIndex == 4 && getPosition().y > 1600)
			{
				setPosition(Vec2(1768, 1699));
			}
			else
			{
				setPosition(Vec2(50, 200));
			}
			setState(STATE_IDLE);
			break;
		case STATE_IDLE:
			if (nextState != mCurrentState)
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_IDLE]);
			}
			else if (mSprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				mSprite->runAction(mAnimation[ANIM_IDLE]);
			}
			break;
		case STATE_RUN:
			if (nextState != mCurrentState)
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_RUN]);
			}
			else if (mSprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				mSprite->runAction(mAnimation[ANIM_RUN]);
			}
			break;
		case STATE_JUMP:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_JUMP]);
			}
			else if (mSprite->getNumberOfRunningActions() == 0)
			{
				mSprite->runAction(mAnimation[ANIM_JUMP]);
			}
			break;
		case STATE_KNIFE:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				if (mCurrentState == STATE_IDLE)
				{
					mSprite->runAction(mAnimation[ANIM_KNIFE]);
				}
				else if (mCurrentState == STATE_RUN)
				{
					mSprite->runAction(mAnimation[ANIM_KNIFE]);
				}
				else if (mCurrentState == STATE_JUMP)
				{
					mSprite->runAction(mAnimation[ANIM_KNIFE]);
				}
			}
			else if (mSprite->getNumberOfRunningActions() == 0)
			{
				mSprite->runAction(mAnimation[ANIM_KNIFE]);
			}
			break;
		case STATE_IDLE_FIRE_GUN1:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				if (mCurrentState == STATE_IDLE)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN1]);
				}
				else if (mCurrentState == STATE_RUN)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN1]);
				}
				else if (mCurrentState == STATE_JUMP)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN1]);
				}
			}
			else if (mSprite->getNumberOfRunningActions() == 0)
			{
				mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN1]);
			}
			break;
		case STATE_IDLE_FIRE_GUN2:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				if (mCurrentState == STATE_IDLE)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN2]);
				}
				else if (mCurrentState == STATE_RUN)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN2]);
				}
				else if (mCurrentState == STATE_JUMP)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN2]);
				}
			}
			else if (mSprite->getNumberOfRunningActions() == 0)
			{
				mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN2]);
			}
			break;
		case STATE_IDLE_FIRE_GUN3:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				if (mCurrentState == STATE_IDLE)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN3]);
				}
				else if (mCurrentState == STATE_RUN)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN3]);
				}
				else if (mCurrentState == STATE_JUMP)
				{
					mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN3]);
				}
			}
			else if (mSprite->getNumberOfRunningActions() == 0)
			{
				mSprite->runAction(mAnimation[ANIM_IDLE_FIRE_GUN3]);
			}
			break;
		case STATE_DAMAGE:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_DAMAGE]);
				mBlood -= BLOOD_DECREASE;
				if (mBlood <= 0)
				{
					setAlive(false);
					setLive(getLive() - 1);
				}
			}
			break;
		}

		mCurrentState = nextState;
	}

}

void Player2::update()
{
	updateBullets();
	attackPoint->isSkillFinish(mSprite->getPosition() + Vec2((mIsRunLeftToRight ? 1 : -1) * mSprite->getContentSize().width / 4 , mSprite->getContentSize().height / 2 ));
	//check idle

	if (getPosition().y < 0)
	{
		setAlive(false);
		setLive(getLive() - 1);
	}

	//restart
	if (!isAlive())
	{
		setState(STATE_START);
	}
}

void Player2::updateBullets()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->update();
	}
}

void Player2::bulletHasCollision(int bulletIndex)
{
	mBullets[bulletIndex]->setAlive(false);
}
