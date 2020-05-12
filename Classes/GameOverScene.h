#ifndef _GAMEOVERSCENE_H
#define _GAMEOVERSCENE_H
#include "cocos2d.h"

class GameOver :public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float d);




	void createButton();


	CREATE_FUNC(GameOver);
};
#endif