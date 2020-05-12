#include "InGameScene.h"
#include "MainMenuScene.h"
#include "GunMaking.h"
#include "GameOverScene.h"
#include "Define.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "Monster.h"
#include "GameWinScene.h"
#include "ChooseMapScene.h"
#include "TheEarthSave.h"

USING_NS_CC;
using namespace CocosDenshion;

Sprite* logGun;
Size visibleSize;
Sprite* mItemPickedLayer;
Sprite* mPauseLayer;
int InGameScene::mapIndex = 1;
Sprite* item;
std::vector<Label*> labelNumber;
Scene* InGameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	// 'layer' is an autorelease object
	auto layer = InGameScene::create();
	layer->setTag(10);

	// add layer as a child to scene
	scene->addChild(layer);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1100.0f));

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	viewLayer = Layer::create();
	controllerLayer = Layer::create();
	addChild(viewLayer, 1);
	viewLayer->addChild(controllerLayer);

	isCompletedStage = false;
	boomC = 0;

	if (mapIndex != 1)
	{
		numBullets = Label::createWithTTF(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(Inventory::getInstance()->getCurrentGun())), "fonts/Marker Felt.ttf", 15);
		numBullets->setColor(Color3B::ORANGE);
		numBullets->enableOutline(Color4B::BLACK, 10);
		numBullets->enableGlow(Color4B::BLACK);
		numBullets->setPosition(SCREEN_W / 2 - 230, SCREEN_H / 2 + 170);
		viewLayer->addChild(numBullets);

		logGun = Sprite::create("item/rpk74.png");
		logGun->setScale(0.6f);
		logGun->setPosition(SCREEN_W / 2 - 290, SCREEN_H / 2 + 170);
		viewLayer->addChild(logGun);
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
	SimpleAudioEngine* audio;
	audio = SimpleAudioEngine::getInstance();
	GameSetting::getInstance()->preLoadSounds();
	if (GameSetting::getInstance()->checkMusic) {
		switch (mapIndex)
		{
		case 1: audio->playBackgroundMusic("sounds/ingameBegin.mp3", true); break;
		case 2: audio->playBackgroundMusic("sounds/ingameLV1.mp3", true); break;
		case 3: audio->playBackgroundMusic("sounds/ingameLV2.mp3", true); break;
		case 4: audio->playBackgroundMusic("sounds/sound_ingameLV3.mp3", true); break;
		
		}
	}
	audio->setBackgroundMusicVolume(0.5);

	//create map
	createMap();

	//init physics
	createPhysics();

	//create Object
	createObjects();

	//create controller
	createController();

	//create hud
	createHud();

	//create item pick layer
	createItemPickedLayer();

	//create pause layer
	createPauseLayer();

	//add Listener: touch, key 
	addListener();

	//update
	scheduleUpdate();

	//setCenterView();

	return true;
}

void InGameScene::update(float dt)
{
	setCenterView(mPlayer->getPosition());
	if (isCompletedStage)
	{
		Director::getInstance()->replaceScene(GameWinScene::createScene());
	}
	
	if (!isPause)
	{
		if (!mItemPickedLayer->isVisible())
		{
			controllerLayer->setVisible(true);
		}
		if (mPlayer->getLive()== 0)
		{
			Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, GameOver::createScene()));
		}

		viewLayer->setPosition(-this->getPosition());

		if (curPos.y > mPlayer->getPosition().y)
		{
			mPlayer->setIsFalling(true);
		}
		else
		{
			mPlayer->setIsFalling(false);
		}

		curPos = mPlayer->getPosition();
	
		//update controller
		updateController();

		//update Bullets
		mPlayer->update();

		//update blood hud of mc
		mMcHudBlood->setPercent(mPlayer->getBlood());

		//update xp hud of mc
		mMcHudXP->setPercent(mPlayer->getLive()*100/5);

		//update Monsters
		updateMonsters();

		for (FlyGround *f : flyGrounds)
		{
			f->update();
		}
	}

	if (mapIndex == 1)
	{
		for (Monster* a : mMonsters)
		{
			if (a->isAlive())
			{
				break;
			}
			if (mPlayer->getPosition().x > 3022)
			{
				isCompletedStage = true;
			}
		}
	}

	int hpBoss = mMonsters.at(mMonsters.size() - 1)->getHP();
	if (hpBoss <= 3000 && mMonsters.at(mMonsters.size() - 1)->isAlive())
	{
		for (BomItem *b : bomItems)
		{
			if (!b->getSprite()->isVisible())
			{
				b->setAlive(true);
				break;
			}
		}
	}

	if (isBoomActivated)
	{
		if (isBoomSoundOn)
		{
			GameSetting::getInstance()->stopBackgroundMusic("sounds/ingameLV1.mp3");
			GameSetting::getInstance()->playSoundEffect("sounds/boomboom.mp3");
			isBoomSoundOn = false;
		}
		if (gameTimer >= 32 * 20)
		{
			auto boomDie = ParticleSystemQuad::create("particle/particle_boomboom.plist");
			boomDie->setPosition(mMonsters.at(mMonsters.size() - 1)->getPosition());
			addChild(boomDie);
			auto fireGround = ParticleSystemQuad::create("particle/particle_firefire.plist");
			fireGround->setPosition(Vec2(800, mMonsters.at(mMonsters.size() - 1)->getPosition().y - 25));
			addChild(fireGround);

			for (BomItem *b : bomItems)
			{
				auto boom1 = ParticleSystemQuad::create("particle/particle_boomboom2.plist");
				boom1->setPosition(b->getPosition() + Vec2(0, -10));
				addChild(boom1);
				b->setAlive(false);
			}

			auto boomDie2 = ParticleSystemQuad::create("particle/particle_firefire.plist");
			boomDie2->setPosition(Vec2(mMonsters.at(mMonsters.size() - 1)->getPosition().x + 30, mMonsters.at(mMonsters.size() - 1)->getPosition().y - 30));
			addChild(boomDie2);
			mMonsters.at(mMonsters.size() - 1)->setAlive(false);
			isBoomActivated = false;
			Director::getInstance()->replaceScene(TransitionFade::create(2.5f, TheEarthSave::createScene()));
		}
		else
		{
			gameTimer++;
		}
	}
	else
	{
		gameTimer = 0;
	}
}

