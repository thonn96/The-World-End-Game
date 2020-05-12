#ifndef _MODEL_H_
#define _MODEL_H_

#include "cocos2d.h"

class Model
{
public:
	static const int MAX_BULLET = 10;
	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;
	static const int BITMASK_PLAYER_BULLET = BITMASK_PLAYER + 1;
	static const int BITMASK_GROUND = BITMASK_PLAYER_BULLET + 1;
	static const int BITMASK_WALL = BITMASK_GROUND + 1;
	static const int BITMASK_MONSTER = BITMASK_WALL + 1;
	static const int BITMASK_MONSTER_BULLET = BITMASK_MONSTER + 1;
	static const int BITMASK_PLAYER_PUNCH = BITMASK_MONSTER_BULLET + 1;
	static const int BITMASK_PLAYER_KNIFE = BITMASK_PLAYER_PUNCH + 1;

	static const int MODLE_TYPE_MAIN_CHARACTER = 1;

	static const int MODLE_TYPE_MONSTER3 = 3;
	static const int MODLE_TYPE_MONSTER4 = 4;
	static const int MODLE_TYPE_MONSTER5 = 5;
	static const int MODLE_TYPE_MONSTER6 = 6;
	static const int MODLE_TYPE_MONSTER7 = 7;

	static const int MODLE_TYPE_GUN1 = 1;
	static const int MODLE_TYPE_GUN2 = 2;
	static const int MODLE_TYPE_GUN3 = 3;
	
protected:
	cocos2d::Sprite* mSprite;
	cocos2d::PhysicsBody* mPhysicsBody;
	bool mIsALive;
	bool mIsRunLeftToRight; //use to flip sprite: use one sprite to run left or right
	int mBlood;
	int totalmBlood;
	int currentmBlood;
public:
	Model();
	~Model();

	int getHP();

	void setHP(int mBlood);

	bool isMoveRight();

	void setAlive(bool alive);

	bool isAlive();

	void setPosition(cocos2d::Vec2 pos);

	void setScale(float scale);

	void setIndex(int index);

	int getIndex();

	cocos2d::Vec2 getPosition();

	cocos2d::Size getContentSize();

	cocos2d::Sprite* getSprite();
};

#endif