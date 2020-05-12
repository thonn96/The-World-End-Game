#ifndef _WEAPON_MODEL_H_
#define _WEAPON_MODEL_H_
#include "Model.h"

USING_NS_CC;
class WeaponModel : public Model
{
protected:
	int runStep;
	int maxBullet;
	cocos2d::Sprite* mSpriteOwner;
public:
	static const int MAX_BULLET_GUN1 = 7;
	static const int MAX_BULLET_GUN2 = 20;
	static const int MAX_BULLET_GUN3 = 3;
	WeaponModel();
	~WeaponModel();

	void explode(bool isRight);

	int getMaxBullet()
	{
		return maxBullet;
	}

	virtual void update();
};
#endif