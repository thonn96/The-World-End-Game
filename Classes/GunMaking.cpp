#include "GunMaking.h"
#include "cocos2d.h"
#include "GunMaking.h"
#include "MainMenuScene.h"
#include "ChooseMapScene.h"
#include "InGameScene.h"

USING_NS_CC;

Sprite* mGunMakingLayer;

Scene* GunMaking::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GunMaking::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
GunMaking::GunMaking()
{
}
GunMaking::~GunMaking()
{
}

bool GunMaking::init()
{
	if (!Layer::init())
	{
		return false;
	}
	GameSetting::getInstance()->preLoadSounds();
	if (GameSetting::getInstance()->checkMusic)
	{
		GameSetting::getInstance()->playBackgroundMusic("sounds/sound_gunmaking.mp3");
	}
	//bg
	auto bgGunMaking = Sprite::create("BG_gunmaking.png");
	bgGunMaking->setContentSize(Director::getInstance()->getVisibleSize());
	bgGunMaking->setPosition(Director::getInstance()->getVisibleSize() / 2);
	addChild(bgGunMaking);

	viewGun1 = Sprite::create("1.png");
	viewGun1->setVisible(false);
	viewGun1->setPosition(Vec2(SCREEN_W / 2 + 30, SCREEN_H / 2 + 125));
	addChild(viewGun1);
	

	//button opacity = 0
	btnSlot1 = ui::Button::create("back_normal.png", "back_pressed.png");
	btnSlot1->setOpacity(0);
	btnSlot1->setScale(0.5f);
	btnSlot1->setPosition(Vec2(SCREEN_W / 2 - 305, SCREEN_H / 2 - 40));
	btnSlot1->addClickEventListener([&](Ref* event) {
		slot1 = false;
		Inventory::getInstance()->addPart(sprite1->getTag() - 100);
		sprite1->setVisible(false);
		btnSlot1->setEnabled(false);
	});
	addChild(btnSlot1);


	btnSlot2 = ui::Button::create("back_normal.png", "back_pressed.png");
	btnSlot2->setOpacity(0);
	btnSlot2->setScale(0.5f);
	btnSlot2->setPosition(Vec2(SCREEN_W / 2 + 25, SCREEN_H / 2 - 40));
	btnSlot2->addClickEventListener([&](Ref* event) {
		slot2 = false;
		Inventory::getInstance()->addPart(sprite2->getTag() - 100);
		sprite2->setVisible(false);
		btnSlot2->setEnabled(false);
	});
	addChild(btnSlot2);
	
	auto viewBullet = Sprite::create("item/bullet.png");
	viewBullet->setScale(0.6f);
	viewBullet->setPosition(Vec2(SCREEN_W / 2 + 305, SCREEN_H / 2 - 40));
	addChild(viewBullet);

	sprite1 = Sprite::create("item/gun1.png");
	sprite1->setVisible(false);
	sprite1->setScale(0.5f);
	sprite1->setPosition(Vec2(SCREEN_W / 2 - 305, SCREEN_H / 2 - 40));
	addChild(sprite1);

	sprite2 = Sprite::create("item/gun2.png");
	sprite2->setScale(0.5f);
	sprite2->setVisible(false);
	sprite2->setPosition(Vec2(SCREEN_W / 2 + 20, SCREEN_H / 2 - 40));
	addChild(sprite2);

	btnGuns.clear();
	createLabel();
	createButton();
	addClickListener();
	scheduleUpdate();
	return true;
}

