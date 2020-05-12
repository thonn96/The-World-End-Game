#include "MonsterBoss1.h"

USING_NS_CC;

MonsterBoss1::MonsterBoss1(cocos2d::Layer* layer, float iMinPos, float iMaxPos)
{
	mBlood = BLOOD_MAX_MONSTER5;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	minPos = iMinPos;
	maxPos = iMaxPos;
	typeMonster = MODLE_TYPE_MONSTER5;
	mSprite = Sprite::create("crep/Boss1.png", Rect(7, 7, 72, 55));
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	mSprite->setScale(1.5f);
	mSprite->setFlippedX(mIsMcLeft);
	//physics body
	mPhysicsBody = PhysicsBody::createBox(mSprite->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setPositionOffset(Vec2(20, 0));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setCollisionBitmask(Model::BITMASK_MONSTER);
	mPhysicsBody->setContactTestBitmask(true);
	mPhysicsBody->setMass(50);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);

	//create loading heart

	loadingHeartM5 = Sprite::create("heartM1.png");
	loadingHeartM5->setPosition(mSprite->getPosition() + Vec2(15, 70));
	loadingHeartM5->setScale(0.8f);
	mSprite->addChild(loadingHeartM5);

	loadingHM5 = ui::LoadingBar::create("heartMonster.png");
	loadingHM5->setPosition(loadingHeartM5->getPosition());
	loadingHM5->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingHM5->setScale(0.8f);
	loadingHM5->setPercent(100);
	mSprite->addChild(loadingHM5);

	//create animate
	Vector<SpriteFrame*> animFrames;
	//idle
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(7, 7, 72, 55)));
	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//Walk
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(7, 7, 72, 55)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(161, 4, 72, 56)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(248, 5, 85, 62)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(343, 11, 73, 57)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(423, 11, 71, 54)));
	mAnimation[ANIM_WALK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//eat bullet
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(7, 7, 72, 55)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(161, 4, 72, 56)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(248, 5, 85, 62)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(343, 11, 73, 57)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(423, 11, 71, 54)));
	mAnimation[ANIM_BE_HIT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//attack
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(5, 81, 74, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(87, 80, 71, 61)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(173, 75, 84, 68)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(272, 74, 85, 64)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(369, 78, 89, 62)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss1.png", Rect(4, 149, 93, 64)));
	mAnimation[ANIM_ATTACK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)), 1);

	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_WALK]);
	CC_SAFE_RETAIN(mAnimation[ANIM_BE_HIT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);

	setState(STATE_IDLE);
	//bullet
	auto sprite = Sprite::create("crep/bullet.png", Rect(312, 156, 16, 17));
	sprite->setScale(0.7f);
	mBullet = new Bullet(layer, sprite, Model::BITMASK_MONSTER_BULLET, mSprite);
	mBullet->setScale(1.5f);
	mBullet->setAlive(false);
}

MonsterBoss1::~MonsterBoss1()
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
void MonsterBoss1::update(Vec2 player)
{
	Monster::update(player);

	loadingHM5->setPercent(getHP()/20);
}
int MonsterBoss1::getDamage()
{
	return DAMAGE_BOSS1;
}