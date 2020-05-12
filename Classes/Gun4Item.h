#ifndef _GUN4_ITEM_H
#define _GUN4_ITEM_H
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun4Item : public ItemModel
{
public:
	Gun4Item();
	~Gun4Item();
	Gun4Item(Layer* layer);
};
#endif