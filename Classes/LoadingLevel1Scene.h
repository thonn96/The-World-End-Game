#ifndef _LOANGDING_LEVEL1_SCENE_H_
#define _LOANGDING_LEVEL1_SCENE_H_
#include "cocos2d.h"

class LoadingLevel1Scene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(LoadingLevel1Scene);
};
#endif