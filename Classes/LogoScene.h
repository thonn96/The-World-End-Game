#ifndef _LOGO_SCENE_H_
#define _LOGO_SCENE_H_

#include "cocos2d.h"

class LogoScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(LogoScene);
};

#endif // _LOGO_SCENE_H_
