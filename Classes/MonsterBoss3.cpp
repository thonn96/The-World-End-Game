#include "MonsterBoss3.h"

USING_NS_CC;
ParticleSystemQuad* untiBoss;
MonsterBoss3::MonsterBoss3(cocos2d::Layer* layer, float iMinPos, float iMaxPos)
{
	mBlood = BLOOD_MAX_BOSS3;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	minPos = iMinPos;
	maxPos = iMaxPos;
	typeMonster = MODLE_TYPE_MONSTER3;
	mSprite = Sprite::create("crep/Boss3.png", Rect(2, 7, 127, 113));
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
	loadingHeartM3 = Sprite::create("heartM1.png");
	loadingHeartM3->setPosition(mSprite->getPosition() + Vec2(30, 120));
	/*loadingHeartM3->setScale(0.8f);*/
	mSprite->addChild(loadingHeartM3);

	loadingHM3 = ui::LoadingBar::create("heartMonster.png");
	loadingHM3->setPosition(loadingHeartM3->getPosition());
	loadingHM3->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingHM3->setPercent(100);
	mSprite->addChild(loadingHM3);

	//create animate
	Vector<SpriteFrame*> animFrames;
	//idle
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(2, 7, 127, 113)));
	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);
	
	//walk
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(2, 7, 127, 113)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(129, 9, 136, 114)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(271, 8, 122, 116)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(403, 7, 136, 116)));
	mAnimation[ANIM_WALK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//eat bullet
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(2, 7, 127, 113)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(129, 9, 136, 114)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(271, 8, 122, 116)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(403, 7, 136, 116)));
	mAnimation[ANIM_BE_HIT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//attack
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(6, 386, 131, 101)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(145, 386, 136, 101)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss3.png", Rect(293, 389, 168, 101)));
	mAnimation[ANIM_ATTACK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)), 1);

	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_WALK]);
	CC_SAFE_RETAIN(mAnimation[ANIM_BE_HIT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);

	setState(STATE_IDLE);
	//bullet
	auto sprite = Sprite::create("crep/bullet.png", Rect(63, 240, 32, 12));
	sprite->setScale(0.7f);
	mBullet = new Bullet(layer, sprite, Model::BITMASK_MONSTER_BULLET, mSprite);
	mBullet->setScale(2.0f);
	mBullet->setAlive(false);

	untiBoss = ParticleSystemQuad::create("particle/unti_boss.plist");
	untiBoss->setPosition(Vec2(-150,50));
	mSprite->addChild(untiBoss);
	untiBoss->setDuration(4);
}

MonsterBoss3::~MonsterBoss3()
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

int ultiHit = 4;
void MonsterBoss3::update(Vec2 player)
{
	Monster::update(player);
	if (mIsMcLeft)
	{
		untiBoss->setPosition(Vec2(-150, 50));
		untiBoss->setAngle(-178);
		untiBoss->setGravity(Vec2(-13,0));
	}
	else
	{
		untiBoss->setPosition(Vec2(150, 50));
		untiBoss->setAngle(0);
		untiBoss->setGravity(Vec2(13,0));
	}

	if (countHit == ultiHit)
	{
		mBullet->getSprite()->setVisible(false);
		countHit = 0;
		untiBoss->start();
		ultiHit = RandomHelper::random_int(4, 8);
	}

	loadingHM3->setPercent(getHP() /100);
}
int MonsterBoss3::getDamage()
{
	return DAMAGE_BOSS3;
}
