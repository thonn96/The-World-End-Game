#ifndef _MONSTERBOSS3_H_
#define _MONSTERBOSS3_H_
#include "Monster.h"
#include "Bullet.h"
#include "ui/CocosGUI.h"
class MonsterBoss3 : public Monster
{
public:
	Sprite* loadingHeartM3;
	ui::LoadingBar* loadingHM3;
	MonsterBoss3(cocos2d::Layer* layer, float iMinPos = 0, float iMaxPos = 0);
	~MonsterBoss3();
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