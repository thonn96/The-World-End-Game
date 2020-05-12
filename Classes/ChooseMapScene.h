#ifndef _CHOOSE_MAP_SCENE_H
#define _CHOOSE_MAP_SCENE_H
#include "cocos2d.h"

class ChooseMapScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ChooseMapScene);
};
#endif