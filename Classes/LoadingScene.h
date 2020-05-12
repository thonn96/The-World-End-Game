#ifndef _LOADING_SCENE_H_
#define _LOADING_SCENE_H_

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);
    
    // implement the "static create()" method manually
	CREATE_FUNC(LoadingScene);
};

#endif // __HELLOWORLD_SCENE_H__