void InGameScene::addListener()
{
	//touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//key
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InGameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//add contact event listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(InGameScene::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(InGameScene::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(InGameScene::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(InGameScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

Point touchChangeGun = Point(-1, -1);
bool InGameScene::onTouchBegan(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	if (Rect(0, 370, 100, 60).containsPoint(mCurrentTouchPoint) && mapIndex != 1)
	{
		touchChangeGun = mCurrentTouchPoint;
	}
	return true;
}

void InGameScene::onTouchMoved(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
	mCurrentTouchPoint = touch->getLocation();
	if (Rect(0, 370, 100, 60).containsPoint(mCurrentTouchPoint) && mapIndex != 1)
	{
		if (touchChangeGun == Point(-1, -1))
		{
			touchChangeGun = touch->getLocation();
		}
	}
	//log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
}

void InGameScene::onTouchEnded(Touch* touch, Event  *event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);

	if (mapIndex != 1)
	{
		if (touchChangeGun.x < touch->getLocation().x && touchChangeGun != Point(-1, -1))
		{
			dynamic_cast<Player2*>(mPlayer)->changeGun(true);
			
			numBullets->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(Inventory::getInstance()->getCurrentGun())));
		}
		else if (touchChangeGun.x > touch->getLocation().x)
		{
			dynamic_cast<Player2*>(mPlayer)->changeGun(false);

			numBullets->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(Inventory::getInstance()->getCurrentGun())));
		}
		switch (Inventory::getInstance()->getCurrentGun())
		{
		case 1:
			logGun->setTexture("item/rpk74.png");
			break;
		case 2:
			logGun->setTexture("item/fnscar.png");
			break;
		case 3:
			logGun->setTexture("item/waltherp99.png");
			break;
		}
		touchChangeGun = Point(-1, -1);
	}
}

void InGameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	mCurrentKey = keyCode;
}

void InGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	mCurrentKey = EventKeyboard::KeyCode::KEY_NONE;
}

