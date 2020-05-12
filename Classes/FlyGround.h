#ifndef _FLY_GROUND_H_
#define _FLY_GROUND_H_

#include "Model.h"
#include "cocos2d.h"

using namespace cocos2d;
class FlyGround : public Model
{
private:
	int groundType;
	bool isUp = true;
	float minPos;
	float maxPos;
public:
	static const int GO_UP_DOWN = 1;
	static const int GO_RIGHT_LEFT = 2;
	static const int SPEED_FALL = 100;

	FlyGround(Layer* layer, int type, float mMinPos, float mMaxPos);
	~FlyGround();

	void update();
	int getType();
};
#endif