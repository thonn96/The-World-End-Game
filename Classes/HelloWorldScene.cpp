#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Define.h"
#include "MainMenuScene.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//background 

	auto bgActionBarScene = Sprite::create("bgActionBarScene.png");
	bgActionBarScene->setPosition(visibleSize/2);
	addChild(bgActionBarScene);

	//Action bar

	auto loadingBarBG = Sprite::create("loading.png");
	loadingBarBG->setPosition(SCREEN_W/2,40);
	loadingBarBG->setScale(0.5f);
	addChild(loadingBarBG);
	auto loadingBar = ui::LoadingBar::create("loading_bar.png");
	loadingBar->setPosition(loadingBarBG->getPosition());
	loadingBar->setScale(0.5f);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent(0);
	this->addChild(loadingBar);

	this->schedule([=](float delta){
		float percent = loadingBar->getPercent();
		percent++;
		loadingBar->setPercent(percent);
		if (percent >= 100.0f)
		{
			this->unschedule("updateLoadingBar");
			auto gotoMainMenu = CallFunc::create([]() {
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
			});
			auto waitAction = Sequence::create(DelayTime::create(1.5f), gotoMainMenu, nullptr);
			runAction(waitAction);
		}
	},0.1f,"updateLoadingBar");
   
	//particle Action Bar

	auto particleSystem = ParticleSystemQuad::create("particle/prActionBar.plist");
	particleSystem->setPosition(visibleSize/2);
	addChild(particleSystem);

	//load some sound
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/title.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/ingame.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/title.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/confirm.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/fire.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sounds/killed.wav");

	


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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
