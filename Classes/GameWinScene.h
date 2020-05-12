#ifndef _GAMEWINSCENE_H
#define _GAMEWINSCENE_H
#include "cocos2d.h"

class GameWinScene :public cocos2d::Layer
{
public:
	GameWinScene();
	~GameWinScene();
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float d);

	void createButton();

	CREATE_FUNC(GameWinScene);
};
#endif