bool InGameScene::onContactBegin(PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	//bullet of Monster with MC
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		|| (a->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (GameSetting::getInstance()->checkMusic)
		{
		SimpleAudioEngine::getInstance()->playEffect("sounds/vacham_physic.mp3");
		}
		auto paricleBloodOfMC = ParticleSystemQuad::create("particle/dame_blood.plist");
		if (a->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			mMonsters.at(a->getGroup())->bulletHasCollision();
			mPlayer->getDamage(mMonsters.at(a->getGroup())->getDamage());
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_MONSTER_BULLET)
		{
			mMonsters.at(b->getGroup())->bulletHasCollision();
			mPlayer->getDamage(mMonsters.at(b->getGroup())->getDamage());
		}

		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER || b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		{
			paricleBloodOfMC->setPosition(mPlayer->getPosition() + Vec2(0, 60));
			mPlayer->setState(Player2::STATE_DAMAGE);
		}
		addChild(paricleBloodOfMC);
	}


	// mc ground
	if ((a->getCollisionBitmask() == Model::BITMASK_GROUND && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_GROUND))
	{
		onAir = false;
		jumpC = 0;
		mPlayer->setIsFalling(false);
		if (a->getCollisionBitmask() == Model::BITMASK_GROUND) {
			if (b->getPosition().y < a->getPosition().y + 16 && b->getPosition().y > a->getPosition().y - 17) {
				mPlayer->setCanRun(false);
			}
			else mPlayer->setCanRun(true);
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_GROUND) {
			if (a->getPosition().y < b->getPosition().y + 16 && a->getPosition().y > b->getPosition().y - 17) {
				mPlayer->setCanRun(false);
			}
			else mPlayer->setCanRun(true);
		}
	}

	//bullet mc with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET && b->getCollisionBitmask() == Model::BITMASK_MONSTER))
	{
		auto paricleEffect = ParticleSystemQuad::create("particle/collision.plist");
		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			dynamic_cast<Player2*> (mPlayer)->bulletHasCollision(a->getGroup());
			mMonsters.at(b->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffect->setPosition(mMonsters.at(b->getGroup())->getPosition() + Vec2(0, 50));
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_PLAYER_BULLET)
		{
			dynamic_cast<Player2*> (mPlayer)->bulletHasCollision(b->getGroup());
			mMonsters.at(a->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffect->setPosition(mMonsters.at(a->getGroup())->getPosition() + Vec2(0, 50));
		}

		paricleEffect->setScale(0.5f);
		addChild(paricleEffect);
	}

	// attack from mc with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER_PUNCH)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER_PUNCH && b->getCollisionBitmask() == Model::BITMASK_MONSTER))
	{
		auto paricleEffect = ParticleSystemQuad::create("particle/collision.plist");
		if (a->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(a->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffect->setPosition(mMonsters.at(a->getGroup())->getPosition() + Vec2(0, 50));
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(b->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffect->setPosition(mMonsters.at(b->getGroup())->getPosition() + Vec2(0, 50));
		}
		paricleEffect->setScale(0.5f);
		addChild(paricleEffect);	
	}

	// attack knife of MC with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER_KNIFE)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER_KNIFE && b->getCollisionBitmask() == Model::BITMASK_MONSTER))
	{
		auto paricleEffectKnife = ParticleSystemQuad::create("particle/collision.plist");
		if (a->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(a->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffectKnife->setPosition(mMonsters.at(a->getGroup())->getPosition() + Vec2(0, 50));
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		{
			mMonsters.at(b->getGroup())->setState(Monster::STATE_BE_HIT);
			paricleEffectKnife->setPosition(mMonsters.at(b->getGroup())->getPosition() + Vec2(0, 50));
		}
		paricleEffectKnife->setScale(0.5f);
		addChild(paricleEffectKnife);
	}

	//mc with monster
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		|| (a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		if (a->getCollisionBitmask() == Model::BITMASK_PLAYER || b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		{
			mPlayer->setState(PlayerModel::STATE_DAMAGE);
		}
	}


	//mc with item
	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == ItemModel::BITMASK_ITEM)
		|| (a->getCollisionBitmask() == ItemModel::BITMASK_ITEM && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		int type;
		auto paricleEffect = ParticleSystemQuad::create("particle/mcwithitem.plist");
		if (GameSetting::getInstance()->checkSound)
		{
			SimpleAudioEngine::getInstance()->playEffect("SoundsEffect/selectItem.wav");
		}
		if (a->getCollisionBitmask() == ItemModel::BITMASK_ITEM)
		{
			a->setEnabled(false);
			Sprite* sprite = (Sprite*) a->getNode();
			sprite->setVisible(false);
			type = sprite->getTag();
			paricleEffect->setPosition(sprite->getPosition());
		}
		if (b->getCollisionBitmask() == ItemModel::BITMASK_ITEM)
		{
			b->setEnabled(false);
			Sprite* sprite = (Sprite*) b->getNode();
			sprite->setVisible(false);
			paricleEffect->setPosition(sprite->getPosition());
			type = sprite->getTag();
		}
		if (type == 210)
		{
			isCompletedStage = true;
		}
		addChild(paricleEffect);
		Inventory::getInstance()->addPart(type);
	}

	// mc vs wall
	if ((a->getCollisionBitmask() == Model::BITMASK_WALL && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WALL)) 
	{
		onAir = false;
		jumpC = 0;
		mPlayer->setIsFalling(false);
		if (a->getCollisionBitmask() == Model::BITMASK_WALL) 
		{
			if (a->getPosition().y + 40 > mPlayer->getSprite()->getPosition().y) 
			{
				mPlayer->setCanRun(false);
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_WALL) 
		{
			if (b->getPosition().y + 40 > mPlayer->getSprite()->getPosition().y) 
			{
				mPlayer->setCanRun(false);
			}
		}
	}
	// bom vs mc
	if ((a->getCollisionBitmask() == 666 && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == 666))
	{
		if (GameSetting::getInstance()->checkSound)
		{
			GameSetting::getInstance()->playSoundEffect("sounds/sound_changegun.mp3");
		}
		if (a->getCollisionBitmask() == 666)
		{
			//bomItems.at(a->getGroup())->setAlive(false);
			bomItems.at(a->getGroup())->getSprite()->getPhysicsBody()->setEnabled(false);
			bomItems.at(a->getGroup())->setPosition(bomItems.at(a->getGroup())->getPosition() + Vec2(0, -10));
			log("a->getGroup()  %d", a->getGroup());
		}
		else if (b->getCollisionBitmask() == 666)
		{
			//bomItems.at(b->getGroup())->setAlive(false);
			bomItems.at(b->getGroup())->getSprite()->getPhysicsBody()->setEnabled(false);
			bomItems.at(b->getGroup())->setPosition(bomItems.at(b->getGroup())->getPosition() + Vec2(0, -10));
			log("b->getGroup()  %d", b->getGroup());
		}
	}

	// bomActivator vs mc
	if ((a->getCollisionBitmask() == 667 && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == 667))
	{
		for (BomItem *b : bomItems)
		{
			if (b->getSprite()->getPhysicsBody()->isEnabled())
			{
				break;
			}
			if (!isBoomSoundOn2)
			{
				isBoomActivated = true;
				isBoomSoundOn = true;
				isBoomSoundOn2 = true;
				isSoundPlay = false;
			}
		}
	}

	// bomActivator vs boss
	if ((a->getCollisionBitmask() == 667 && b->getCollisionBitmask() == Model::BITMASK_MONSTER)
		|| (a->getCollisionBitmask() == Model::BITMASK_MONSTER && b->getCollisionBitmask() == 667))
	{
		if (GameSetting::getInstance()->checkSound && !isSoundPlay)
		{
			GameSetting::getInstance()->stopAllEffects();
			GameSetting::getInstance()->playBackgroundMusic("sounds/ingameLV3.mp3");
			isBoomSoundOn2 = false;
		}
		
		isBoomActivated = false;

	}
	return true;
}

void InGameScene::createMap()
{
	//backgroundfar	
	mTileMapFarBackground = TMXTiledMap::create(std::string("maps/level") + std::to_string(InGameScene::mapIndex) + std::string("_bg.tmx"));
	auto paraNode = ParallaxNode::create();
	paraNode->addChild(mTileMapFarBackground, 0, Vec2(0.14f, 0.0f), Vec2::ZERO);
	this->addChild(paraNode);

	//tile map
	mTileMap = TMXTiledMap::create(std::string("maps/level") + std::to_string(InGameScene::mapIndex) + std::string(".tmx"));
	mPhysicsLayer = mTileMap->getLayer("physics");
	mWallPhysicsLayer = mTileMap->getLayer("physics_wall");
	mObjectGroup = mTileMap->getObjectGroup("objectPos");
	mWallPhysicsLayer->setVisible(false);
	mPhysicsLayer->setVisible(false);
	this->addChild(mTileMap);
}

void InGameScene::createPhysics()
{
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

	//wall
	layerSize = mWallPhysicsLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mWallPhysicsLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physics->setCollisionBitmask(Model::BITMASK_WALL);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setMass(2000);
				tileSet->setPhysicsBody(physics);
			}
		}
	}
}

void InGameScene::createObjects() {
	auto objects = mObjectGroup->getObjects();

	bomItems.clear();
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
			if (mapIndex == 1)
			{
				mPlayer = new Player1(this);
			}
			else
			{
				mPlayer = new Player2(this);
			}
			mPlayer->setPosition(Vec2(posX, posY));
		}
		else if (type == Model::MODLE_TYPE_MONSTER3)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			MonsterBoss3 *monsterBoss3 = new MonsterBoss3(this, pMinPos, pMaxPos);
			monsterBoss3->setPosition(Vec2(posX, posY));
			monsterBoss3->setGroupBullet(monster_count);
			monsterBoss3->setIndex(monster_count++);
			mMonsters.push_back(monsterBoss3);
		}
		else if (type == Model::MODLE_TYPE_MONSTER4)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			MonsterCrep *monsterCrep = new MonsterCrep(this, pMinPos, pMaxPos);
			monsterCrep->setPosition(Vec2(posX, posY));
			monsterCrep->setGroupBullet(monster_count);
			monsterCrep->setIndex(monster_count++);
			mMonsters.push_back(monsterCrep);
		}
		else if (type == Model::MODLE_TYPE_MONSTER5)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			MonsterBoss1 *monsterBoss1 = new MonsterBoss1(this, pMinPos, pMaxPos);
			monsterBoss1->setPosition(Vec2(posX, posY));
			monsterBoss1->setGroupBullet(monster_count);
			monsterBoss1->setIndex(monster_count++);
			mMonsters.push_back(monsterBoss1);
		}
		else if (type == Model::MODLE_TYPE_MONSTER6)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			MonsterSky *monsterSky = new MonsterSky(this, pMinPos, pMaxPos);
			monsterSky->setPosition(Vec2(posX, posY));
			monsterSky->setGroupBullet(monster_count);
			monsterSky->setIndex(monster_count++);
			mMonsters.push_back(monsterSky);
		}
		else if (type == Model::MODLE_TYPE_MONSTER7)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			MonsterBoss2 *monsterBoss2 = new MonsterBoss2(this, pMinPos, pMaxPos);
			monsterBoss2->setPosition(Vec2(posX, posY));
			monsterBoss2->setGroupBullet(monster_count);
			monsterBoss2->setIndex(monster_count++);
			mMonsters.push_back(monsterBoss2);
		}
		else if (type == 25)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			int groundType = object.asValueMap().at("typeGround").asInt();
			auto flyGround = new FlyGround(this, groundType, pMinPos, pMaxPos);
			flyGround->setPosition(Vec2(posX, posY));
			flyGrounds.push_back(flyGround);
		}
		else if (type == 100)
		{
			auto particleFinal = ParticleSystemQuad::create("particle/final_map.plist");
			particleFinal->setPosition(Vec2(posX, posY));
			addChild(particleFinal);
			particle.push_back(particleFinal);
		}
		else if (type == 666)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			int BomType = object.asValueMap().at("bomItem").asInt();
			BomItem *bomItem = new BomItem(this, BomType, pMinPos, pMaxPos);
			bomItem->setPosition(Vec2(posX, posY));
			bomItem->setIndex(boomC++);
			bomItem->setAlive(false);
			bomItems.push_back(bomItem);
			
		}
		else if (type == 667)
		{
			int pMinPos = object.asValueMap().at("_minPos").asInt();
			int pMaxPos = object.asValueMap().at("_maxPos").asInt();
			int BomActivatorType = object.asValueMap().at("bomActivator").asInt();
			bomActivator = new BomActivator(this, BomActivatorType, pMinPos, pMaxPos);
			bomActivator->setPosition(Vec2(posX, posY));
		}
	}
}

