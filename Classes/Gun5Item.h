#ifndef _GUN5_ITEM_H
#define _GUN5_ITEM_H
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class Gun5Item : public ItemModel
{
public:
	Gun5Item();
	~Gun5Item();
	Gun5Item(Layer* layer);
};
#endif