void GunMaking::createLabel()
{
	auto slgun1 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(1)), "fonts/Marker Felt.ttf", 30);
	slgun1->setColor(Color3B::ORANGE);
	slgun1->enableShadow(Color4B::BLACK);
	slgun1->enableOutline(Color4B::BLACK, 10);
	slgun1->enableGlow(Color4B::BLACK);
	slgun1->setPosition(Vec2(SCREEN_W / 2 - 140, SCREEN_H / 2 - 140));
	addChild(slgun1);

	auto slgun2 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(2)), "fonts/Marker Felt.ttf", 30);
	slgun2->setColor(Color3B::ORANGE);
	slgun2->enableShadow(Color4B::BLACK);
	slgun2->enableOutline(Color4B::BLACK, 10);
	slgun2->enableGlow(Color4B::BLACK);
	slgun2->setPosition(Vec2(SCREEN_W / 2 - 140, SCREEN_H / 2 - 200));
	addChild(slgun2);

	auto slgun3 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(3)), "fonts/Marker Felt.ttf", 30);
	slgun3->setColor(Color3B::ORANGE);
	slgun3->enableShadow(Color4B::BLACK);
	slgun3->enableOutline(Color4B::BLACK, 10);
	slgun3->enableGlow(Color4B::BLACK);
	slgun3->setPosition(Vec2(SCREEN_W / 2 + 20, SCREEN_H / 2 - 140));
	addChild(slgun3);

	auto slgun4 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(4)), "fonts/Marker Felt.ttf", 30);
	slgun4->setColor(Color3B::ORANGE);
	slgun4->enableShadow(Color4B::BLACK);
	slgun4->enableOutline(Color4B::BLACK, 10);
	slgun4->enableGlow(Color4B::BLACK);
	slgun4->setPosition(Vec2(SCREEN_W / 2 + 20, SCREEN_H / 2 - 200));
	addChild(slgun4);

	auto slgun5 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(5)), "fonts/Marker Felt.ttf", 30);
	slgun5->setColor(Color3B::ORANGE);
	slgun5->enableShadow(Color4B::BLACK);
	slgun5->enableOutline(Color4B::BLACK, 10);
	slgun5->enableGlow(Color4B::BLACK);
	slgun5->setPosition(Vec2(SCREEN_W / 2 + 190, SCREEN_H / 2 - 140));
	addChild(slgun5);

	auto slgun6 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getPart(6)), "fonts/Marker Felt.ttf", 30);
	slgun6->setColor(Color3B::ORANGE);
	slgun6->enableShadow(Color4B::BLACK);
	slgun6->enableOutline(Color4B::BLACK, 10);
	slgun6->enableGlow(Color4B::BLACK);
	slgun6->setPosition(Vec2(SCREEN_W / 2 + 190, SCREEN_H / 2 - 200));
	addChild(slgun6);

	labels.push_back(slgun1);
	labels.push_back(slgun2);
	labels.push_back(slgun3);
	labels.push_back(slgun4);
	labels.push_back(slgun5);
	labels.push_back(slgun6);




	//current gun 
	auto gUn1 = Sprite::create("item/rpk74.png");
	gUn1->setScale(0.7f);
	gUn1->setPosition(Vec2(SCREEN_W / 2 - 340, SCREEN_H / 2 + 200));
	addChild(gUn1);
	auto curBullet1 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(1)), "fonts/Marker Felt.ttf", 20);
	curBullet1->setPosition(Vec2(SCREEN_W / 2 - 250, SCREEN_H / 2 + 200));
	curBullet1->setColor(Color3B::ORANGE);
	curBullet1->enableShadow(Color4B::BLACK);
	curBullet1->enableOutline(Color4B::BLACK, 10);
	curBullet1->enableGlow(Color4B::BLACK);
	addChild(curBullet1);

	auto gUn2 = Sprite::create("item/fnscar.png");
	gUn2->setScale(0.7f);
	gUn2->setPosition(Vec2(SCREEN_W / 2 - 340, SCREEN_H / 2 + 140));
	addChild(gUn2);
	auto curBullet2 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(2)), "fonts/Marker Felt.ttf", 20);
	curBullet2->setPosition(Vec2(SCREEN_W / 2 - 250, SCREEN_H / 2 + 140));
	curBullet2->setColor(Color3B::ORANGE);
	curBullet2->enableShadow(Color4B::BLACK);
	curBullet2->enableOutline(Color4B::BLACK, 10);
	curBullet2->enableGlow(Color4B::BLACK);
	addChild(curBullet2);

	auto gUn3 = Sprite::create("item/waltherp99.png");
	gUn3->setScale(0.7f);
	gUn3->setPosition(Vec2(SCREEN_W / 2 - 340, SCREEN_H / 2 + 80));
	addChild(gUn3);
	auto curBullet3 = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(3)), "fonts/Marker Felt.ttf", 20);
	curBullet3->setPosition(Vec2(SCREEN_W / 2 - 250, SCREEN_H / 2 + 80));
	curBullet3->setColor(Color3B::ORANGE);
	curBullet3->enableShadow(Color4B::BLACK);
	curBullet3->enableOutline(Color4B::BLACK, 10);
	curBullet3->enableGlow(Color4B::BLACK);
	addChild(curBullet3);


	labels.push_back(curBullet1);
	labels.push_back(curBullet2);
	labels.push_back(curBullet3);

}

