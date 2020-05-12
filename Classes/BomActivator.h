#ifndef _BOM_ACTIVATOR_H_
#define _BOM_ACTIVATOR_H_
#include "Model.h"
#include "cocos2d.h"
using namespace cocos2d;

class BomActivator : public Model
{
private:
	int BomActivatorType;
	bool isUp = true;
	float minPos;
	float maxPos;
public:
	BomActivator(Layer* layer, int type, float mMinPos, float mMaxPos);
	~BomActivator();
	void update();
	int getType();
};
#endif