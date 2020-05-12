#include "Player1.h"
#include "Define.h"
#include <cstdio>
#include <cstdarg>

USING_NS_CC;

Player1::Player1(cocos2d::Layer* layer)
{
	mCurrentState = STATE_START;
	mBlood = BLOOD_MAX;
	mSprite = Sprite::create("lv1.png", Rect(3, 4, 61, 108));
	//mSprite->setFlippedX(true);
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	//physics body
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setMass(90);
	mPhysicsBody->setCollisionBitmask(Model::BITMASK_PLAYER);
	mPhysicsBody->setContactTestBitmask(true);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);

	attackPoint = new AttackPoint(layer, BITMASK_PLAYER_PUNCH, 112, 2);

	//create animate
	Vector<SpriteFrame*> animFrames;

	//idle
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1176, 0, 53, 114)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1230, 2, 54, 112)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1286, 1, 51, 113)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1339, 1, 52, 113)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1393, 1, 52, 113)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1446, 0, 54, 114)));

	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)), 1);

	//run
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("lv1_51.png", Rect(0, 0, 80, 93)));
	animFrames.pushBack(SpriteFrame::create("lv1_52.png", Rect(0, 0, 45, 101)));
	/*animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(881, 2061, 78, 102)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(655, 2056, 80, 102)));*/

	mAnimation[ANIM_RUN] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.15f)), 1);

	//jump
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(117, 637, 87, 87)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(231, 633, 75, 108)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(332, 629, 77, 92)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(446, 631, 67, 94)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(563, 635, 51, 102)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(655, 634, 74, 98)));

	/*animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(139, 2675, 49, 103)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(272, 2691, 60, 71)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(408, 2693, 57, 57)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(555, 2690, 50, 59)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(680, 2685, 87, 71)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(821, 2695, 85, 52)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(955, 2695, 88, 62)));*/

	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(763, 631, 69, 99)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(877, 642, 59, 85)));

	mAnimation[ANIM_JUMP] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//parkout
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(139, 2675, 49, 103)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(272, 2691, 60, 71)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(408, 2693, 57, 57)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(555, 2690, 50, 59)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(680, 2685, 87, 71)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(821, 2695, 85, 52)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(955, 2695, 88, 62)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1107, 2673, 90, 79)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1259, 2676, 68, 92)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(1405, 2672, 64, 105)));

	mAnimation[ANIM_PARKOUT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//beat 
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(14, 12, 83, 119)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(152, 3, 83, 124)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(289, 35, 106, 98)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(424, 38, 63, 93)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(559, 37, 71, 96)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(695, 36, 99, 102)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(831, 31, 97, 106)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(959, 39, 99, 95)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(1085, 40, 106, 94)));
	animFrames.pushBack(SpriteFrame::create("beat.png", Rect(1233, 38, 85, 99)));

	mAnimation[ANIM_FIRE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.07f)), 1);

	//die
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(697, 3688, 52, 86)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(820, 3700, 85, 63)));
	/*animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(419, 541, 88, 65)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(539, 550, 130, 38)));*/

	mAnimation[ANIM_DIE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.05f)), 1);

	//avoid
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(560, 2534, 53, 76)));
	animFrames.pushBack(SpriteFrame::create("lv1.png", Rect(698, 2535, 61, 75)));

	mAnimation[ANIM_AVOID] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.5f)), 1);

	//retain
	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_RUN]);
	CC_SAFE_RETAIN(mAnimation[ANIM_JUMP]);
	CC_SAFE_RETAIN(mAnimation[ANIM_PARKOUT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_FIRE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_AVOID]);
	CC_SAFE_RETAIN(mAnimation[ANIM_DIE]);

	//create bullet	
	/*for (int i = 0; i < MAX_BULLET; i++) {
		auto sprite = Sprite::create("mc/mc.png", Rect(1077, 2257, 120, 76));
		sprite->setScale(0.7f);
		mBullets[i] = new Bullet(layer, sprite, Model::BITMASK_PLAYER_BULLET);
		mBullets[i]->setIndex(i);
	}*/

}

Player1::~Player1()
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

void Player1::avoid()
{
	setState(PlayerModel::STATE_AVOID);
}

void Player1::fire()
{
	setState(PlayerModel::STATE_FIRE);
	attackPoint->rotateToAttack(mIsRunLeftToRight);
}

void Player1::parkout()
{
	setState(PlayerModel::STATE_PARKOUT);
}

void Player1::setState(int nextState)
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
			//setPosition(mSprite->getPosition());
			setPosition(Vec2(50, 200));
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
			}
			break;
		case STATE_DAMAGE:
			if (nextState != mCurrentState) //one time
			{
				mSprite->stopAllActions();
				mSprite->runAction(mAnimation[ANIM_DIE]);
				mBlood -= BLOOD_DECREASE;
				if (mBlood <= 0)
				{
					setAlive(false);
					setLive(getLive() - 1);
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
	}
}

void Player1::update()
{
	attackPoint->isSkillFinish(mSprite->getPosition() + Vec2((mIsRunLeftToRight ? 1 : -1) * mSprite->getContentSize().width / 4, mSprite->getContentSize().height / 2));

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
