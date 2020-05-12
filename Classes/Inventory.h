#pragma once

#include "Define.h"
#include "BulletItem.h"
#include "Gun1Item.h"
#include "Gun2Item.h"
#include "Gun3Item.h"
#include "Gun4Item.h"
#include "Gun5Item.h"
#include "Gun6Item.h"

class Inventory
{
private:
	Inventory();
	static Inventory* cInstance;
	static int numOfPart1;
	static int numOfPart2;
	static int numOfPart3;
	static int numOfPart4;
	static int numOfPart5;
	static int numOfPart6;
	static int numOfPartBullet;
	
	bool hasGun1 = true;
	bool hasGun2 = true;
	bool hasGun3 = true;

	static int bulletsGun1;
	static int bulletsGun2;
	static int bulletsGun3;

	int mCurrentGun = 1;
public:
	static Inventory* getInstance();
	void addPart(int type);
	void dePart(int type);

	int getPart(int type);

	void setGun(int type);

	void throwGun(int type);

	bool getGun(int type);

	void setCurrentGun(int type);

	int getCurrentGun();

	void setNumBulletGun(int type, int quantity);

	int getNumBulletGun(int type);

	void useBulletGun(int type);

	void loadFromSaved();
};