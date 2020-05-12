#include "Monster.h"
#include "Define.h"
#include "Inventory.h"
#include "InGameScene.h"
USING_NS_CC;

Monster::Monster()
{
	mBlood = BLOOD_MAX;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	isInRange = false;
}

Monster::~Monster()
{
	for (int i = 0; i < ANIM_TOTAl; i++)
	{
		if (mAnimation[i])
		{
			mAnimation[i]->autorelease();
		}
	}

	CC_SAFE_DELETE(mBullet);
}

void Monster::setState(int state)
{
	switch (state)
	{
	case STATE_IDLE:
		mSprite->stopAllActions();
		mSprite->runAction(mAnimation[ANIM_IDLE]);
		break;
	case STATE_WALK:
		mSprite->stopAllActions();
		mSprite->runAction(mAnimation[ANIM_WALK]);
		break;
	case STATE_BE_HIT:
		countHit++;
		if (mCurrentState != STATE_BE_HIT)
		{
			mSprite->stopAllActions();
		}
		if (mCurrentState != state)
		{
			mSprite->runAction(mAnimation[ANIM_BE_HIT]);
		}
		if (getTypeMonster() == MODLE_TYPE_MONSTER3 && mBlood < 400)
		{
			return;
		}
		if (InGameScene::mapIndex == 1)
		{
			mBlood -= BLOOD_DECREASE_WITH_CHAO;
		}
		else if (InGameScene::mapIndex == 2) // type 5
		{
			if ((getTypeMonster() == MODLE_TYPE_MONSTER5) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER5) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 150;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER5) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 200;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else
			{
				mBlood -= 50;
			}
		}
		else if (InGameScene::mapIndex == 3) // type 7
		{
			if ((getTypeMonster() == MODLE_TYPE_MONSTER7) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER7) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 150;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER7) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 200;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else
			{
				mBlood -= 50;
			}
		}
		else if (InGameScene::mapIndex == 4) // type 3
		{
			if ((getTypeMonster() == MODLE_TYPE_MONSTER3) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER3) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 150;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER3) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 200;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER4) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 1)
			{
				mBlood -= 80;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 2)
			{
				mBlood -= 100;
			}
			else if ((getTypeMonster() == MODLE_TYPE_MONSTER6) && Inventory::getInstance()->getCurrentGun() == 3)
			{
				mBlood -= 120;
			}
			else
			{
				mBlood -= 50;
			}
		}
			
		break;
	case STATE_FIRE:
		if (!mBullet->isAlive())
		{
			mBullet->setAlive(true);
			mBullet->setPosition(getPosition() + Vec2((mIsMcLeft ? -1 : +1) * getContentSize().width * 2 / 3, getContentSize().height * 2 / 3));
			mBullet->explode(!mIsMcLeft);
		}
		break;
	case STATE_ATTACK:
		mSprite->stopAllActions();
		mSprite->runAction(mAnimation[ANIM_ATTACK]);
		break;
	}
	mCurrentState = state;
}

void Monster::update(Vec2 player)
{
	mIsMcLeft = player.x < getPosition().x;

	if (abs(player.x - getPosition().x) <= getRange() && abs(player.y - getPosition().y) <= 50)
	{
		setIsInRange(true);
	}
	else
	{
		walk();
		setIsInRange(false);
	}

	//change state
	if (mSprite->getNumberOfRunningActions() == 0)
	{
		//log("Current state %d", mCurrentState);
		if (isInRange)
		{
			if (mCurrentState == STATE_WALK)
			{
				//update orientation
				mSprite->setFlippedX(mIsMcLeft);
				setState(STATE_IDLE);
			}
			else if (mCurrentState == STATE_IDLE)
			{
				mSprite->setFlippedX(mIsMcLeft);
				//if (abs(player.x - getPosition().x) <= 250 && (getTypeMonster() == 3 || getTypeMonster() == 5 || getTypeMonster() == 7))
				//{
				//	runMonster(player.x);
				//	setState(STATE_ATTACK);
				//}
				//else
				
				setState(STATE_FIRE);
			}
			else if (mCurrentState == STATE_FIRE || mCurrentState == STATE_ATTACK)
			{
				setState(STATE_IDLE);
			}
			else if (mCurrentState == STATE_BE_HIT)
			{
				setState(STATE_IDLE);
			}
		}
		else
		{
			if (mCurrentState == STATE_WALK)
			{
				setState(STATE_WALK);
			}
			else if (mCurrentState == STATE_IDLE)
			{
				setState(STATE_WALK);
			}
			else if (mCurrentState == STATE_BE_HIT)
			{
				setState(STATE_IDLE);
			}
		}
	}

	if (mBlood <= 0)
	{
		setAlive(false);
		mBullet->setAlive(false);
		if (getTypeMonster() == 3 || getTypeMonster() == 5 || getTypeMonster() == 7)
		{
			item = new BossItem((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
			item->getSprite()->setTag(210);
		}
		else
		{
			int typeGun;
			if (InGameScene::mapIndex == 4)
			{
				typeGun = 7;
			}
			else
			{
				typeGun = cocos2d::RandomHelper::random_int(1, 7);
			}
			switch (typeGun) {
			case 1:
				item = new Gun1Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(201);
				break;
			case 2:
				item = new Gun2Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(202);
				break;
			case 3:
				item = new Gun3Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(203);
				break;
			case 4:
				item = new Gun4Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(204);
				break;
			case 5:
				item = new Gun5Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(205);
				break;
			case 6:
				item = new Gun6Item((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(206);
				break;
			case 7:
				item = new BulletItem((Layer*)(Director::getInstance()->getRunningScene()->getChildByTag(10)));
				item->getSprite()->setTag(207);
				break;
			}
		}

		item->setPosition(mSprite->getPosition());
		auto particleSelectitem = ParticleSystemQuad::create("particle/particle_selectitem.plist");
		particleSelectitem->setPosition(mSprite->getPosition()- Vec2(5,0));
		particleSelectitem->setScale(0.7f);
		dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByTag(10))->addChild(particleSelectitem);
	}
	
	//update bullet
	mBullet->update(getSpeed());
}

void Monster::bulletHasCollision()
{
	mBullet->setAlive(false);
}

void Monster::setIsInRange(bool isIn)
{
	isInRange = isIn;
}

void Monster::walk()
{
	if (minPos == maxPos && minPos == 0)
	{
		return;
	}
	if (mSprite->getPosition().x <= minPos)
	{
		mIsRunLeftToRight = true;
	}
	else if (mSprite->getPosition().x >= maxPos)
	{
		mIsRunLeftToRight = false;
	}

	if (mIsRunLeftToRight)
	{
		mPhysicsBody->setVelocity(Vec2(SPEED, mPhysicsBody->getVelocity().y));
	}
	else
	{
		mPhysicsBody->setVelocity(Vec2(-SPEED, mPhysicsBody->getVelocity().y));
	}
	mSprite->setFlippedX(!mIsRunLeftToRight);
}

void Monster::runMonster(float x)
{
	float x1 = mSprite->getPosition().x;
	float x2 = x1 + 100;

	if (x < x1)
	{
		mSprite->setPosition(mSprite->getPosition() + Vec2(-1, 0));
	}
	else
	{
		mSprite->setPosition(mSprite->getPosition() + Vec2(+1, 0));
	}
}

void Monster::setItemAlive()
{
	item->setAlive(false);
}

int Monster::getHP()
{
	return mBlood;
}
int Monster::getTypeMonster()
{
	return typeMonster;
}

void Monster::setGroupBullet(int i)
{
	mBullet->getSprite()->getPhysicsBody()->setGroup(i);
}