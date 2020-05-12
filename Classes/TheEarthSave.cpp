#include "TheEarthSave.h"
#include "ui\CocosGUI.h"
#include "MainMenuScene.h"
#include "Define.h"

USING_NS_CC;

Scene* TheEarthSave::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TheEarthSave::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
TheEarthSave::TheEarthSave()
{
}
TheEarthSave::~TheEarthSave()
{
}
bool TheEarthSave::init()
{
	if (!Layer::init())
	{
		return false;
	}
	if (GameSetting::getInstance()->checkMusic)
	{
		GameSetting::getInstance()->playBackgroundMusic("sounds/sound_gamewin.mp3");
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bgFinal = Sprite::create("bg_final.png");
	bgFinal->setPosition(visibleSize / 2);
	bgFinal->setContentSize(visibleSize);
	addChild(bgFinal);

	auto particleGreate = ParticleSystemQuad::create("particle/great.plist");
	particleGreate->setPosition(Vec2(SCREEN_W/2 ,SCREEN_H/2 - 250));
	addChild(particleGreate);
	//btn back menu
	auto btnBack = ui::Button::create("back_normal.png", "back_pressed.png");
	btnBack->setScale(0.6f);
	btnBack->setPosition(Vec2(40, 30));
	btnBack->addClickEventListener([](Ref* event) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	addChild(btnBack);

	scheduleUpdate();
	return true;
}
void TheEarthSave::update()
{

}