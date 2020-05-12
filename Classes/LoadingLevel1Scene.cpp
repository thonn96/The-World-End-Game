#include "LoadingLevel1Scene.h"
#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Define.h"
#include "MainMenuScene.h"
#include "InGameScene.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* LoadingLevel1Scene::createScene()
{
	return LoadingLevel1Scene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingLevel1Scene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	

	//Action bar

	auto loadingLevel1 = Sprite::create("loadingLevel1.png");
	loadingLevel1->setPosition(SCREEN_W / 2, 40);
	loadingLevel1->setScale(0.5f);
	addChild(loadingLevel1);

	auto loading1 = ui::LoadingBar::create("loadingLevel1_bar.png");
	loading1->setPosition(loadingLevel1->getPosition());
	loading1->setScale(0.5f);
	loading1->setDirection(ui::LoadingBar::Direction::LEFT);
	loading1->setPercent(0);
	this->addChild(loading1);

	//animation 

	auto animLoading1 = Sprite::create();
	animLoading1->setPosition(Vec2(SCREEN_W / 2 - 150, SCREEN_H / 2 - 150));
	animLoading1->setScale(0.8f);
	addChild(animLoading1);
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(SpriteFrame::create("animationLevel1.png", Rect(35, 4, 61, 109)));
	animFrames.pushBack(SpriteFrame::create("animationLevel1.png", Rect(171, 3, 61, 110)));
	animFrames.pushBack(SpriteFrame::create("animationLevel1.png", Rect(302, 3, 66, 110)));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	animLoading1->runAction(RepeatForever::create(animate));

	//actionMoveBy

	auto actionMoveBy = MoveBy::create(15, Vec2(300, 0));
	animLoading1->runAction(actionMoveBy);
	auto labelPercent = Label::createWithTTF("", "fonts/Marker Felt.ttf", 28);
	labelPercent->setPosition(Vec2(SCREEN_W / 2 + 200, SCREEN_H / 2 - 200));
	labelPercent->setString("0");
	labelPercent->setColor(cocos2d::Color3B::GRAY);

	this->addChild(labelPercent);
	this->schedule([=](float delta){
		int percent = loading1->getPercent();
		percent += 2;
		loading1->setPercent(percent);

		char currentPercent[10];
		sprintf(currentPercent, "%d %%", percent);
		labelPercent->setString(currentPercent);
		if (percent >= 100)
		{
			this->unschedule("updateLoadingBar");
			auto gotoMainMenu = CallFunc::create([]() {
				Director::getInstance()->replaceScene(InGameScene::createScene());
			});
			auto waitAction = Sequence::create(DelayTime::create(1.5f), gotoMainMenu, nullptr);
			runAction(waitAction);
		}
	}, 0.3f, "updateLoadingBar");


	//button back
	auto btnBack = ui::Button::create("back_normal.png", "back_pressed.png");
	btnBack->setPosition(Vec2(50, 50));
	btnBack->addClickEventListener([](Ref* event) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	addChild(btnBack);

	//load some sound + map
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/title.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/ingame.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/title.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/confirm.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/fire.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/killed.wav");




	return true;
}


void LoadingLevel1Scene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
