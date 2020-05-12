#ifndef _INGAME_SCENE_H_
#define _INGAME_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player1.h"
#include "Player2.h"
#include "MonsterBoss3.h"
#include "MonsterCrep.h"
#include "MonsterBoss1.h"
#include "MonsterSky.h"
#include "MonsterBoss2.h"
#include "Gun1Item.h"
#include "Gun2Item.h"
#include "Gun3Item.h"
#include "Gun4Item.h"
#include "Gun5Item.h"
#include "Gun6Item.h"
#include "BulletItem.h"
#include "Inventory.h"
#include "FlyGround.h"
#include "SimpleAudioEngine.h"
#include "BomItem.h"
#include "BomActivator.h"

#include <string>
#include <sstream>
using namespace std;
namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

class InGameScene : public cocos2d::Layer
{
private:
	bool isPause = false;
	cocos2d::PhysicsWorld* mphysicsWorld;
	int jumpC = 4;
	bool onAir = true;
	bool touchGround;
	int gameTimer = 0;
	bool isBoomActivated = false;
	bool isBoomSoundOn = false;
	bool isBoomSoundOn2 = false;
	bool isSoundPlay = true;
	int numOfBoom = 0;
	int boomC = 0;

	cocos2d::Label * numBullets;

	cocos2d::Vec2 curPos;

	cocos2d::Layer* viewLayer;
	cocos2d::Layer* controllerLayer;

	//use cheat for key
	cocos2d::EventKeyboard::KeyCode mCurrentKey;

	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;

	cocos2d::Point mCurrentTouchPoint;

	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;

	cocos2d::ui::Button* mPunchController;
	cocos2d::ui::Button* mFireController;
	cocos2d::ui::Button* mChangeGunController;
	cocos2d::ui::Button* mKnifeController;
	cocos2d::ui::Button* mJumpController;
	cocos2d::ui::Button* mParkourController;
	cocos2d::ui::Button* mAvoidController;

	cocos2d::TMXTiledMap* mTileMap;
	cocos2d::TMXTiledMap* mTileMapFarBackground;
	cocos2d::TMXLayer* mPhysicsLayer;
	cocos2d::TMXLayer* mWallPhysicsLayer;
	cocos2d::TMXObjectGroup* mObjectGroup;

	//progress's blood
	cocos2d::ui::LoadingBar *mMcHudBlood;
	cocos2d::ui::LoadingBar *mMonsterHudBlood;

	cocos2d::ui::LoadingBar *mMcHudXP;

	cocos2d::ui::LoadingBar *mMcHudMonster1;

	PlayerModel *mPlayer;
	std::vector<Monster*> mMonsters;
	std::vector<ItemModel*> items;
	std::vector<FlyGround*>  flyGrounds;
	std::vector<BomItem*>  bomItems;
	BomActivator *bomActivator;

	std::vector<ParticleSystemQuad*> particle;
	bool isCompletedStage;
	ItemModel* item;

public:
	static int mapIndex;

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	void onContactSeparate(cocos2d::PhysicsContact& contact);
	
	CREATE_FUNC(InGameScene);

private:
	void createMap();

	void createPhysics();

	void createObjects();

	void createController();

	void createHud();

	void createItemPickedLayer();

	void createPauseLayer();

	void updateController();

	void addListener();

	void setCenterView();

	void setCenterView(cocos2d::Vec2 player);

	void moveLeft();

	void moveRight();

	void fire(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void changeGun(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void avoid(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void parkour(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
	void knife(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void jump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void viewItemGun(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void enablePressedControl(bool isLeft, bool pressed);

	void updateMonsters();
};

#endif