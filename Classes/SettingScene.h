#ifndef _SETTING_SCENE_H
#define _SETTINg_SCENE_H
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameSetting.h"
class SettingScene :public cocos2d::Layer
{
public:
	ui::Button* btnSound;
	ui::Button* btnSoundDisable;
	bool isVisibleSound = true;
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
};

#endif