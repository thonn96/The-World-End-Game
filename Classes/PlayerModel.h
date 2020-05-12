#ifndef _PLAYER_MODEL_H_
#define _PLAYER_MODEL_H_

#include "Model.h"
#include "Bullet.h"
#include "cocos2d.h"
#include "AttackPoint.h"

class PlayerModel : public Model
{
public:
	static const int RUN_STEP = 4;
	static const int NUM_Of_LIVE = 5;
	static const int ANIM_IDLE = 1;
	static const int ANIM_RUN = ANIM_IDLE + 1;
	static const int ANIM_JUMP = ANIM_RUN + 1;
	static const int ANIM_PARKOUT = ANIM_JUMP + 1;
	static const int ANIM_FIRE = ANIM_PARKOUT + 1;
	static const int ANIM_DIE = ANIM_FIRE + 1;
	static const int ANIM_AVOID = ANIM_DIE + 1;
	static const int ANIM_KNIFE = ANIM_AVOID + 1;
	static const int ANIM_IDLE_FIRE_GUN1 = ANIM_KNIFE + 1;
	static const int ANIM_IDLE_FIRE_GUN2 = ANIM_IDLE_FIRE_GUN1 + 1;
	static const int ANIM_IDLE_FIRE_GUN3 = ANIM_IDLE_FIRE_GUN2 + 1;
	static const int ANIM_DAMAGE = ANIM_IDLE_FIRE_GUN3 + 1;
	static const int ANIM_TOTAl = ANIM_DAMAGE + 1;

	static const int STATE_START = 0;
	static const int STATE_IDLE = STATE_START + 1;
	static const int STATE_RUN = STATE_IDLE + 1;
	static const int STATE_JUMP = STATE_RUN + 1;
	static const int STATE_FIRE = STATE_JUMP + 1;
	static const int STATE_PARKOUT = STATE_FIRE + 1;
	static const int STATE_AVOID = STATE_PARKOUT + 1;
	static const int STATE_KNIFE = STATE_AVOID + 1;
	static const int STATE_IDLE_FIRE_GUN1 = STATE_KNIFE + 1;
	static const int STATE_IDLE_FIRE_GUN2 = STATE_IDLE_FIRE_GUN1 + 1;
	static const int STATE_IDLE_FIRE_GUN3 = STATE_IDLE_FIRE_GUN2 + 1;
	static const int STATE_DAMAGE = STATE_IDLE_FIRE_GUN3 + 1;
	static const int STATE_DIE = STATE_DAMAGE + 1;

	static const int BLOOD_MAX = 100;
	static const int BLOOD_DECREASE = 5;
protected:
	int mCurrentState;
	cocos2d::Action* mAnimation[ANIM_TOTAl];

	int mBlood;
	AttackPoint* attackPoint;
	int numOfLive;

	bool canRun;
	bool isFalling;

public:
	PlayerModel();
	~PlayerModel();

	virtual void setState(int nextState);

	int getCurrentState();

	int getBlood();

	void setCanRun(bool canRun);

	void moveLeft(bool isJumping);

	void moveRight(bool isJumping);

	virtual void jump();

	virtual void stop();

	virtual void fire();

	virtual void update();

	int getLive()
	{
		return numOfLive;
	}

	void setLive(int live);

	bool getIsFalling();

	void setIsFalling(bool);

	//virtual void bulletHasCollision(int bulletIndex);

	void transform();

	virtual void getDamage(int damage);

private:
	//void updateBullets();
};

#endif