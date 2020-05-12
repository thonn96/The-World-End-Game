#ifndef _BOM_ITEM_H_
#define _BOM_ITEM_H_

#include "Model.h"
#include "cocos2d.h"

using namespace cocos2d;
class BomItem : public Model
{
private:
	int BomType;
	bool isUp = true;
	float minPos;
	float maxPos;
public:
	BomItem(Layer* layer, int type, float mMinPos, float mMaxPos);
	~BomItem();
	void update();
	int getType();
};
#endif