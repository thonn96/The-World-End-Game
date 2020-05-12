#include "Intro.h"
#include "MainMenuScene.h"
#include "Define.h"

Scene * Intro::createScene()
{
	Layer* layer = Intro::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	return scene;
}

bool Intro::init()
{
	if (!Layer::init())
	{
		return false;
	}

	GameSetting::getInstance()->playBackgroundMusic("sounds/sound_intro.mp3");

	Size screenSize = Director::getInstance()->getVisibleSize();
	Vector<SpriteFrame*> animFrames;
	intro = Sprite::create();
	isIntroFinish = false;
	intro->setPosition(Vec2(screenSize / 2));
	this->addChild(intro);
	char str[100] = { 0 };
	for (int i = 1; i <= 500; i++) {
		sprintf(str, "%s  (%d).jpg", "Intro/intro/trailer", i);
		animFrames.pushBack(SpriteFrame::create(str, Rect(0, 0, 800, 480)));
	}
	mAnimation[0] = Repeat::create(Animate::create(Animation::createWithSpriteFrames(animFrames, 0.1f)), 1);
	CC_SAFE_RETAIN(mAnimation[0]);
	intro->runAction(mAnimation[0]);
	setupSkipButton();
	scheduleUpdate();
	return true;
}

void Intro::update(float dl){
	if (mAnimation[0]->isDone() && !isIntroFinish){
		Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene::createScene()));
		isIntroFinish = true;
	}
}
void Intro::setupSkipButton(){
	skipButton = ui::Button::create("skip.png", "skip.png");
	skipButton->setPosition(Vec2(SCREEN_W/2 + 360, SCREEN_H/2 + 200));
	skipButton->setOpacity(0);
	skipButton->addClickEventListener([&](Ref* event) {
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenuScene::createScene()));
	});
	auto skipLabel = Label::createWithTTF("Skip", "fonts/Marker Felt.ttf", 30);
	skipLabel->setColor(Color3B::ORANGE);
	skipLabel->enableShadow(Color4B::BLACK);
	skipLabel->enableOutline(Color4B::BLACK, 4);
	skipLabel->enableGlow(Color4B::BLACK);
	skipLabel->setPosition(Vec2(SCREEN_W / 2 + 360, SCREEN_H / 2 + 200));
	auto action1 = Sequence::createWithTwoActions(ScaleTo::create(0.6f, 0.7f), ScaleTo::create(1.0f, 1.0f));
	skipLabel->runAction(RepeatForever::create(Sequence::create(action1, DelayTime::create(0.3f), action1, nullptr)));
	this->addChild(skipLabel);
	this->addChild(skipButton);

}