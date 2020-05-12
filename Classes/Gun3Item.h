#ifndef _GUN3_ITEM_H
#define _GUN3_ITEM_H
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun3Item : public ItemModel
{
public:
	Gun3Item();
	~Gun3Item();
	Gun3Item(Layer* layer);
};
#endif