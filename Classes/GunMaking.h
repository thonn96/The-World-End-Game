#ifndef _GUNMAKING_H_
#define _GUNMAKING_H_
#include "cocos2d.h"
#include "Define.h"
#include "ui\CocosGUI.h"
#include "Inventory.h"
#include <vector>

class GunMaking :public cocos2d::Layer
{
private:
	bool slot1 = false;
	bool slot2 = false;
	int temp;
	cocos2d::Sprite* sprite1;
	cocos2d::Sprite* sprite2;
	cocos2d::Sprite* viewGun1;
	std::vector<ui::Button*> btnGuns;
	ui::Button* btnCreateGun;
	ui::Button* btnSlot1;
	ui::Button* btnSlot2;
	std::vector<Label*> labels;

public:
	GunMaking();
	~GunMaking();

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float d);

	void createLabel();
	void createButton();
	void addClickListener();

	CREATE_FUNC(GunMaking);
};
#endif