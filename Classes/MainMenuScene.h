#ifndef _MAINMENU_SCENE_H_
#define _MAINMENU_SCENE_H_

#include "ui\CocosGUI.h"
#include "cocos2d.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "AboutScene.h"
#include "GameSetting.h"
using namespace CocosDenshion;
using namespace cocos2d;

class MainMenuScene : public cocos2d::Layer
{
private:
	ui::Button* btnPlay;
public:
	bool isExit = false;
	cocos2d::Layer* controllerLayer;
	static cocos2d::Scene* createScene();
	virtual bool init();
	ui::Button* btnAbout;
	void exitGame();
	void gameExit(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(MainMenuScene);
};

#endif // _MAINMENU_SCENE_H_
