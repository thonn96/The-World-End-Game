#include "LoadingScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Define.h"
#include "MainMenuScene.h"
#include "Intro.h"
#include "GameSetting.h"
using namespace CocosDenshion;
USING_NS_CC;
extern int gCount;
Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
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

	//animation 

	auto animLoadingBar = Sprite::create();
	animLoadingBar->setPosition(Vec2(SCREEN_W / 2-100, SCREEN_H / 2 - 200));
	animLoadingBar->setScale(0.3f);
	addChild(animLoadingBar);
	Vector<SpriteFrame*> animFrames;
	animFrames.pushBack(SpriteFrame::create("ani1.png", Rect(0, 0, 100, 120)));
	animFrames.pushBack(SpriteFrame::create("ani2.png", Rect(0, 0, 100, 120)));
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animate = Animate::create(animation);
	animLoadingBar->runAction(RepeatForever::create(animate));

	//actionMoveBy

	auto actionMoveBy = MoveBy::create(15, Vec2(900,0));
	animLoadingBar->runAction(actionMoveBy);
	auto labelPercent = Label::createWithTTF("", "fonts/Marker Felt.ttf", 28);
	labelPercent->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 - 200));
	labelPercent->setString("0");
	labelPercent->setColor(cocos2d::Color3B::GRAY);

	this->addChild(labelPercent);
	this->schedule([=](float delta){
		int percent = loadingBar->getPercent();
		percent+=10 ;
		loadingBar->setPercent(percent);

		char currentPercent[10];
		sprintf(currentPercent, "%d %%", percent);
		labelPercent->setString(currentPercent);
		if (percent >= 100)
		{
			this->unschedule("updateLoadingBar");
			auto gotoMainMenu = CallFunc::create([]() {
				Director::getInstance()->replaceScene(Intro::createScene());
			});
			auto waitAction = Sequence::create(DelayTime::create(0.5f), gotoMainMenu, nullptr);
			runAction(waitAction);
		}
	},0.3f,"updateLoadingBar");
   
	//particle Action Bar

	auto particleSystem = ParticleSystemQuad::create("particle/prActionBar.plist");
	particleSystem->setPosition(visibleSize/2);
	addChild(particleSystem);
    return true;
}

void LoadingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool isLoaded = false;
void LoadingScene::update(float dt)
{
	gCount++;
	if (!isLoaded)
	{
		GameSetting::getInstance()->preLoadSounds();
		isLoaded = true;
	}
	//sau 2s bat dau hien thi loading bar

	if (gCount > 2 * FPS&&gCount <= 4 * FPS)
	{
		//mMcHudBlood->setPercent((gCount - 2 * FPS) * 100 / (2 * FPS));
		if (gCount == 2 * FPS + 2)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("crep/crep3.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("crep/crep4.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("crep/crep6.png");
			//GameSetting::getInstance()->saveData();
			//GameSetting::getInstance()->loadData();

		}
		else if (gCount == 2 * FPS + 30)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("A4.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lv1.png");
		}
		/*else if (gCount == 3 * FPS)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monters/boss1.plist");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Arrow/arrow.plist");
		}
		else if (gCount == 3 * FPS + 20)
		{
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/iconplayer.plist");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items/item.plist");
		}*/
	}
	//Tang loaddingBar len 100% tu giay thu 2, den giay thu 4

	//Sau 4s thi chuyen den MainMenuScene
	if (gCount > 4 * FPS)
	{
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}
