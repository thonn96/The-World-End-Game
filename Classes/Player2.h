#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include "Bullet.h"
#include "cocos2d.h"
#include "PlayerModel.h"
#include "Gun1.h"
#include "Gun2.h"
#include "Gun3.h"
#include <vector>

class Player2 : public PlayerModel
{
private:
	std::vector<WeaponModel*> mBullets;
	//Bullet * mBullets[MAX_BULLET];
	Sprite* sprite;
	int typeGun = 1;
	Gun1* gun1;
	Layer* mLayer;
public:
	Player2(cocos2d::Layer* layer);
	~Player2();

	void setState(int nextState);

	void knife();

	void fire();

	void update();

	void loadGun();

	void changeGun(bool isRev);

	int getTypeGun();

	virtual void bulletHasCollision(int bulletIndex);

private:
	void updateBullets();
};

#endif