#ifndef _MONSTERCREP_H_
#define _MONSTERCREP_H_
#include "Monster.h"
#include "Bullet.h"
#include "ui\CocosGUI.h"

class MonsterCrep : public Monster
{
public:
	Sprite* loadingHeartM4;
	ui::LoadingBar* loadingHM4;

	MonsterCrep(cocos2d::Layer* layer, float iMinPos, float iMaxPos);
	~MonsterCrep();
	virtual void update(cocos2d::Vec2 player);
	virtual int getDamage();
	int getRange()
	{
		return 250;
	}
	int getSpeed()
	{
		return 5;
	}
};
#endif