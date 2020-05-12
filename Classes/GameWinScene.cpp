#include "GameWinScene.h"
#include "Define.h"
#include "ui\CocosGUI.h"
#include "ChooseMapScene.h"
#include "InGameScene.h"
#include "GameSetting.h"
#include "GameOverScene.h"
#include "AboutScene.h"
#include "MainMenuScene.h"
#include "GunMaking.h"
#include "TheEarthSave.h"
USING_NS_CC;

Scene* GameWinScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameWinScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameWinScene::GameWinScene()
{
}

GameWinScene::~GameWinScene()
{
}
bool GameWinScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bgGameWin = Sprite::create("bggamewin.png");
	bgGameWin->setContentSize(visibleSize);
	bgGameWin->setPosition(visibleSize / 2);
	addChild(bgGameWin);

	//particle
	auto particleGameWin = ParticleSystemQuad::create("particle/gamewin.plist");
	particleGameWin->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2));
	addChild(particleGameWin, 2);

	SimpleAudioEngine* audio;
	audio = SimpleAudioEngine::getInstance();
	GameSetting::getInstance()->preLoadSounds();
	if (GameSetting::getInstance()->checkMusic) {
		switch (InGameScene::mapIndex)
		{
		case 1: audio->stopBackgroundMusic("sounds/ingameLV1.mp3"); break;
		case 2: audio->stopBackgroundMusic("sounds/ingameLV2.mp3"); break;
		case 3: audio->stopBackgroundMusic("sounds/sound_ingameLV3.mp3"); break;
		}
		if (GameSetting::getInstance()->checkMusic)
		{
			GameSetting::getInstance()->playSoundEffect("sounds/sound_gamewin.mp3");
		}
		
	}



	createButton();

	scheduleUpdate();
	return true;
}
void GameWinScene::update(float dt)
{

}
void GameWinScene::createButton()
{
	auto btnGameWin = ui::Button::create("btn_gamewin_normal.png", "btn_gamewin_press.png");
	btnGameWin->setPosition(Vec2(SCREEN_W / 2 , SCREEN_H / 2 - 100));
	auto action = Sequence::createWithTwoActions(ScaleTo::create(0.9f, 1.0f), ScaleTo::create(0.9f, 0.9f));
	btnGameWin->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(0.4f), action, nullptr)));
	btnGameWin->addClickEventListener([&](Ref* event){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		if (InGameScene::mapIndex < 4)
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, GunMaking::createScene()));
		}
		else
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainMenuScene::createScene()));
		}
	});
	addChild(btnGameWin,1);
}