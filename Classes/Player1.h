#ifndef _PLAYER1_H_
#define _PLAYER1_H_

#include "PlayerModel.h"
#include "Bullet.h"
#include "cocos2d.h"
#include "AttackPoint.h"

class Player1 : public PlayerModel
{
private:
	int mCurrentState;
	cocos2d::Action* mAnimation[ANIM_TOTAl];
	//Bullet* mBullets[MAX_BULLET];

	AttackPoint* attackPoint;

public:
	Player1(cocos2d::Layer* layer);
	~Player1();

	void setState(int nextState);

	void fire();

	void parkout();

	void avoid();

	void update();

};

#endif