void InGameScene::createController()
{
	//move Left
	mMoveLeftController = Sprite::create("moveleft_normal.png");
	mMoveLeftController->setOpacity(80);
	mMoveLeftController->setAnchorPoint(Vec2(0, 0));
	mMoveLeftController->setScale(0.8f);
	mMoveLeftController->setPosition(Vec2(8, 8));
	controllerLayer->addChild(mMoveLeftController);
	mMoveLeftControllerPressed = Sprite::create("moveleft_press.png");
	mMoveLeftControllerPressed->setOpacity(80);
	mMoveLeftControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveLeftControllerPressed->setScale(0.8f);
	mMoveLeftControllerPressed->setPosition(mMoveLeftController->getPosition());
	mMoveLeftControllerPressed->setVisible(false);
	controllerLayer->addChild(mMoveLeftControllerPressed);

	//move Right
	mMoveRightController = Sprite::create("moveleft_normal.png");
	mMoveRightController->setOpacity(80);
	mMoveRightController->setFlippedX(true);
	mMoveRightController->setScale(0.8f);
	mMoveRightController->setAnchorPoint(Vec2(0, 0));
	mMoveRightController->setPosition(mMoveLeftController->getPosition() + Vec2(mMoveLeftController->getContentSize().width, 0));
	controllerLayer->addChild(mMoveRightController);
	mMoveRightControllerPressed = Sprite::create("moveleft_press.png");
	mMoveRightControllerPressed->setOpacity(80);
	mMoveRightControllerPressed->setAnchorPoint(Vec2(0, 0));
	mMoveRightControllerPressed->setScale(0.8f);
	mMoveRightControllerPressed->setFlippedX(true);
	mMoveRightControllerPressed->setPosition(mMoveRightController->getPosition());
	mMoveRightControllerPressed->setVisible(false);
	controllerLayer->addChild(mMoveRightControllerPressed);

	if (mapIndex == 1)
	{
		//parkour control
		mParkourController = ui::Button::create("parkour_normal.png", "parkour_press.png");
		mParkourController->setOpacity(80);
		mParkourController->setScale(0.5f);
		mParkourController->setPosition(Vec2(visibleSize.width - 130, visibleSize.height - 360));
		mParkourController->addTouchEventListener(CC_CALLBACK_2(InGameScene::parkour, this));
		controllerLayer->addChild(mParkourController);
	}
	else
	{
		//knife control
		mKnifeController = ui::Button::create("knife_normal.png", "knife_press.png");
		mKnifeController->setOpacity(80);
		mKnifeController->setScale(0.7f);
		mKnifeController->setPosition(Vec2(visibleSize.width - 130, visibleSize.height - 360));
		mKnifeController->addTouchEventListener(CC_CALLBACK_2(InGameScene::knife, this));
		controllerLayer->addChild(mKnifeController);
	}


	if (mapIndex == 1)
	{
	//avoid control
		mAvoidController = ui::Button::create("down_no.png", "down_no_press.png");
		mAvoidController->setOpacity(80);
		mAvoidController->setScale(0.3f);
		mAvoidController->setPosition(Vec2(visibleSize.width / 2  + 245, visibleSize.height / 2 - 200));
		mAvoidController->addTouchEventListener(CC_CALLBACK_2(InGameScene::avoid, this));
		controllerLayer->addChild(mAvoidController);
	}

	if (mapIndex == 1)
	{
		//punch control
		mFireController = ui::Button::create("shoot_normal.png", "shoot_press.png");
	}
	else
	{
		//fire controller
		mFireController = ui::Button::create("shoot_normal.png", "shoot_press.png");
	}
	mFireController->setOpacity(80);
	mFireController->setScale(0.7f);
	mFireController->setPosition(Vec2(visibleSize.width / 2 + 245, visibleSize.height / 2 - 195));
	mFireController->addTouchEventListener(CC_CALLBACK_2(InGameScene::fire, this));
	controllerLayer->addChild(mFireController);

	if (mapIndex != 1)
	{
		//change gun control
		mChangeGunController = ui::Button::create("changegun_normal.png", "changegun_press.png");
		mChangeGunController->setOpacity(80);
		mChangeGunController->setPosition(Vec2(visibleSize.width /2 + 355,visibleSize.height/2 - 90));
		mChangeGunController->addTouchEventListener(CC_CALLBACK_2(InGameScene::changeGun, this));
		controllerLayer->addChild(mChangeGunController);
	}

	//jump control
	mJumpController = ui::Button::create("jump_normal.png", "jump_press.png");
	mJumpController->setOpacity(80);
	mJumpController->setScale(0.9f);
	mJumpController->setPosition(Vec2(visibleSize.width/2 + 340, visibleSize.height/2 - 180));
	mJumpController->addTouchEventListener(CC_CALLBACK_2(InGameScene::jump, this));
	controllerLayer->addChild(mJumpController);

	//btn pause
	auto btnPause = ui::Button::create("pause_normal.png", "pause_press.png");
	btnPause->setScale(0.6f);
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(visibleSize - Size(10, 10));
	btnPause->addTouchEventListener(CC_CALLBACK_2(InGameScene::pause, this));
	controllerLayer->addChild(btnPause);


	ui::Button* btnItemPick;
	if (mapIndex == 1)
	{
		//Item pick
		btnItemPick = ui::Button::create("faceMClv1.png");
		btnItemPick->setScaleY(0.7f);
		btnItemPick->setScaleX(0.9f);
		btnItemPick->setPosition(Vec2(45, SCREEN_H - 30));		
	}
	else
	{
		btnItemPick = ui::Button::create("faceManCharacter.png");
		btnItemPick->setScale(0.17f);
		btnItemPick->setPosition(Vec2(55, SCREEN_H - 30));
	}
	btnItemPick->addTouchEventListener(CC_CALLBACK_2(InGameScene::viewItemGun, this));
	controllerLayer->addChild(btnItemPick);
}

