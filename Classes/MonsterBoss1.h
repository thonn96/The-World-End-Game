#ifndef _MONSTERBOSS1_H_
#define _MONSTERBOSS1_H_
#include "Monster.h"
#include "Bullet.h"
#include "ui/CocosGUI.h"
class MonsterBoss1 : public Monster
{
public:
	
	Sprite* loadingHeartM5;
	ui::LoadingBar* loadingHM5;
	MonsterBoss1(cocos2d::Layer* layer, float iMinPos = 0, float iMaxPos = 0);
	~MonsterBoss1();
	virtual void update(cocos2d::Vec2 player);
	virtual int getDamage();
	int getRange()
	{
		return 300;
	}
	int getSpeed()
	{
		return 15;
	}
};
#endif