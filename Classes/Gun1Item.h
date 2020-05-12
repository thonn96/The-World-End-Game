#ifndef _GUN1_ITEM_H
#define _GUN1_ITEM_H
#include"cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun1Item : public ItemModel
{
public:
	Gun1Item();
	~Gun1Item();
	Gun1Item(Layer* layer);
};
#endif