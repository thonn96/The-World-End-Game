#include "GameOverScene.h"
#include "Define.h"
#include "ui\CocosGUI.h"
#include "ChooseMapScene.h"
#include "InGameScene.h"
#include "GameSetting.h"
USING_NS_CC;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bgGameOver = Sprite::create("game-over.png");
	bgGameOver->setContentSize(visibleSize);
	bgGameOver->setPosition(visibleSize/ 2);
	addChild(bgGameOver);

	//label
	auto slogan = Label::createWithTTF("You have failed to save the earth,", "fonts/Marker Felt.ttf", 28);
	slogan->setColor(Color3B::ORANGE);
	slogan->enableShadow(Color4B::BLACK);
	slogan->enableOutline(Color4B::BLACK, 10);
	slogan->enableGlow(Color4B::BLACK);
	slogan->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 + 50));
	addChild(slogan);

	auto slogan1 = Label::createWithTTF("do you want to try again ? ", "fonts/Marker Felt.ttf", 28);
	slogan1->setColor(Color3B::ORANGE);
	slogan1->enableShadow(Color4B::BLACK);
	slogan1->enableOutline(Color4B::BLACK, 10);
	slogan1->enableGlow(Color4B::BLACK);
	slogan1->setPosition(Vec2(visibleSize.width / 2 - 30, visibleSize.height / 2 ));
	addChild(slogan1);

	createButton();
	GameSetting::getInstance()->stopBackgroundMusic("sounds/ingameBegin.mp3");
	GameSetting::getInstance()->stopAllEffects();
	if (GameSetting::getInstance()->checkMusic) {
		if (GameSetting::getInstance()->checkMusic)
		{
			GameSetting::getInstance()->playSoundEffect("sounds/sound_gameover.mp3");
		}
	}
	return true;
}

void GameOver::update(float d)
{
}

void GameOver::createButton()
{
	//btn resume choosemap
	auto btnResume = ui::Button::create("btn_play_gameover_normal.png", "btn_play_gameover_press.png");
	btnResume->setScale(0.4f);
	btnResume->setPosition(Vec2(SCREEN_W / 2 , SCREEN_H / 2 - 80));
	auto action = Sequence::createWithTwoActions(ScaleTo::create(0.4f, 0.5f), ScaleTo::create(0.4f, 0.4f));
	btnResume->runAction(RepeatForever::create(Sequence::create(action, DelayTime::create(0.5f), action, nullptr)));
	btnResume->addClickEventListener([](Ref* event) {
		SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, ChooseMapScene::createScene()));
	});
	addChild(btnResume);
}