void InGameScene::createHud()
{
	auto hud = Sprite::create("HeartMana.png");
	hud->setAnchorPoint(Vec2(0, 0.5f));
	hud->setScale(0.7f);
	hud->setPosition(Vec2(0, SCREEN_H - 35));
	controllerLayer->addChild(hud);

	mMcHudBlood = ui::LoadingBar::create("hud_blood.png");
	mMcHudBlood->setAnchorPoint(Vec2(0, 0.5));
	mMcHudBlood->setScaleX(0.55f);
	mMcHudBlood->setScaleY(0.4f);
	mMcHudBlood->setPosition(Vec2(78,SCREEN_H-26));
	mMcHudBlood->setDirection(ui::LoadingBar::Direction::LEFT);
	mMcHudBlood->setPercent(100);
	controllerLayer->addChild(mMcHudBlood);

	mMcHudXP = ui::LoadingBar::create("xp.png");
	mMcHudXP->setAnchorPoint(Vec2(0., 0.5));
	mMcHudXP->setScaleX(0.40f);
	mMcHudXP->setScaleY(0.52f);
	mMcHudXP->setPosition(Vec2(90, SCREEN_H - 40));
	mMcHudXP->setDirection(ui::LoadingBar::Direction::LEFT);
	mMcHudXP->setPercent(100);
	controllerLayer->addChild(mMcHudXP);

	Sprite* faceMC;
	if (mapIndex == 1)
	{
		faceMC = Sprite::create("faceMClv1.png");
		faceMC->setScaleY(0.7f);
		faceMC->setScaleX(0.9f);
		faceMC->setPosition(Vec2(45, SCREEN_H - 30));
		controllerLayer->addChild(faceMC);
	}
	else
	{
		faceMC = Sprite::create("faceManCharacter.png");
		faceMC->setScale(0.17f);
		faceMC->setPosition(Vec2(55, SCREEN_H - 30));
		controllerLayer->addChild(faceMC);
	}
}

