#include "MonsterCrep.h"
#include "Define.h"
USING_NS_CC;

MonsterCrep::MonsterCrep(cocos2d::Layer* layer, float iMinPos, float iMaxPos)
{
	mBlood = BLOOD_MAX_MONSTER4;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	minPos = iMinPos;
	maxPos = iMaxPos;
	typeMonster = MODLE_TYPE_MONSTER4;
	mSprite = Sprite::create("crep/MonsterCrep.png", Rect(20, 0, 39, 63));
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	mSprite->setScale(1.5f);
	//mSprite->setFlippedX(mIsMcLeft);

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

	loadingHeartM4 = Sprite::create("heartM1.png");
	loadingHeartM4->setPosition(mSprite->getPosition() + Vec2(15, 70));
	loadingHeartM4->setScale(0.8f);
	mSprite->addChild(loadingHeartM4);

	loadingHM4 = ui::LoadingBar::create("heartMonster.png");
	loadingHM4->setPosition(loadingHeartM4->getPosition());
	loadingHM4->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingHM4->setScale(0.8f);
	loadingHM4->setPercent(100);
	mSprite->addChild(loadingHM4);

	//create animate
	Vector<SpriteFrame*> animFrames;

	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(63, 0, 56, 59)));
	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)), 1);

	//idle
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(20, 0, 39, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(63, 0, 56, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 0, 54, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(187, 2, 51, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(0, 72, 58, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(66, 68, 50, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 66, 43, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(180, 68, 58, 61)));
	mAnimation[ANIM_WALK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)),1);

	//eat bullet
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(20, 0, 39, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(63, 0, 56, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 0, 54, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(187, 2, 51, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(0, 72, 58, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(66, 68, 50, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 66, 43, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(180, 68, 58, 61)));
	
	mAnimation[ANIM_BE_HIT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)), 1);
	//
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(20, 0, 39, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(63, 0, 56, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 0, 54, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(187, 2, 51, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(0, 72, 58, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(66, 68, 50, 59)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(129, 66, 43, 63)));
	animFrames.pushBack(SpriteFrame::create("crep/MonsterCrep.png", Rect(180, 68, 58, 61)));

	mAnimation[ANIM_ATTACK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.3f)), 1);

	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_WALK]);
	CC_SAFE_RETAIN(mAnimation[ANIM_BE_HIT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);
	setState(STATE_IDLE);

	//bullet
	auto sprite = Sprite::create("crep/bullet.png", Rect(202, 111, 13, 13));
	sprite->setScale(3.0f);
	mBullet = new Bullet(layer, sprite, Model::BITMASK_MONSTER_BULLET, mSprite);
	mBullet->setScale(1.5f);
	mBullet->setAlive(false);
}

MonsterCrep::~MonsterCrep()
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
void MonsterCrep::update(Vec2 player)
{
	Monster::update(player);
	
	loadingHM4->setPercent(getHP()/6);
}
int MonsterCrep::getDamage()
{
	return DAMAGE_BOSS_CREP;
}