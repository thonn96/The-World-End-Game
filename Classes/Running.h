#ifndef _RUNNING_H_
#define _RUNNING_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player2.h"
#include "Monster.h"

class Running : public cocos2d::Layer
{
private:
	bool onAir = true;
	//use cheat for key
	cocos2d::EventKeyboard::KeyCode mCurrentKey;

	cocos2d::ui::Widget::TouchEventType mCurrentTouchState;

	cocos2d::Point mCurrentTouchPoint;

	cocos2d::Sprite* mMoveLeftController;
	cocos2d::Sprite* mMoveLeftControllerPressed;
	cocos2d::Sprite* mMoveRightController;
	cocos2d::Sprite* mMoveRightControllerPressed;

	cocos2d::ui::Button* mFireController;
	cocos2d::ui::Button* mJumpController;

	cocos2d::TMXTiledMap* mTileMap;
	cocos2d::TMXTiledMap* mTileMapFarBackground;
	cocos2d::TMXLayer* mPhysicsLayer;
	cocos2d::TMXObjectGroup* mObjectGroup;

	//progress's blood
	cocos2d::ui::LoadingBar *mMcHudBlood;

	Player2 *mPlayer;
	std::vector<Monster*> mMonsters;

public:

	static char* mapName;

	static cocos2d::Scene* createScene(char* mapName);


	virtual bool init();

	virtual void update(float dt);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);

	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	bool onContactBegin(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(Running);

private:
	void createMap();

	void createPhysics();

	void createObjects();

	void createController();

	void createHud();

	void createPauseLayer();

	void updateController();

	void addListener();

	void setCenterView(bool isMoveRight);

	void moveLeft();

	void moveRight();

	void fire(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void jump(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void pause(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void enablePressedControl(bool isLeft, bool pressed);

	void updateMonsters();
};

#endif // _INGAME_SCENE_H_