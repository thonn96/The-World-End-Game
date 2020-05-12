#include "SettingScene.h"
#include "AboutScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Define.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* AboutScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AboutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto bgAbout = Sprite::create("bg1.jpg");
	bgAbout->setPosition(visibleSize / 2);
	addChild(bgAbout);

	//title
	auto title = Label::createWithTTF("About", "fonts/njnaruto.ttf", 60);
	title->setColor(Color3B::RED);
	title->enableShadow(Color4B::BLACK);
	title->enableOutline(Color4B::BLACK, 10);
	title->enableGlow(Color4B::BLACK);
	title->setPosition(SCREEN_W / 2, SCREEN_H / 2 + 180);
	addChild(title);

	//particle
	auto paricleEffectAbout = ParticleSystemQuad::create("particle/particleAbout.plist");
	paricleEffectAbout->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2));
	addChild(paricleEffectAbout);

	////About Game
	auto scrollView = ui::ScrollView::create();
	scrollView->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 - title->getContentSize().height));
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setBounceEnabled(true);
	scrollView->setInnerContainerSize(Size(SCREEN_W , SCREEN_H));
	scrollView->setContentSize(Size(SCREEN_W, 400));
	scrollView->setAnchorPoint(Vec2(0.5,0.5));

	auto lableGameInfo = Label::createWithTTF("GAME INFO", "fonts/arial.ttf", 16);
	lableGameInfo->setPosition(Vec2(SCREEN_W/2,SCREEN_H/2 + 200));
	lableGameInfo->setAlignment(TextHAlignment::CENTER);

	auto lableGame = Label::createWithTTF("Name : The World's End", "fonts/arial.ttf", 16);
	lableGame->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 + 175));
	lableGame->setAlignment(TextHAlignment::LEFT);

	auto lableDateDeveloper = Label::createWithTTF("Date developer : 08/01/2018 ", "fonts/arial.ttf", 16);
	lableDateDeveloper->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 + 150));
	lableDateDeveloper->setAlignment(TextHAlignment::LEFT);

	auto lableVersion = Label::createWithTTF(" Version : 1.0 ", "fonts/arial.ttf", 16);
	lableVersion->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 + 125));
	lableVersion->setAlignment(TextHAlignment::LEFT);

	auto lableMember = Label::createWithTTF(" MEMBER INFORMATION ", "fonts/arial.ttf", 16);
	lableMember->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 + 100));
	lableMember->setAlignment(TextHAlignment::LEFT);

	auto infoMember = Label::createWithTTF(
	"       Name                             Adress                                               School \n"
	"\nNguyen Ngoc Tho                     Tam Ky                              Duy Tan Univercity\n"
	"\nNguyen Anh Tuan                Da Nang                                     Duy Tan Univercity \n"
	"\nHuynh Nhat Hoa                  Binh Dinh                                    Duy Tan Univercity \n"
	"\nNguyen Thanh Yen              Da Nang                                     Duy Tan Univercity \n"
	"\n \n\n\n"
	,"fonts/arial.ttf", 16);
	infoMember->setPosition(Vec2(SCREEN_W / 2, SCREEN_H / 2 - 50));
	infoMember->setAlignment(TextHAlignment::LEFT);

	scrollView->addChild(lableGameInfo);
	scrollView->addChild(lableGame);
	scrollView->addChild(lableDateDeveloper);
	scrollView->addChild(lableVersion);
	scrollView->addChild(lableMember);
	scrollView->addChild(infoMember);

	addChild(scrollView);

	//btn back
	auto btnBack = ui::Button::create("back_normal.png", "back_pressed.png");
	btnBack->setScale(0.7f);
	btnBack->setPosition(Vec2(50, 50));
	btnBack->addClickEventListener([](Ref* event) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	addChild(btnBack);
	return true;
}