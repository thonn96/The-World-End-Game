#include "Running.h"
#include "MainMenuScene.h"
#include "Define.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Size visibleSize1;
cocos2d::Sprite* mPauseLayer1;
char* Running::mapName = NULL;
Scene* Running::createScene(char* mapName2)
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
#if SHOW_PHYSICS	
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

	// 'layer' is an autorelease object
	auto layer = Running::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Running::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize1 = Director::getInstance()->getVisibleSize();
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);

	//create map
	createMap();

	//init physics
	createPhysics();

	createObjects();

	//create controller
	createController();

	//create hud
	createHud();

	//create pause layer
	createPauseLayer();

	//add Listener: touch, key 
	addListener();

	//update
	scheduleUpdate();
	return true;
}

void Running::update(float dt)
{
	//update controller
	updateController();

	//update Bullets
	mPlayer->update();

	//update blood hud of mc
	mMcHudBlood->setPercent(mPlayer->getBlood());

	//update Monsters
	updateMonsters();
}


void Running::addListener()
{
	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Running::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Running::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Running::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//key
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Running::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Running::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//add contact event listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Running::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool Running::onTouchBegan(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}

void Running::onTouchMoved(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
	mCurrentTouchPoint = touch->getLocation();
	log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
}

void Running::onTouchEnded(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
}

void Running::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	mCurrentKey = keyCode;
}

void Running::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	mCurrentKey = EventKeyboard::KeyCode::KEY_NONE;
}

bool Running::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	//bullet of Monster with MC
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		|| (a->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			mMonsters.at(a->getGroup())->bulletHasCollision();
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			mMonsters.at(b->getGroup())->bulletHasCollision();
		}

		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER || b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		{
			mPlayer->setState(Player2::STATE_DAMAGE);
		}
	}

	//bullet mc with ground
	if ((a->getCollisionBitmask() == Model::BITMASK_GROUND && b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET && b->getCollisionBitmask() == Model::BITMASK_GROUND))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			mPlayer->bulletHasCollision(a->getGroup());
		}
		if (b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			mPlayer->bulletHasCollision(b->getGroup());
		}

		//add effect
		auto paricleEffect = ParticleSystemQuad::create("particle/collision.plist");
		paricleEffect->setPosition(a->getPosition());
		addChild(paricleEffect);
	}

	//bullet mc with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET && b->getCollisionBitmask() == Model::BITMASK_MONSTER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			mPlayer->bulletHasCollision(a->getGroup());
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			mPlayer->bulletHasCollision(b->getGroup());
		}

		if (a->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(a->getGroup())->setState(Monster::STATE_BE_HIT);
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(b->getGroup())->setState(Monster::STATE_BE_HIT);
		}

		//add effect
		auto paricleEffect = ParticleSystemQuad::create("particle/collision.plist");
		paricleEffect->setPosition(a->getPosition());
		addChild(paricleEffect);

	}

	//mc with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		|| (a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER || b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		{
			mPlayer->setState(Player2::STATE_DAMAGE);
		}
	}
	return true;
}

void Running::createMap()
{
	//backgroundfar	
	mTileMapFarBackground = TMXTiledMap::create("maps/map_city_farBG.tmx");
	addChild(mTileMapFarBackground);
	//tile map
	mTileMap = TMXTiledMap::create("maps/map_city.tmx");
	mPhysicsLayer = mTileMap->getLayer("physics");
	mObjectGroup = mTileMap->getObjectGroup("objectPos");
	mPhysicsLayer->setVisible(false);
	addChild(mTileMap);
}

void Running::createPhysics()
{
	//world
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize1 + Size(0, 200), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(Model::BITMASK_WORLD);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize1.width / 2, visibleSize1.height / 2 - 100);
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);

	//ground
	Size layerSize = mPhysicsLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mPhysicsLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setCollisionBitmask(Model::BITMASK_GROUND);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setMass(100);
				tileSet->setPhysicsBody(physics);
			}
		}
	}

}

void Running::createObjects() {

	//add effect
	auto paricleEffect = ParticleSnow::create();
	paricleEffect->setPosition(Vec2(visibleSize1.width / 2, visibleSize1.height));
	addChild(paricleEffect);


	auto objects = mObjectGroup->getObjects();

	int monster_count = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		int posX = properties.at("x").asInt();
		int posY = properties.at("y").asInt();
		int type = object.asValueMap().at("type").asInt();
		if (type == Model::MODLE_TYPE_MAIN_CHARACTER)
		{
			mPlayer = new Player2(this);
		}
		else if (type == Model::MODLE_TYPE_MONSTER)
		{
			Monster *monster = new Monster();
			monster->setPosition(Vec2(posX, posY));
			monster->setIndex(monster_count++);
			mMonsters.push_back(monster);
		}
	}
}

