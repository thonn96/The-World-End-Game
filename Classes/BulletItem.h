#ifndef _BULLET_ITEM_H_
#define _BULLET_ITEM_H_
#include "cocos2d.h"
#include "ItemModel.h"
USING_NS_CC;
class BulletItem : public ItemModel
{
public:
	BulletItem();
	~BulletItem();
	BulletItem(Layer* layer);
};
#endif