#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Define.h"
#include "GameSetting.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	GameSetting::getInstance()->preLoadSounds();
	GameSetting::getInstance()->setBackgroundMusicVolum(0.5f);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bgSetting = Sprite::create("bgMenu.jpg");
	bgSetting->setPosition(visibleSize / 2);
	addChild(bgSetting);

	//title

	auto title = Label::createWithTTF("Setting", "fonts/njnaruto.ttf", 60);
	title->setColor(Color3B::RED);
	title->enableShadow(Color4B::BLACK);
	title->enableOutline(Color4B::BLACK, 10);
	title->enableGlow(Color4B::BLACK);
	title->setPosition(SCREEN_W/2, SCREEN_H/2 + 180);
	addChild(title);

	//checkbox
	//checkbox Musiccheckbox_checked
	auto checkboxMusic = ui::CheckBox::create("music_normal.png", "music_press.png");
	checkboxMusic->setPosition(Vec2(SCREEN_W / 2 -50, SCREEN_H / 2 + 90));
	checkboxMusic->setScale(0.5f);
	checkboxMusic->addEventListener([&](Ref* sender, ui::CheckBox::EventType type){
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			GameSetting::getInstance()->checkMusic = false;
			GameSetting::getInstance()->stopBackgroundMusic("sounds/musicBG.mp3");
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			GameSetting::getInstance()->checkMusic = true;
			GameSetting::getInstance()->playBackgroundMusic("sounds/musicBG.mp3");
			break;
		default:
			break;
		}
	});
	if (GameSetting::getInstance()->getMusic())
	{
		checkboxMusic->setSelected(false);
	}
	else
	{
		checkboxMusic->setSelected(true);
	}
	log("asdasdsads %d", GameSetting::getInstance()->getMusic());
	addChild(checkboxMusic);
	
	//title Music 
	auto txtMusic = Label::createWithTTF("Music", "fonts/njnaruto.ttf", 30);
	txtMusic->setColor(Color3B::ORANGE);
	txtMusic->enableShadow(Color4B::BLACK);
	txtMusic->enableOutline(Color4B::BLACK, 10);
	txtMusic->enableGlow(Color4B::BLACK);
	txtMusic->setPosition(Vec2(SCREEN_W/2 + 50 , SCREEN_H/2 + 90));
	addChild(txtMusic);

	//checkbox Sound
	auto checkboxSound = ui::CheckBox::create("sound_normal.png", "sound_press.png"); 
	checkboxSound->setPosition(Vec2(SCREEN_W / 2 -50, SCREEN_H / 2 - 20));
	checkboxSound->setScale(0.5f);
	checkboxSound->addEventListener([&](Ref* sender, ui::CheckBox::EventType type){
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			GameSetting::getInstance()->checkSound = false;
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			GameSetting::getInstance()->checkSound = true;
			break;
		default:
			break;
		}
	});
	if (GameSetting::getInstance()->getSound())
	{
		checkboxSound->setSelected(false);
	}
	else
	{
		checkboxSound->setSelected(true);
	}
	addChild(checkboxSound);
	
	//title Sound 
	auto txtSound = Label::createWithTTF("Sound", "fonts/njnaruto.ttf", 30);
	txtSound->setColor(Color3B::ORANGE);
	txtSound->enableShadow(Color4B::BLACK);
	txtSound->enableOutline(Color4B::BLACK, 10);
	txtSound->enableGlow(Color4B::BLACK);
	txtSound->setPosition(Vec2(SCREEN_W / 2 + 50, SCREEN_H / 2 -20));
	addChild(txtSound);

	//volum slider

	auto slider = ui::Slider::create();
	slider->setAnchorPoint(Vec2(0, 0.5));
	slider->loadBarTexture("slider_bar_bg.png");
	slider->loadSlidBallTextures("slider_ball_normal.png", "slider_ball_pressed.png", "slider_ball_disable.png");
	slider->loadProgressBarTexture("slider_bar_pressed.png");
	slider->setPosition(Vec2(SCREEN_W/2 - 70, SCREEN_H/2 - 150));
	slider->setPercent(GameSetting::getInstance()->getVolume());
	slider->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::ENDED:
			GameSetting::getInstance()->setVolume(slider->getPercent());
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSetting::getInstance()->getVolume() / 100.0f);
			CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(GameSetting::getInstance()->getVolume() / 100.0f);
			break;
		}
	});

	addChild(slider);

	//title Volume Slider 
	auto txtVolume = Label::createWithTTF("Volume :", "fonts/njnaruto.ttf", 30);
	txtVolume->setColor(Color3B::ORANGE);
	txtVolume->enableShadow(Color4B::BLACK);
	txtVolume->enableOutline(Color4B::BLACK, 10);
	txtVolume->enableGlow(Color4B::BLACK);
	txtVolume->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 - 100));
	addChild(txtVolume);

	//button back
	auto btnBack = ui::Button::create("back_normal.png", "back_pressed.png");
	btnBack->setScale(0.7f);
	btnBack->setPosition(Vec2(50, 50));
	btnBack->addClickEventListener([](Ref* event) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	addChild(btnBack);


	//particleBottom
	auto prMainMenuScene = ParticleSystemQuad::create("particle/particle_fire_MainMenuScene.plist");
	prMainMenuScene->setPosition(Vec2(SCREEN_W / 2, 0));
	addChild(prMainMenuScene);

	return true;
}