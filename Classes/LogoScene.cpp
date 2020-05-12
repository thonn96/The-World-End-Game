#include "LogoScene.h"
//#include "MainMenuScene.h"
#include "Define.h"
//#include "GameSetting.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "LoadingScene.h"
#include "MainMenuScene.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* LogoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto logo = Sprite::create("logo.jpg");
	logo->setScale(0.5f);
	logo->setPosition(visibleSize / 2);
	addChild(logo);

	//scale logo

	auto scaleTo = ScaleTo::create(4, 1.0f);
	logo->runAction(scaleTo);

	auto s = Sequence::create(scaleTo, nullptr);
	logo->runAction(s);

	auto gotoActionBarScene = CallFunc::create([]() {
		Director::getInstance()->replaceScene(LoadingScene::createScene());
	});

	//load some sound
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/title.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/ingame.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/title.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/confirm.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/fire.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/killed.wav");
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(MainMenuScene::getInstance()->getVolume());
	//SimpleAudioEngine::getInstance()->setEffectsVolume(GameSetting::getInstance()->getVolume());


	auto waitAction = Sequence::create(DelayTime::create(LOGO_TIME), gotoActionBarScene, nullptr);
	runAction(waitAction);

	return true;
}