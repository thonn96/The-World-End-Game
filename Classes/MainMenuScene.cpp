#include "MainMenuScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include "ChooseMapScene.h"
#include "Define.h"
using namespace CocosDenshion;
using namespace cocos2d;
USING_NS_CC;

using namespace std;
using namespace CocosDenshion;
Sprite* mExit;
MenuItemImage* itemPlay;
MenuItemImage* itemSetting;
MenuItemImage* itemAbout;
ui::Button* itemExit;
Vector<SpriteFrame*> animSpriteFrame, animSpriteFrame2;

Scene* MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	GameSetting::getInstance()->preLoadSounds();
	if (GameSetting::getInstance()->checkMusic)
	{
		GameSetting::getInstance()->playBackgroundMusic("sounds/musicBG.mp3");
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//background 
	auto bgMainMenuScene = Sprite::create("bgnew.png");
	bgMainMenuScene->setContentSize(visibleSize);
	bgMainMenuScene->setPosition(visibleSize / 2);
	addChild(bgMainMenuScene);
	
	//Button 
	 itemPlay = MenuItemImage::create("btn_start_normal.png", "btn_start_press.png", [](Ref* sender) {
		Director::getInstance()->replaceScene(ChooseMapScene::createScene());
		GameSetting::getInstance()->stopBackgroundMusic("sounds/musicBG.mp3");
		if (GameSetting::getInstance()->checkMusic)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		}
		else
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}	
	});
	 itemSetting = MenuItemImage::create("btn_setting_normal.png", "btn_setting_press.png", [](Ref* sender) {
		Director::getInstance()->replaceScene(SettingScene::createScene());
		if (GameSetting::getInstance()->checkMusic)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		}
		else
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
	});
	 itemAbout = MenuItemImage::create("btn_about_normal.png", "btn_about_press.png", [](Ref* sender) {
		Director::getInstance()->replaceScene(AboutScene::createScene());
		if (GameSetting::getInstance()->checkMusic)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		}
		else
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
		}
	});

	itemExit = ui::Button::create("btn_exit_normal.png", "btn_exit_press.png");
	itemExit->setPosition(Vec2(SCREEN_W / 2 + 360, SCREEN_H / 2 - 200));
	itemExit->setScale(0.7f);
	itemExit->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::gameExit, this));
	addChild(itemExit);


	itemPlay->setPosition(Vec2(SCREEN_W / 2 - 20 , SCREEN_H / 2 - 175));
	auto action = Sequence::createWithTwoActions(ScaleTo::create(0.8f, 1.1f), ScaleTo::create(0.8f, 0.8f));
	itemPlay->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(0.4f), action, nullptr)));
	itemPlay->setScale(0.8f);

	itemAbout->setPosition(Vec2(SCREEN_W / 2 + 360, SCREEN_H / 2 ));
	itemAbout->setScale(0.7f);

	itemSetting->setPosition(Vec2(SCREEN_W / 2 + 360, SCREEN_H / 2 - 100));
	itemSetting->setScale(0.7f);

	/*itemExit->setPosition(Vec2(SCREEN_W / 2 + 360, SCREEN_H / 2 - 200));
	itemExit->setScale(0.7f);*/

	auto menu = Menu::create(itemPlay, itemSetting, itemAbout, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);



	exitGame();
	mExit->setVisible(false);
	scheduleUpdate();
	return true;
}

void MainMenuScene::exitGame()
{
	mExit = Sprite::create("bgExit.png");
	mExit->setPosition(Vec2(SCREEN_W/2,SCREEN_H/2));
	mExit->setScale(0.7f);
	addChild(mExit);

	auto btnYes = ui::Button::create("btn_yes_normal.png","btn_yes_press.png");
	btnYes->setPosition(Vec2(SCREEN_W / 2-235, SCREEN_H / 2 - 180));
	btnYes->addClickEventListener([](Ref* event) {
		exit(0);
	});
	mExit->addChild(btnYes);

	auto btnNo = ui::Button::create("btn_no_normal.png", "btn_no_press.png");
	btnNo->setPosition(Vec2(SCREEN_W / 2 + 80, SCREEN_H / 2 - 180));
	btnNo->addClickEventListener([&](Ref* event) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		mExit->setVisible(false);

		itemPlay->setEnabled(true);
		itemAbout->setEnabled(true);
		itemSetting->setEnabled(true);
		itemExit->setEnabled(true);
	});
	mExit->addChild(btnNo);
}
void MainMenuScene::gameExit(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		});
		isExit = true;
		mExit->setOpacity(0);
		mExit->setVisible(true);

		itemPlay->setEnabled(false);
		itemAbout->setEnabled(false);
		itemSetting->setEnabled(false);
		itemExit->setEnabled(false);
		auto fadeIn = FadeIn::create(0.3f);
		mExit->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}