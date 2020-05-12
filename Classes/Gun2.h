#ifndef _GUN2_H_
#define _GUN2_H_
#include "WeaponModel.h"

class Gun2 : public WeaponModel
{
public:
	Gun2(cocos2d::Layer* layer, int owner, cocos2d::Sprite* spriteOwner);
	~Gun2();
};
#endif