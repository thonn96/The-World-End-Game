#pragma once
#include "WeaponModel.h"
class Fireball : public WeaponModel
{
public:
	Fireball(cocos2d::Layer* layer, int owner, cocos2d::Sprite* spriteOwner);
	~Fireball();

	void update();
};
