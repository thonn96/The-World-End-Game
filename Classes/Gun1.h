#ifndef _GUN1_H_
#define _GUN1_H_
#include "WeaponModel.h"

class Gun1 : public WeaponModel
{
public:
	Gun1(cocos2d::Layer* layer, int owner, cocos2d::Sprite* spriteOwner);
	~Gun1();

};
#endif