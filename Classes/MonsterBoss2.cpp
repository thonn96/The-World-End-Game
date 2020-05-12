#include "MonsterBoss2.h"
#include"math.h"
#include"cocos2d.h"

USING_NS_CC;

MonsterBoss2::MonsterBoss2(cocos2d::Layer* layer, float iMinPos, float iMaxPos)
{
	mBlood = BLOOD_MAX_BOSS2;
	mCurrentState = STATE_IDLE;
	mIsMcLeft = true;
	minPos = iMinPos;
	maxPos = iMaxPos;
	typeMonster = MODLE_TYPE_MONSTER7;
	mSprite = Sprite::create("crep/Boss2.png", Rect(24, 11, 225, 95));
	mSprite->setAnchorPoint(Vec2(0.5, 0));
	mSprite->setScale(1.0f);
	mSprite->setFlippedX(mIsMcLeft);
	//physics body
	mPhysicsBody = PhysicsBody::createBox(Size(120,100), PhysicsMaterial(1.0f, 0.0f, 1.0f));
	mPhysicsBody->setPositionOffset(Vec2(20, 0));
	mPhysicsBody->setRotationEnable(false);
	mPhysicsBody->setCollisionBitmask(Model::BITMASK_MONSTER);
	mPhysicsBody->setGravityEnable(true);
	mPhysicsBody->setContactTestBitmask(true);
	mPhysicsBody->setMass(50);
	mSprite->setPhysicsBody(mPhysicsBody);
	layer->addChild(mSprite);

	//create heaart monster

	loadingHeartM7 = Sprite::create("heartM1.png");
	loadingHeartM7->setPosition(mSprite->getPosition() + Vec2(15, 70));
	/*loadingHeartM7->setScale(0.8f);*/
	mSprite->addChild(loadingHeartM7);

	loadingHM7 = ui::LoadingBar::create("heartMonster.png");
	loadingHM7->setPosition(loadingHeartM7->getPosition());
	loadingHM7->setDirection(ui::LoadingBar::Direction::LEFT);
	/*loadingHM7->setScale(0.8f);*/
	loadingHM7->setPercent(100);
	mSprite->addChild(loadingHM7);

	//create animate
	Vector<SpriteFrame*> animFrames;
	//idle
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(7, 121, 217, 95)));
	mAnimation[ANIM_IDLE] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);

	//walk
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(7, 121, 217, 95)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(235, 122, 220, 94)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(469, 122, 230, 94)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(712, 125, 223, 91)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(5, 241, 218, 95)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(239, 238, 227, 98)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(474, 237, 235, 101)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(725, 240, 221, 98)));

	/*animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(244, 518, 227, 73)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(487, 486, 205, 103)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(704, 477, 200, 97)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(927, 495, 225, 100)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(2, 504, 221, 92)));*/
	mAnimation[ANIM_WALK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);
	
	

	//eat bullet
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(7, 121, 217, 95)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(235, 122, 220, 94)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(469, 122, 230, 94)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(712, 125, 223, 91)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(5, 241, 218, 95)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(239, 238, 227, 98)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(474, 237, 235, 101)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(725, 240, 221, 98)));

	mAnimation[ANIM_BE_HIT] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);
	
	//attack
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(3, 749, 208, 99)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(230, 739, 201, 109)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(444, 748, 244, 100)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(701, 748, 268, 100)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(981, 748, 262, 100)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(1253, 748, 245, 110)));
	animFrames.pushBack(SpriteFrame::create("crep/Boss2.png", Rect(1506, 748, 208, 99)));
	mAnimation[ANIM_ATTACK] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.09f)), 1);
	//

	CC_SAFE_RETAIN(mAnimation[ANIM_IDLE]);
	CC_SAFE_RETAIN(mAnimation[ANIM_WALK]);
	CC_SAFE_RETAIN(mAnimation[ANIM_BE_HIT]);
	CC_SAFE_RETAIN(mAnimation[ANIM_ATTACK]);

	setState(STATE_IDLE);
	//bullet
	auto sprite = Sprite::create("crep/bullet.png", Rect(39, 221, 21, 12));
	sprite->setScale(1.5f);
	mBullet = new Bullet(layer, sprite, Model::BITMASK_MONSTER_BULLET, mSprite);
	mBullet->setScale(1.5f);
	mBullet->setAlive(false);
}

MonsterBoss2::~MonsterBoss2()
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
void MonsterBoss2::update(Vec2 player)
{
	Monster::update(player);

	loadingHM7->setPercent(getHP()/30);
}
int MonsterBoss2::getDamage()
{
	return DAMAGE_BOSS2;
}