void GunMaking::createButton()
{
	auto gun1 = ui::Button::create("item/gun1.png");
	gun1->setTag(21);
	gun1->setScale(0.5f);
	gun1->setPosition(Vec2(SCREEN_W / 2 - 200, SCREEN_H / 2 - 140));
	addChild(gun1);

	auto gun2 = ui::Button::create("item/gun2.png");
	gun2->setScale(0.5f);
	gun2->setPosition(Vec2(SCREEN_W / 2 - 195, SCREEN_H / 2 - 200));
	addChild(gun2);

	auto gun3 = ui::Button::create("item/gun3.png");
	gun3->setScale(0.6f);
	gun3->setPosition(Vec2(SCREEN_W / 2 - 40, SCREEN_H / 2 - 140));
	addChild(gun3);

	auto gun4 = ui::Button::create("item/gun4.png");
	gun4->setScale(0.6f);
	gun4->setPosition(Vec2(SCREEN_W / 2 - 35, SCREEN_H / 2 - 200));
	addChild(gun4);

	auto gun5 = ui::Button::create("item/gun5.png");
	gun5->setScale(0.5f);
	gun5->setPosition(Vec2(SCREEN_W / 2 + 110, SCREEN_H / 2 - 140));
	addChild(gun5);

	auto gun6 = ui::Button::create("item/gun6.png");
	gun6->setScale(0.5f);
	gun6->setPosition(Vec2(SCREEN_W / 2 + 125, SCREEN_H / 2 - 200));
	addChild(gun6);

	btnGuns.push_back(gun1);
	btnGuns.push_back(gun2);
	btnGuns.push_back(gun3);
	btnGuns.push_back(gun4);
	btnGuns.push_back(gun5);
	btnGuns.push_back(gun6);

	//button next
	auto btnNext = ui::Button::create("btn_nextlevel_normal.png", "btn_nextlevel_press.png");
	btnNext->setScale(0.7f);
	btnNext->setPosition(Vec2(SCREEN_W / 2 + 340, SCREEN_H / 2 - 200));
	btnNext->addClickEventListener([&](Ref* event){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("sounds/sound_click.mp3");
		if (InGameScene::mapIndex < 4)
		{
			InGameScene::mapIndex++;
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, InGameScene::createScene()));
		}
		else
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainMenuScene::createScene()));
		}
	});
	addChild(btnNext);

	//scale button 
	float timeEachScale = 0.45f;
	auto actionScaleYDown = ScaleTo::create(timeEachScale, 0.8f, 0.7f, 0.8f);
	auto actionScaleYUp = ScaleTo::create(timeEachScale, 0.8f, 0.8f, 0.8f);
	auto actionScaleXDown = ScaleTo::create(timeEachScale, 0.7f, 0.8f, 0.8f);
	auto actionScaleXUp = ScaleTo::create(timeEachScale, 0.8f, 0.8f, 0.8f);
	auto scaleSequence = Sequence::create(actionScaleYDown, actionScaleYUp, actionScaleXDown, actionScaleXUp, nullptr);
	auto scaleButton = RepeatForever::create(scaleSequence);

	//button create gun
	btnCreateGun = ui::Button::create("shop_gun_normal.png", "shop_gun_press.png");
	btnCreateGun->setScale(0.4f);
	btnCreateGun->setPosition(Vec2(SCREEN_W / 2 - 310, SCREEN_H / 2 - 170));
	btnCreateGun->runAction(scaleButton);
	addChild(btnCreateGun);
}

