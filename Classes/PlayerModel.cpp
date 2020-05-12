#include "PlayerModel.h"
#include "Define.h"
#include <cstdio>
#include <cstdarg>
#include "Monster.h"
#include "Model.h"
USING_NS_CC;

PlayerModel::PlayerModel()
{
	mCurrentState = STATE_START;
	mBlood = BLOOD_MAX;


	canRun = true;
	numOfLive = NUM_Of_LIVE;


	//create bullet	
	/*for (int i = 0; i < MAX_BULLET; i++) 
	{
		auto sprite = Sprite::create("mc/mc.png", Rect(1077, 2257, 120, 76));
		sprite->setScale(0.7f);
		mBullets[i] = new Bullet(layer, sprite, Model::BITMASK_PLAYER_BULLET);
		mBullets[i]->setIndex(i);
	}*/


}
void PlayerModel::setLive(int live)
{
	numOfLive = live;
}

PlayerModel::~PlayerModel()
{
	for (int i = 0; i < ANIM_TOTAl; i++)
	{
		if (mAnimation[i])
		{
			mAnimation[i]->autorelease();
		}
	}

	for (int i = 0; i < MAX_BULLET; i++)
	{
		//CC_SAFE_DELETE(mBullets[i]);
	}
}

void PlayerModel::setCanRun(bool canRun)
{
	this->canRun = canRun;
}

void PlayerModel::setIsFalling(bool state)
{
	isFalling = state;
}

bool PlayerModel::getIsFalling()
{
	return isFalling;
}

void PlayerModel::moveLeft(bool isJumping)
{
	mIsRunLeftToRight = false;
	mSprite->setFlippedX(true);
	if (!isJumping && !isFalling)
	{
		setState(PlayerModel::STATE_RUN);
	}
	if (canRun)
	{
		if (isFalling)
		{
			mSprite->setPosition(mSprite->getPosition() - Vec2(4, 0));
		}
		else
		{
			mSprite->setPosition(mSprite->getPosition() - Vec2(5, 0));
		}
	}
}

void PlayerModel::moveRight(bool isJumping)
{
	mIsRunLeftToRight = true;
	mSprite->setFlippedX(false);
	if (!isJumping && !isFalling)
	{
		setState(PlayerModel::STATE_RUN);
	}
	if (canRun)
	{
		if (isFalling)
		{
			mSprite->setPosition(mSprite->getPosition() + Vec2(4, 0));
		}
		else
		{
			mSprite->setPosition(mSprite->getPosition() + Vec2(5, 0));
		}
	}	
}

void PlayerModel::jump()
{
	//tac dung luc day
	float mass = mPhysicsBody->getMass();
	float gravity = Director::getInstance()->getRunningScene()->getPhysicsWorld()->getGravity().y;
	
	if (mCurrentState != STATE_DAMAGE)
	{
		mPhysicsBody->setVelocity(Vec2(mPhysicsBody->getVelocity().x, 500));
		setState(PlayerModel::STATE_JUMP);
	}
}

void PlayerModel::stop()
{
	//giảm toc do goc
	//mPhysicsBody->setAngularDamping(1);
	//mSprite->stopAction(mAnimation[mCurrentState]);
	//setState(PlayerModel::STATE_IDLE);
}

void PlayerModel::fire()
{
	setState(PlayerModel::STATE_FIRE);
	attackPoint->rotateToAttack(mIsRunLeftToRight);
}

int PlayerModel::getCurrentState()
{
	return mCurrentState;
}

int PlayerModel::getBlood()
{
	return mBlood;
}

void PlayerModel::setState(int nextState)
{
	//change animation, if JUMP: wait finish
	if (!((mCurrentState == STATE_JUMP || mCurrentState == STATE_DAMAGE) && mSprite->getNumberOfRunningActions() > 0))
	{
		switch (nextState) {
		case STATE_START:
			mCurrentState = STATE_IDLE;
			mIsRunLeftToRight = true;
			mBlood = BLOOD_MAX;
			setAlive(true);
			setPosition(Vec2(300, 300));
			setState(STATE_IDLE);
			break;
		case STATE_IDLE:
			mCurrentState = STATE_IDLE;
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
			break;
		case STATE_FIRE:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				if (mCurrentState == STATE_IDLE)
				{
					mSprite->runAction(mAnimation[ANIM_FIRE]);
				}
				else if (mCurrentState == STATE_RUN)
				{
					mSprite->runAction(mAnimation[ANIM_FIRE]);
				}
				else if (mCurrentState == STATE_JUMP)
				{
					mSprite->runAction(mAnimation[ANIM_FIRE]);
				}

				//log("asdasd %d", mSprite->getNumberOfRunningActions());
			}
			break;
		case STATE_DAMAGE:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_DIE]);
				if (mBlood <= 0 )
				{
					mSprite->stopAllActions();
					mSprite->runAction(mAnimation[ANIM_DIE]);
					setAlive(false);
				}
			}
			break;
		case STATE_PARKOUT:
			if (nextState != mCurrentState)
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_PARKOUT]);
			}
			break;
		case STATE_AVOID:
			if (nextState != mCurrentState)
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_AVOID]);
			}
		}

		mCurrentState = nextState;
		//log("%d", mSprite->getNumberOfRunningActions());
	}

}
void PlayerModel::getDamage(int damage)
{
	mBlood -= damage;
}

void PlayerModel::update()
{
	//updateBullets();

	attackPoint->isSkillFinish(mSprite->getPosition() + Vec2((mIsRunLeftToRight ? 1 : -1) * mSprite->getContentSize().width / 4, mSprite->getContentSize().height / 2));

	//check idle
	if (getPosition().y < 0)
	{
		setAlive(false);
	}

	//restart
	if (!isAlive())
	{
		setState(STATE_START);
	}
}

void PlayerModel::transform()
{
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1114, 1, 65, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1182, 0, 58, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1243, 0, 63, 105)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1309, 1, 60, 102)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1372, 0, 62, 103)));
	animFrames.pushBack(SpriteFrame::create("A4.png", Rect(1437, 0, 62, 104)));

	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)), 1);
}
