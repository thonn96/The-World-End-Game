#ifndef _ITEM_MODEL_H
#define _ITEM_MODEL_H
#include "cocos2d.h"
#include "Model.h"
USING_NS_CC;
class ItemModel : public Model
{
public:
	static const int BITMASK_ITEM = 200;
	
	ItemModel();
	~ItemModel();
	void setIsAlive(bool isAlive, Vec2 pos);
};
#endif