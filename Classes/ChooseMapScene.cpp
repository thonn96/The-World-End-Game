#include "ChooseMapScene.h"
#include "MainMenuScene.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include  "Define.h"
#include "LoadingLevel1Scene.h"
#include "InGameScene.h"
#include "GunMaking.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

Scene* ChooseMapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ChooseMapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseMapScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//background ChooseMapScene

	auto bgChooseMap = Sprite::create("bgChooseMap.png");
	bgChooseMap->setScaleX(0.63f);
	bgChooseMap->setScaleY(0.7f);
	bgChooseMap->setPosition(visibleSize / 2);
	addChild(bgChooseMap);

	//animation Maps

	/*auto animMaps = Sprite::create();
	animMaps->setFlippedX(true);
	animMaps->setPosition(Vec2(visibleSize - Size(135, 70)));
	animMaps->setScale(0.3f);
	addChild(animMaps);

	Vector<SpriteFrame*> animSpriteFrame;
	animSpriteFrame.pushBack(SpriteFrame::create("hd1.png", Rect(0, 0, 400, 400)));
	animSpriteFrame.pushBack(SpriteFrame::create("hd2.png", Rect(0, 0, 400, 400)));
	auto animationMaps = Animation::createWithSpriteFrames(animSpriteFrame,0.3f);
	auto run = Animate::create(animationMaps);
	animMaps->runAction(RepeatForever::create(run));*/

	auto level1 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel.png", [](Ref* sender){
		InGameScene::mapIndex = 1;
		Director::getInstance()->replaceScene(InGameScene::createScene());
	});
	auto level2 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		InGameScene::mapIndex = 2;
		Director::getInstance()->replaceScene(InGameScene::createScene());
	});
	auto level3 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		InGameScene::mapIndex = 3;
		Director::getInstance()->replaceScene(InGameScene::createScene());
	});
	auto level4 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		InGameScene::mapIndex = 4;
		Director::getInstance()->replaceScene(InGameScene::createScene());
	});
	auto level5 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		//Director::getInstance()->replaceScene(PlayGame::createScene());
	});
	auto level6 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		//Director::getInstance()->replaceScene(PlayGame::createScene());
	});
	auto level7 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		//Director::getInstance()->replaceScene(PlayGame::createScene());
	});
	auto level8 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		//Director::getInstance()->replaceScene(PlayGame::createScene());
	});
	auto level9 = MenuItemImage::create("playChooseLevel1.png", "playChooseLevel2.png", [](Ref* sender){
		//Director::getInstance()->replaceScene(PlayGame::createScene());
	});

	level1->setPosition(Vec2(SCREEN_W / 2 - 268, SCREEN_H / 2 + 100));
	level1->setScale(0.3f);

	level2->setPosition(Vec2(SCREEN_W / 2 - 165, SCREEN_H / 2 - 157));
	level2->setScale(0.3f);

	level3->setPosition(Vec2(SCREEN_W / 2 - 50, SCREEN_H / 2 - 33));
	level3->setScale(0.3f);

	level4->setPosition(Vec2(SCREEN_W / 2 - 98, SCREEN_H / 2 + 92));
	level4->setScale(0.3f);

	/*level5->setPosition(Vec2(SCREEN_W / 2 + 55, SCREEN_H / 2 + 78));
	level5->setScale(0.3f);*/


	auto choose = Menu::create(level1, level2, level3, level4, nullptr);
	choose->setPosition(0, 0);
	addChild(choose);


	//button back
	auto btnBack = ui::Button::create("back_normal.png", "back_pressed.png");
	btnBack->setScale(0.7f);
	btnBack->setPosition(Vec2(50, 50));
	btnBack->addClickEventListener([](Ref* event) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	addChild(btnBack);

	//particleTop
	auto paricleEffectTop = ParticleSystemQuad::create("particle/particleSettingTop.plist");
	paricleEffectTop->setPosition(Vec2(SCREEN_W / 2, visibleSize.height));
	addChild(paricleEffectTop);


	return true;
}