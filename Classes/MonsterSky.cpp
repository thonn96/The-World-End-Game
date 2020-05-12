#include "MonsterSky.h"
#include"math.h"
#include"cocos2d.h"

USING_NS_CC;

MonsterSky::MonsterSky(cocos2d::Layer* layer, float iMinPos, float iMaxPos)
{
	mBlood = BLOOD_MAX_MONSTER6;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	minPos = iMinPos;
	maxPos = iMaxPos;
	typeMonster = MODLE_TYPE_MONSTER6;
	mSprite = Sprite::create("crep/MonsterSky.png", Rect(10, 13, 133, 141));
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	mSprite->setScale(0.75f);
	mSprite->setFlippedX(mIsMcLeft);
	//physics body
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setPositionOffset(Vec2(20, 0));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setCollisionBitmask(Model::BITMASK_MONSTER);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setContactTestBitmask(true);
	mPhysicsBody->setMass(500000);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);

	//create heaart monster

	loadingHeartM6 = Sprite::create("heartM1.png");
	loadingHeartM6->setPosition(mSprite->getPosition() + Vec2(30, 120));
	loadingHeartM6->setScale(0.8f);
	mSprite->addChild(loadingHeartM6);

	loadingHM6 = ui::LoadingBar::create("heartMonster.png");
	loadingHM6->setPosition(loadingHeartM6->getPosition());
	loadingHM6->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingHM6->setScale(0.8f);
	loadingHM6->setPercent(100);
	mSprite->addChild(loadingHM6);

	//create animate
	Vector<SpriteFrame*> animFrames;
	//idle

	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(7, 11, 115, 145)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 55, 140, 96)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(282, 40, 124, 122)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 55, 140, 96)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(7, 177, 126, 157)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 55, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(163, 231, 140, 93)));

	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//eat bullet
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(10, 13, 133, 141)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(283, 42, 121, 117)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(10, 181, 120, 155)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(163, 231, 140, 93)));
	mAnimation[ANIM_BE_HIT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);
	//
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(10, 13, 133, 141)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(283, 42, 121, 117)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(10, 181, 120, 155)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(137, 57, 137, 93)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterSky.png", Rect(163, 231, 140, 93)));
	mAnimation[ANIM_ATTACK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);


	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_BE_HIT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);


	setState(STATE_IDLE);
	setState(STATE_ATTACK);
	//bullet
	auto sprite = Sprite::create("crep/bullet.png", Rect(273, 300, 19, 19));
	sprite->setScale(0.7f);
	mBullet = new Bullet(layer, sprite, Model::BITMASK_MONSTER_BULLET, mSprite);
	mBullet->setScale(2.0f);
	mBullet->setAlive(false);
}

MonsterSky::~MonsterSky()
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

void MonsterSky::update(Vec2 player)
{
	mIsMcLeft = player.x < getPosition().x;

	if (abs(player.x - getPosition().x) <= getRange() && abs(player.y - getPosition().y) <= 5)
	{
		setIsInRange(true);
	}
	else
	{
		walk();
		setIsInRange(false);
	}

	if (mSprite->getNumberOfRunningActions() == 0)
	{
		if (mCurrentState == STATE_IDLE && isInRange)
		{
			//update orientation
			mSprite->setFlippedX(mIsMcLeft);
			//setState(STATE_ATTACK);
			setState(STATE_FIRE);
		}
		else if (mCurrentState == STATE_ATTACK && STATE_FIRE)
		{
			setState(STATE_IDLE);
		}
		else if (mCurrentState == STATE_BE_HIT)
		{
			setState(STATE_IDLE);
		}
		else
		{
			setState(STATE_IDLE);
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
			int typeGun = cocos2d::RandomHelper::random_int(1, 7);
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
		particleSelectitem->setPosition(mSprite->getPosition() - Vec2(5, 0));
		particleSelectitem->setScale(0.7f);
		dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByTag(10))->addChild(particleSelectitem);
	}

	//update bullet
	mBullet->update(10);

	loadingHM6->setPercent(getHP()/3);
}

int MonsterSky::getDamage()
{
	return DAMAGE_BOSS_SKY;
}