void InGameScene::createItemPickedLayer()
{
	//create itempicked layer
	mItemPickedLayer = Sprite::create("bgitempick.png");
	mItemPickedLayer = Sprite::create("layerItem.png");
	mItemPickedLayer->setPosition(visibleSize / 2);
	mItemPickedLayer->setVisible(false);
	viewLayer->addChild(mItemPickedLayer);
	

	auto curHP = Label::createWithTTF(" 100" , "fonts/Marker Felt.ttf", 30);
	curHP->setColor(Color3B::ORANGE);
	curHP->enableShadow(Color4B::BLACK);
	curHP->enableOutline(Color4B::BLACK, 10);
	curHP->enableGlow(Color4B::BLACK);
	curHP->setPosition(Vec2(visibleSize.width / 2 - 20 , visibleSize.height / 2 + 30));
	mItemPickedLayer->addChild(curHP);

	auto curXP = Label::createWithTTF("5", "fonts/Marker Felt.ttf", 30);
	curXP->setColor(Color3B::ORANGE);
	curXP->enableShadow(Color4B::BLACK);
	curXP->enableOutline(Color4B::BLACK, 10);
	curXP->enableGlow(Color4B::BLACK);
	curXP->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 30));
	mItemPickedLayer->addChild(curXP);

	auto gun1 = Sprite::create("item/gun1.png");
	gun1->setScale(0.5f);
	gun1->setPosition(visibleSize.width / 2 - 250, visibleSize.height / 2 - 80);
	mItemPickedLayer->addChild(gun1);

	auto gun2 = Sprite::create("item/gun2.png");
	gun2->setScale(0.5f);
	gun2->setPosition(visibleSize.width / 2 - 245, visibleSize.height / 2 - 160);
	mItemPickedLayer->addChild(gun2);

	auto gun3 = Sprite::create("item/gun3.png");
	gun3->setScale(0.6f);
	gun3->setPosition(visibleSize.width / 2 - 90, visibleSize.height / 2 - 80);
	mItemPickedLayer->addChild(gun3);

	auto gun4 = Sprite::create("item/gun4.png");
	gun4->setScale(0.6f);
	gun4->setPosition(visibleSize.width / 2 - 85, visibleSize.height / 2 - 160);
	mItemPickedLayer->addChild(gun4);

	auto gun5 = Sprite::create("item/gun5.png");
	gun5->setScale(0.5f);
	gun5->setPosition(visibleSize.width / 2 + 80, visibleSize.height / 2 - 80);
	mItemPickedLayer->addChild(gun5);

	auto gun6 = Sprite::create("item/gun6.png");
	gun6->setScale(0.5f);
	gun6->setPosition(visibleSize.width / 2 + 85, visibleSize.height / 2 - 160);
	mItemPickedLayer->addChild(gun6);

	auto slgun1 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun1->setColor(Color3B::ORANGE);
	slgun1->enableShadow(Color4B::BLACK);
	slgun1->enableOutline(Color4B::BLACK, 10);
	slgun1->enableGlow(Color4B::BLACK);
	slgun1->setPosition(Vec2(visibleSize.width / 2 - 190, visibleSize.height / 2 - 80));
	mItemPickedLayer->addChild(slgun1);
	
	auto slgun2 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun2->setColor(Color3B::ORANGE);
	slgun2->enableShadow(Color4B::BLACK);
	slgun2->enableOutline(Color4B::BLACK, 10);
	slgun2->enableGlow(Color4B::BLACK);
	slgun2->setPosition(Vec2(visibleSize.width / 2 - 190, visibleSize.height / 2 - 160));
	mItemPickedLayer->addChild(slgun2);

	auto slgun3 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun3->setColor(Color3B::ORANGE);
	slgun3->enableShadow(Color4B::BLACK);
	slgun3->enableOutline(Color4B::BLACK, 10);
	slgun3->enableGlow(Color4B::BLACK);
	slgun3->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height / 2 - 80));
	mItemPickedLayer->addChild(slgun3);

	auto slgun4 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun4->setColor(Color3B::ORANGE);
	slgun4->enableShadow(Color4B::BLACK);
	slgun4->enableOutline(Color4B::BLACK, 10);
	slgun4->enableGlow(Color4B::BLACK);
	slgun4->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height / 2 - 160));
	mItemPickedLayer->addChild(slgun4);

	auto slgun5 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun5->setColor(Color3B::ORANGE);
	slgun5->enableShadow(Color4B::BLACK);
	slgun5->enableOutline(Color4B::BLACK, 10);
	slgun5->enableGlow(Color4B::BLACK);
	slgun5->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 - 80));
	mItemPickedLayer->addChild(slgun5);

	auto slgun6 = Label::createWithTTF(" 0", "fonts/Marker Felt.ttf", 30);
	slgun6->setColor(Color3B::ORANGE);
	slgun6->enableShadow(Color4B::BLACK);
	slgun6->enableOutline(Color4B::BLACK, 10);
	slgun6->enableGlow(Color4B::BLACK);
	slgun6->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 - 160));
	mItemPickedLayer->addChild(slgun6);

	labelNumber.clear();
	labelNumber.push_back(slgun1);
	labelNumber.push_back(slgun2);
	labelNumber.push_back(slgun3);
	labelNumber.push_back(slgun4);
	labelNumber.push_back(slgun5);
	labelNumber.push_back(slgun6);
	labelNumber.push_back(curHP);
	labelNumber.push_back(curXP);

	auto btnCancle = ui::Button::create("cancel_normal.png", "cancel_press.png");
	btnCancle->setScale(0.7f);
	btnCancle->setPosition(Vec2(visibleSize.width / 2 + 180, visibleSize.height / 2 + 100));
	btnCancle->addClickEventListener([&](Ref* event) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		mItemPickedLayer->setVisible(false);
	});
	mItemPickedLayer->addChild(btnCancle);

}

