#ifndef _MONSTERBOSS2_H_
#define _MONSTERBOSS2_H_
#include "Monster.h"
#include "Bullet.h"
#include "ui/CocosGUI.h"
class MonsterBoss2 : public Monster
{ 
public:
	Sprite* loadingHeartM7;
	ui::LoadingBar* loadingHM7;
	MonsterBoss2(cocos2d::Layer* layer, float iMinPos = 0, float iMaxPos = 0);
	~MonsterBoss2();
	virtual void update(cocos2d::Vec2 player);
	virtual int getDamage();
	int getRange()
	{
		return 450;
	}
	int getSpeed()
	{
		return 15;
	}
};
#endif