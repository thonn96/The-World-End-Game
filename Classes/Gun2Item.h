#ifndef _GUN2_ITEM_H
#define _GUN2_ITEM_H
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun2Item : public ItemModel
{
public:
	Gun2Item();
	~Gun2Item();
	Gun2Item(Layer* layer);
};
#endif