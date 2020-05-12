#pragma once
#include "Model.h"

USING_NS_CC;

class AttackPoint:public Model {
	int speed;
	int cooldown;
	int type;
	int isFinish;
public:
	AttackPoint(Layer* layer, int type, int category, int range = 2);
	void rotateToAttack(bool isRight);
	void isSkillFinish(Vec2 position);
	bool isAttackFinish();
};