void Running::createController()
{
	Director::getInstance()->getVisibleSize();
	//move Left
	mMoveLeftController = Sprite::create("touchleft_normal.png");
	mMoveLeftController->setAnchorPoint(Vec2(0, 0));
	mMoveLeftController->setPosition(Vec2(50, 50));
	addChild(mMoveLeftController);
	mMoveLeftControllerPressed = Sprite::create("touchleft_press.png");
	mMoveLeftControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveLeftControllerPressed->setPosition(mMoveLeftController->getPosition());
	mMoveLeftControllerPressed->setVisible(false);
	addChild(mMoveLeftControllerPressed);

	//move Right
	mMoveRightController = Sprite::create("touchleft_normal.png");
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setAnchorPoint(Vec2(0, 0));
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	addChild(mMoveRightController);
	mMoveRightControllerPressed = Sprite::create("touchleft_press.png");
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setVisible(false);
	addChild(mMoveRightControllerPressed);

	//fire control
	mFireController = ui::Button::create("fire_controller_normal.png", "fire_controller_pressed.png");
	mFireController->setPosition(Vec2(visibleSize1.width - mFireController->getContentSize().width - 75, mFireController->getContentSize().height - 25));
	mFireController->addTouchEventListener(CC_CALLBACK_2(Running::fire, this));
	addChild(mFireController);

	//jump control
	mJumpController = ui::Button::create("jump_normal.png", "jump_press.png");
	mJumpController->setPosition(Vec2(visibleSize1.width - mJumpController->getContentSize().width + 10, mJumpController->getContentSize().height + 50));
	mJumpController->addTouchEventListener(CC_CALLBACK_2(Running::jump, this));
	addChild(mJumpController);

	//pause

	auto btnPause = ui::Button::create("pause_norrmal.png", "pause_pressed.png");
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(visibleSize1 - Size(10, 10));
	btnPause->addTouchEventListener(CC_CALLBACK_2(Running::pause, this));
	addChild(btnPause);

}

void Running::createHud()
{
	auto hud_bg = Sprite::create("hud_bg.png");
	hud_bg->setAnchorPoint(Vec2(0, 0.5));
	hud_bg->setPosition(Vec2(70, SCREEN_H - 60));
	addChild(hud_bg);

	mMcHudBlood = ui::LoadingBar::create("hud_blood.png");
	mMcHudBlood->setAnchorPoint(Vec2(0, 0.5));
	mMcHudBlood->setPosition(hud_bg->getPosition());
	mMcHudBlood->setDirection(ui::LoadingBar::Direction::LEFT);
	mMcHudBlood->setPercent(mPlayer->getBlood());
	addChild(mMcHudBlood);

	auto hud = Sprite::create("hud.png");
	hud->setAnchorPoint(Vec2(0, 0.5));
	hud->setPosition(hud_bg->getPosition() - Vec2(24, 0));
	addChild(hud);
}

void Running::createPauseLayer()
{
	//create pause layer
	mPauseLayer1 = Sprite::create("alpha.png");
	mPauseLayer1->setContentSize(visibleSize1);
	mPauseLayer1->setPosition(visibleSize1 / 2);
	mPauseLayer1->setVisible(false);
	addChild(mPauseLayer1);

	auto btnHome = ui::Button::create("home_normal.png", "home_pressed.png");
	btnHome->setPosition(Vec2(visibleSize1.width / 2 - btnHome->getContentSize().width / 2, visibleSize1.height / 2));
	btnHome->addClickEventListener([](Ref* event) {
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
	});
	mPauseLayer1->addChild(btnHome);

	auto btnResume = ui::Button::create("resume_normal.png", "resume_pressed.png");
	btnResume->setPosition(Vec2(visibleSize1.width / 2 + btnResume->getContentSize().width / 2, visibleSize1.height / 2));
	btnResume->addClickEventListener([](Ref* event) {
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		mPauseLayer1->setVisible(false);
	});
	mPauseLayer1->addChild(btnResume);
}

