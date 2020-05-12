#ifndef _GUN6_ITEM_H
#define _GUN6_ITEM_H
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun6Item : public ItemModel
{
public:
	Gun6Item();
	~Gun6Item();
	Gun6Item(Layer* layer);
};
#endif