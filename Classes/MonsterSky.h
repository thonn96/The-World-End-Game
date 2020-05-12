#ifndef _MONSTERSKY_H_
#define _MONSTERSKY_H_
#include "Monster.h"
#include "Bullet.h"
#include "ui/CocosGUI.h"
class MonsterSky : public Monster
{
public:
	Sprite* loadingHeartM6;
	ui::LoadingBar* loadingHM6;
	MonsterSky(cocos2d::Layer* layer, float iMinPos = 0, float iMaxPos = 0);
	~MonsterSky();
	virtual void update(cocos2d::Vec2 player);
	virtual int getDamage();
	int getRange()
	{
		return 400;
	}
	int getSpeed()
	{
		return 10;
	}
};
#endif