void InGameScene::createPauseLayer()
{
	//create pause layer
	mPauseLayer = Sprite::create("bg_menu111.png");
	mPauseLayer->setPosition(visibleSize/2);
	mPauseLayer->setVisible(false);
	viewLayer->addChild(mPauseLayer);


	//check box music
	auto btnMusic = ui::CheckBox::create("music_normal.png", "music_press.png");
	btnMusic->setPosition(Vec2(100,50));
	btnMusic->setScale(0.5f);
	btnMusic->addEventListener([&](Ref* sender, ui::CheckBox::EventType type){
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
	if (GameSetting::getInstance()->getSound())
	{
		btnMusic->setSelected(false);
	}
	else
	{
		btnMusic->setSelected(true);
	}
	mPauseLayer->addChild(btnMusic);


	//checkbox Sound
	auto checkboxSound = ui::CheckBox::create("sound_normal.png", "sound_press.png");
	checkboxSound->setPosition(Vec2(170,50));
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
	mPauseLayer->addChild(checkboxSound);


	//button menu, continue
	auto btnContinue = ui::Button::create("continuee_normal.png", "continuee_press.png");
	btnContinue->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 ));
	btnContinue->addClickEventListener([&](Ref* event) {
		//SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		mPauseLayer->setVisible(false);
		controllerLayer->setVisible(true);
		isPause = false;
	});
	mPauseLayer->addChild(btnContinue);

	auto btnmenu = ui::Button::create("menuu_normal.png", "menuu_press.png");
	btnmenu->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100));
	btnmenu->addClickEventListener([](Ref* event) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, MainMenuScene::createScene()));
	});
	mPauseLayer->addChild(btnmenu);
}

void InGameScene::updateController()
{
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
		mCurrentTouchPoint = Point(747, 154);
	}

	switch (mCurrentTouchState)
	{
	case ui::Widget::TouchEventType::BEGAN:
	case ui::Widget::TouchEventType::MOVED:
		if (Rect(mMoveLeftController->getPosition().x, mMoveLeftController->getPosition().y, mMoveLeftController->getContentSize().width, mMoveLeftController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_LEFT_ARROW  
			&& mPlayer->getPosition().x - mPlayer->getContentSize().width /2 > 0) //move left
		{
			enablePressedControl(true, true);
			moveLeft();
		}
		else
		{
			enablePressedControl(true, false);
		}

		if ((Rect(mMoveRightController->getPosition().x, mMoveRightController->getPosition().y, mMoveRightController->getContentSize().width, mMoveRightController->getContentSize().height).containsPoint(mCurrentTouchPoint)
			|| mCurrentKey == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) 
			&& mPlayer->getPosition().x + mPlayer->getContentSize().width/2 <= mTileMap->getMapSize().width * mTileMap->getTileSize().width) //move right		
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
		if (mPlayer->getSprite()->getNumberOfRunningActions() == 0)
		{
			mPlayer->setState(PlayerModel::STATE_IDLE);
		}
		break;
	}
}

void InGameScene::moveLeft()
{
	if (mPlayer->getCurrentState() != PlayerModel::STATE_DAMAGE && mPlayer->getPosition().x - mPlayer->getContentSize().width / 2 > 0)
	{
		mPlayer->moveLeft(onAir);
	}
}

void InGameScene::moveRight()
{
	if (mPlayer->getCurrentState() != PlayerModel::STATE_DAMAGE && mPlayer->getPosition().x <= mTileMap->getMapSize().width * mTileMap->getTileSize().width)
	{
		mPlayer->moveRight(onAir);
	}
}

void InGameScene::fire(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		if (GameSetting::getInstance()->checkSound)
		{
			if (mapIndex != 1)
			{
				if (Inventory::getInstance()->getCurrentGun() == 2)
				{
					SimpleAudioEngine::getInstance()->playEffect("sounds/sound_gunFNSCAR.mp3");
				}
				else if(Inventory::getInstance()->getCurrentGun() == 3)
				{
					SimpleAudioEngine::getInstance()->playEffect("sounds/sound_waltherp99.mp3");
				}
				else
				{
					SimpleAudioEngine::getInstance()->playEffect("sounds/vacham_physic.mp3");
				}
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/knifeLV1.mp3");
			}
		}
		mPlayer->fire();
		if (mapIndex != 1)
		{ 
			numBullets->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(Inventory::getInstance()->getCurrentGun())));
		}
		break;
	}
}

