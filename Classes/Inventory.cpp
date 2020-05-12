#include "Inventory.h"

Inventory* Inventory::cInstance = nullptr;
int Inventory::numOfPart1 = 0;
int Inventory::numOfPart2 = 0;
int Inventory::numOfPart3 = 0;
int Inventory::numOfPart4 = 0;
int Inventory::numOfPart5 = 0;
int Inventory::numOfPart6 = 0;
int Inventory::numOfPartBullet = 0;

int Inventory::bulletsGun1 = 200;
int Inventory::bulletsGun2 = 400;
int Inventory::bulletsGun3 = 50;

Inventory::Inventory()
{
}

Inventory* Inventory::getInstance()
{
	if (Inventory::cInstance == nullptr)
	{
		Inventory::cInstance = new Inventory();
	}
	return Inventory::cInstance;
}

void Inventory::addPart(int type)
{
	switch (type)
	{
	case 201:
		numOfPart1++;
		break;
	case 202:
		numOfPart2++;
		break;
	case 203:
		numOfPart3++;
		break;
	case 204:
		numOfPart4++;
		break;
	case 205:
		numOfPart5++;
		break;
	case 206:
		numOfPart6++;
		break;
	case 207:
		setNumBulletGun(getCurrentGun(), 5);
		break;
	case 210:
		numOfPart1 += 2;
		numOfPart2 += 2;
		numOfPart3 += 2;
		numOfPart4 += 2;
		numOfPart5 += 2;
		numOfPart6 += 2;
		break;
	}
}

void Inventory::dePart(int type)
{
	switch (type)
	{
	case 301:
		numOfPart1--;
		break;
	case 302:
		numOfPart2--;
		break;
	case 303:
		numOfPart3--;
		break;
	case 304:
		numOfPart4--;
		break;
	case 305:
		numOfPart5--;
		break;
	case 306:
		numOfPart6--;
		break;
	case 307:
		numOfPartBullet--;
		break;
	}
}

int Inventory::getPart(int type)
{
	switch (type)
	{
	case 1:
		return numOfPart1;
		break;
	case 2:
		return numOfPart2;
		break;
	case 3:
		return numOfPart3;
		break;
	case 4:
		return numOfPart4;
		break;
	case 5:
		return numOfPart5;
		break;
	case 6:
		return numOfPart6;
		break;
	case 7:
		return numOfPartBullet;
		break;
	}
}

void Inventory::setGun(int type)
{
	switch (type)
	{
	case 1:
		if (hasGun1)
		{
			setNumBulletGun(1, 7);
		}
		else
		{
			hasGun1 = true;
			setNumBulletGun(1, 3);
		}
		break;
	case 2:
		if (hasGun2)
		{
			setNumBulletGun(2, 20);
		}
		else
		{
			hasGun2 = true;
			setNumBulletGun(2, 10);
		}
		break;
	case 3:
		if (hasGun3)
		{
			setNumBulletGun(3, 3);
		}
		else
		{
			hasGun3 = true;
			setNumBulletGun(3, 1);
		}
		break;
	}
}

void Inventory::throwGun(int type)
{
	switch (type)
	{
	case 1:
		hasGun1 = false;
		break;
	case 2:
		hasGun2 = false;
		break;
	case 3:
		hasGun3 = false;
		break;
	}
}

bool Inventory::getGun(int type)
{
	switch (type)
	{
	case 1:
		return hasGun1;
	case 2:
		return hasGun2;
	case 3:
		return hasGun3;
	}
}

void Inventory::setCurrentGun(int type)
{
	mCurrentGun = type;
}

int Inventory::getCurrentGun()
{
	return mCurrentGun;
}

void Inventory::setNumBulletGun(int type, int quantity)
{
	switch (type)
	{
	case 1:
		bulletsGun1 += quantity;
		break;
	case 2:
		bulletsGun2 += quantity;
		break;
	case 3:
		bulletsGun3 += quantity;
		break;
	}
}

int Inventory::getNumBulletGun(int type)
{
	switch (type)
	{
	case 1:
		return bulletsGun1;
		break;
	case 2:
		return bulletsGun2;
		break;
	case 3:
		return bulletsGun3;
		break;
	}
}

void Inventory::useBulletGun(int type)
{
	switch (type)
	{
	case 1:
		bulletsGun1--;
		break;
	case 2:
		bulletsGun2--;
		break;
	case 3:
		bulletsGun3--;
		break;
	}
}

void Inventory::loadFromSaved()
{

}