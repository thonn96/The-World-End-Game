#ifndef _THEEARTHSAVE_H_
#define _THEEARTHSAVE_H_
#include "cocos2d.h"

class TheEarthSave : public cocos2d::Layer
{
public:
	TheEarthSave();
	~TheEarthSave();

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update();

	CREATE_FUNC(TheEarthSave);

};
#endif