void GunMaking::addClickListener()
{
	btnGuns.at(0)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun1.png");
			sprite1->setVisible(true);
			sprite1->setTag(301);
			slot1 = true;
			Inventory::getInstance()->dePart(301);
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun1.png");
			sprite2->setVisible(true);
			sprite2->setTag(301);
			Inventory::getInstance()->dePart(301);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});
	btnGuns.at(1)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun2.png");
			sprite1->setVisible(true);
			sprite1->setTag(302);
			Inventory::getInstance()->dePart(302);
			slot1 = true;
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun2.png");
			sprite2->setVisible(true);
			sprite2->setTag(302);
			Inventory::getInstance()->dePart(302);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});
	btnGuns.at(2)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun3.png");
			sprite1->setVisible(true);
			sprite1->setTag(303);
			Inventory::getInstance()->dePart(303);
			slot1 = true;
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun3.png");
			sprite2->setVisible(true);
			sprite2->setTag(303);
			Inventory::getInstance()->dePart(303);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});

	btnGuns.at(3)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun4.png");
			sprite1->setVisible(true);
			sprite1->setTag(304);
			Inventory::getInstance()->dePart(304);
			slot1 = true;
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun4.png");
			sprite2->setVisible(true);
			sprite2->setTag(304);
			Inventory::getInstance()->dePart(304);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});

	btnGuns.at(4)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun5.png");
			sprite1->setVisible(true);
			sprite1->setTag(305);
			Inventory::getInstance()->dePart(305);
			slot1 = true;
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun5.png");
			sprite2->setVisible(true);
			sprite2->setTag(305);
			Inventory::getInstance()->dePart(305);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});

	btnGuns.at(5)->addClickEventListener([&](Ref* event) {
		if (slot1 && slot2)
		{
			return;
		}
		if (!slot1)
		{
			sprite1->setTexture("item/gun6.png");
			sprite1->setVisible(true);
			sprite1->setTag(306);
			Inventory::getInstance()->dePart(306);
			slot1 = true;
			btnSlot1->setEnabled(true);
		}
		else if (!slot2)
		{
			sprite2->setTexture("item/gun6.png");
			sprite2->setVisible(true);
			sprite2->setTag(306);
			Inventory::getInstance()->dePart(306);
			slot2 = true;
			btnSlot2->setEnabled(true);
		}
	});

	btnCreateGun->addClickEventListener([&](Ref* event) {
		if (sprite1->getTag() + sprite2->getTag() == 301 + 302)
		{
			if (GameSetting::getInstance()->checkMusic)
			{
				GameSetting::getInstance()->stopBackgroundMusic("sounds/sound_gunmaking.mp3");
				GameSetting::getInstance()->playSoundEffect("sounds/sound_creategun.mp3");
				//GameSetting::getInstance()->resumeAllEffects();
			}
			viewGun1->setTexture("item/rpk74.png");
			viewGun1->setVisible(true);
			Inventory::getInstance()->setGun(1);
		}
		else if (sprite1->getTag() + sprite2->getTag() == 303 + 304)
		{
			if (GameSetting::getInstance()->checkMusic)
			{
				GameSetting::getInstance()->stopBackgroundMusic("sounds/sound_gunmaking.mp3");
				GameSetting::getInstance()->playSoundEffect("sounds/sound_creategun.mp3");
				//GameSetting::getInstance()->resumeAllEffects();
			}
			viewGun1->setTexture("item/fnscar.png");
			viewGun1->setVisible(true);
			Inventory::getInstance()->setGun(2);
		}
		else if (sprite1->getTag() + sprite2->getTag() == 305 + 306)
		{
			if (GameSetting::getInstance()->checkMusic)
			{
				GameSetting::getInstance()->stopBackgroundMusic("sounds/sound_gunmaking.mp3");
				GameSetting::getInstance()->playSoundEffect("sounds/sound_creategun.mp3");
				//GameSetting::getInstance()->resumeAllEffects();
			}
			viewGun1->setTexture("item/waltherp99.png");
			viewGun1->setVisible(true);
			Inventory::getInstance()->setGun(3);
		}
		else
		{
			if (GameSetting::getInstance()->checkMusic)
			{
				GameSetting::getInstance()->stopBackgroundMusic("sounds/sound_gunmaking.mp3");
				GameSetting::getInstance()->playSoundEffect("sounds/fail_CreateGun.mp3");
				//GameSetting::getInstance()->resumeAllEffects();
			}	
		}
		slot1 = false;
		slot2 = false;
		sprite1->setTag(-1);
		sprite2->setTag(-1);
		sprite1->setVisible(false);
		sprite2->setVisible(false);
	});
}

void GunMaking::update(float d)
{
	labels.at(0)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(1)));
	labels.at(1)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(2)));
	labels.at(2)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(3)));
	labels.at(3)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(4)));
	labels.at(4)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(5)));
	labels.at(5)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(6)));
	labels.at(6)->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(1)));
	labels.at(7)->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(2)));
	labels.at(8)->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(3)));

	for (int i = 0; i < 6; i++)
	{
		if (Inventory::getInstance()->getPart(i+1) == 0)
		{
			btnGuns.at(i)->setEnabled(false);
		}
		else
		{
			btnGuns.at(i)->setEnabled(true);
		}
	}
}