void InGameScene::changeGun(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		dynamic_cast<Player2*>(mPlayer)->changeGun(false);
		switch (Inventory::getInstance()->getCurrentGun())
		{
		case 1:
			logGun->setTexture("item/rpk74.png");
			break;
		case 2:
			logGun->setTexture("item/fnscar.png");
			break;
		case 3:
			logGun->setTexture("item/waltherp99.png");
			break;
		}
		break;
	}
	numBullets->setString(StringUtils::format("%d", Inventory::getInstance()->getNumBulletGun(Inventory::getInstance()->getCurrentGun())));
}

void InGameScene::parkour(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		if (GameSetting::getInstance()->checkSound)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/mc_jump2.wav");
		}
		dynamic_cast<Player1*>(mPlayer)->parkout();
		break;
	}
}

void InGameScene::knife(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		if (GameSetting::getInstance()->checkSound)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/soundKnife.mp3");
		}
		dynamic_cast<Player2*>(mPlayer)->knife();
		break;
	}
}

void InGameScene::avoid(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case::ui::Widget::TouchEventType::BEGAN:
		if (GameSetting::getInstance()->checkSound)
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/mc_jump2.wav");
		}
		dynamic_cast<Player1*>(mPlayer)->avoid();
		break;
	}
}

void InGameScene::jump(Ref* sender, ui::Widget::TouchEventType type)
{
	if (jumpC >= 1 && onAir)
		return;
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		if (GameSetting::getInstance()->checkSound)
		{
			SimpleAudioEngine::getInstance()->playEffect("sounds/mc_jump2.wav");
		}
		onAir = true;

		mPlayer->jump();
		jumpC++;
		break;
	}
}

void InGameScene::pause(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		});
		isPause = true;
		mPauseLayer->setOpacity(0);
		mPauseLayer->setVisible(true);
		controllerLayer->setVisible(false);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void InGameScene::viewItemGun(Ref* sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		});
		
		controllerLayer->setVisible(false);
		mItemPickedLayer->setOpacity(0);
		mItemPickedLayer->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mItemPickedLayer->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		labelNumber.at(0)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(1)));
		labelNumber.at(1)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(2)));
		labelNumber.at(2)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(3)));
		labelNumber.at(3)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(4)));
		labelNumber.at(4)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(5)));
		labelNumber.at(5)->setString(StringUtils::format("%d", Inventory::getInstance()->getPart(6)));
		labelNumber.at(6)->setString(StringUtils::format("%d", mPlayer->getBlood()));
		labelNumber.at(7)->setString(StringUtils::format("%d", mPlayer->getLive()));
		break;
	}
}
void InGameScene::enablePressedControl(bool isLeft, bool pressed)
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

void InGameScene::updateMonsters()
{
	for (int i = 0; i < mMonsters.size(); i++)
	{
		if (mMonsters.at(i)->isAlive())
		{
			mMonsters.at(i)->update(mPlayer->getPosition());
		}
	}
}

void InGameScene::setCenterView()
{
	float playfield_width = mTileMap->getMapSize().width * mTileMap->getTileSize().width;
	float playfield_height = mTileMap->getMapSize().height * mTileMap->getTileSize().height;
	
	this->runAction(Follow::create(mPlayer->getSprite(), Rect(0, 0, playfield_width, playfield_height)));
}

void InGameScene::setCenterView(Point position) 
{
	Size winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (mTileMap->getMapSize().width * this->mTileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (mTileMap->getMapSize().height * mTileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);

	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	if (position.y > 1600)
	{
		viewPoint.y = -1600;
	}

	if (mapIndex == 1)
	{
		if (viewPoint.x < -2386)
		{
			viewPoint.x = -2386.33f;
		}
	}
	else if (mapIndex == 4)
	{
		if (viewPoint.x < -1267)
		{
			viewPoint.x = -1268;
		}
	}
	else
	{
		if (viewPoint.x < -3201)
		{
			viewPoint.x = -3201.33f;
		}
	}
	this->setPosition(viewPoint);
}

bool InGameScene::onContactPreSolve(cocos2d::PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	if ((a->getCollisionBitmask() == Model::BITMASK_WALL && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WALL)) {
		if (a->getCollisionBitmask() == Model::BITMASK_WALL) {
			if (a->getPosition().y > mPlayer->getSprite()->getPosition().y) {
				mPlayer->setCanRun(false);
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_WALL) {
			if (b->getPosition().y > mPlayer->getSprite()->getPosition().y) {
				mPlayer->setCanRun(false);
			}
		}
	}
	return true;
}

void InGameScene::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	if ((a->getCollisionBitmask() == Model::BITMASK_WALL && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WALL)) {
		if (a->getCollisionBitmask() == Model::BITMASK_WALL) {
			if (a->getPosition().y > mPlayer->getSprite()->getPosition().y) {
				mPlayer->setCanRun(false);
			}
		}
		else if (b->getCollisionBitmask() == Model::BITMASK_WALL) {
			if (b->getPosition().y > mPlayer->getSprite()->getPosition().y) {
				mPlayer->setCanRun(false);
			}
		}
	}
}

void InGameScene::onContactSeparate(cocos2d::PhysicsContact& contact) {
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();
	mPlayer->setCanRun(true);
}