void Running::updateController()
{
	//cheat key
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW) //move left
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(1, 1);
	}
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) //move right		
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(66, 1);
	}
	if (mCurrentKey == EventKeyboard::KeyCode::KEY_UP_ARROW) //jump
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(130, 1);
	}

	if (mCurrentKey == EventKeyboard::KeyCode::KEY_SPACE) //jump
	{
		mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
		mCurrentTouchPoint = Point(194, 1);
	}

	switch (mCurrentTouchState)
	{
	case ui::Widget::TouchEventType::BEGAN:
	case ui::Widget::TouchEventType::MOVED:

		if (Rect(mMoveLeftController->getPosition().x, mMoveLeftController->getPosition().y, mMoveLeftController->getContentSize().width, mMoveLeftController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW) //move left
		{
			enablePressedControl(true, true);
			moveLeft();
		}
		else
		{
			enablePressedControl(true, false);
		}

		if (Rect(mMoveRightController->getPosition().x, mMoveRightController->getPosition().y, mMoveRightController->getContentSize().width, mMoveRightController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) //move right		
		{
			enablePressedControl(false, true);
			moveRight();
		}
		else
		{
			enablePressedControl(false, false);
		}

		break;
	case ui::Widget::TouchEventType::ENDED:
		enablePressedControl(true, false);
		enablePressedControl(false, false);
		/*if (mPlayer->getSprite()->getNumberOfRunningActions() == 0)
		{
			mPlayer->setState(Player2::STATE_IDLE);
		}*/
		mPlayer->setState(Player2::STATE_IDLE);
		break;
	}

}

void Running::setCenterView(bool isMoveRight)
{
	Vec2 mapMoveDistance = Vec2(0, 0);
	Vec2 mcMoveDistance = Vec2(0, 0);
	if (isMoveRight)
	{
		if (mPlayer->getPosition().x < visibleSize1.width / 2)
		{
			mcMoveDistance = Vec2(Player2::RUN_STEP, 0);
		}
		else
		{
			float mapWidth = mTileMap->getMapSize().width * mTileMap->getTileSize().width;
			if (mTileMap->getPosition().x > -(mapWidth - visibleSize1.width - Player2::RUN_STEP))
			{
				mapMoveDistance = -Vec2(Player2::RUN_STEP, 0);
			}
			else if (mPlayer->getPosition().x <= (visibleSize1.width - Player2::RUN_STEP - mPlayer->getContentSize().width / 2))
			{
				mcMoveDistance = Vec2(Player2::RUN_STEP, 0);
			}
		}
	}
	else
	{
		if (mPlayer->getPosition().x > visibleSize1.width / 2)
		{
			mcMoveDistance = -Vec2(Player2::RUN_STEP, 0);
		}
		else
		{
			if (mTileMap->getPosition().x <= -Player2::RUN_STEP)
			{
				mapMoveDistance = Vec2(Player2::RUN_STEP, 0);
			}
			else if (mPlayer->getPosition().x >= Player2::RUN_STEP + mPlayer->getContentSize().width / 2)
			{
				mcMoveDistance = -Vec2(Player2::RUN_STEP, 0);
			}
		}
	}

	if (mcMoveDistance != Vec2(0, 0)) {
		mPlayer->setPosition(mPlayer->getPosition() + mcMoveDistance);
	}

	if (mapMoveDistance != Vec2(0, 0)) {
		mTileMap->setPosition(mTileMap->getPosition() + mapMoveDistance);
		mTileMapFarBackground->setPosition(mTileMapFarBackground->getPosition() + mapMoveDistance / 5);

		for (int i = 0; i < mMonsters.size(); i++)
		{
			mMonsters.at(i)->setPosition(mMonsters.at(i)->getPosition() + mapMoveDistance);
		}
	}
}

void Running::moveLeft()
{
	if (mPlayer->getCurrentState() != Player2::STATE_DAMAGE)
	{
		mPlayer->moveLeft(onAir);
	}
}

void Running::moveRight()
{
	if (mPlayer->getCurrentState() != Player2::STATE_DAMAGE)
	{
		mPlayer->moveRight(onAir);
	}
}

void Running::fire(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		mPlayer->fire();
		break;
	}
}

void Running::jump(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		mPlayer->jump();
		break;
	}
}

void Running::pause(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		});
		mPauseLayer1->setOpacity(0);
		mPauseLayer1->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer1->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void Running::enablePressedControl(bool isLeft, bool pressed)
{
	if (isLeft) {
		mMoveLeftController->setVisible(!pressed);
		mMoveLeftControllerPressed->setVisible(pressed);
	}
	else {
		mMoveRightController->setVisible(!pressed);
		mMoveRightControllerPressed->setVisible(pressed);
	}
}

void Running::updateMonsters()
{
	for (int i = 0; i < mMonsters.size(); i++)
	{
		if (mMonsters.at(i)->isAlive())
		{
			mMonsters.at(i)->update(mPlayer->getPosition().x < mMonsters.at(i)->getPosition().x);
		}
	}
}