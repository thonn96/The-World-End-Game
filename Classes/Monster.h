#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "Model.h"
#include "Bullet.h"
#include "ui\CocosGUI.h"
#include "Gun1Item.h"
#include "Gun2Item.h"
#include "Gun3Item.h"
#include "Gun4Item.h"
#include "Gun5Item.h"
#include "Gun6Item.h"
#include "BossItem.h"
#include "BulletItem.h"

class Monster : public Model
{
public:
	static const int STATE_IDLE = 0;
	static const int STATE_WALK = STATE_IDLE + 1;
	static const int STATE_FIRE = STATE_WALK + 1;
	static const int STATE_BE_HIT = STATE_FIRE + 1;
	static const int STATE_ATTACK = STATE_BE_HIT + 1;

	static const int ANIM_IDLE = 0;
	static const int ANIM_WALK = ANIM_IDLE + 1;
	static const int ANIM_BE_HIT = ANIM_WALK + 1;
	static const int ANIM_ATTACK = ANIM_BE_HIT + 1;
	static const int ANIM_TOTAl = ANIM_ATTACK + 1;


	static const int BLOOD_MAX = 100;
	static const int BLOOD_MAX_CREEP3 = 400;
	static const int BLOOD_DECREASE_WITH_GUN1 = 100;
	static const int BLOOD_DECREASE_WITH_GUN2 = 150;
	static const int BLOOD_DECREASE_WITH_GUN3 = 200;
	static const int BLOOD_DECREASE_WITH_KNIFE = 50;
	static const int BLOOD_DECREASE_WITH_CHAO = 250;
	static const int BLOOD_MONSTER3 = 100;
	static const int SPEED = 60;
	static const int BLOOD_MAX_BOSS3 = 10000; //blood boss3
	static const int BLOOD_MAX_MONSTER4 = 600; //blood crep
	static const int BLOOD_MAX_MONSTER5 = 2000; //blood boss1
	static const int BLOOD_MAX_MONSTER6 = 300; //blood crep sky
	static const int BLOOD_MAX_BOSS2 = 3000; //blood boss2

	static const int DAMAGE_BOSS1 = 10;
	static const int DAMAGE_BOSS2 = 20;
	static const int DAMAGE_BOSS3 = 20;
	static const int DAMAGE_BOSS_CREP = 7;
	static const int DAMAGE_BOSS_SKY = 10;
protected:
	int mCurrentState;
	int minPos, maxPos;
	cocos2d::Action* mAnimation[ANIM_TOTAl];
	bool mIsMcLeft;
	Bullet *mBullet;
	ItemModel* item;
	bool checkAutoRun;
	Sprite *loadingBarBG;
	ui::LoadingBar *loadingBar;
	bool isRight;
	int typeMonster;
	bool isInRange;

	int countHit = 0;

public:
	Monster();
	~Monster();

	void setIsInRange(bool );

	void setState(int state);

	virtual void update(Vec2 player);

	int getHP();

	void runMonster(float x);

	void bulletHasCollision();

	void setItemAlive();

	int getTypeMonster();

	void walk();

	void setGroupBullet(int i);

	virtual int getDamage() = 0;

	virtual int getRange()=0 ;

	virtual int getSpeed() = 0;
};

#endif