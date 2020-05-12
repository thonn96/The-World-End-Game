#ifndef _ABOUT_SCENE_H
#define _ABOUT_SCENE_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class AboutScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);
};
#endif