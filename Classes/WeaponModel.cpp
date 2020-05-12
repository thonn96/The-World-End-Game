#include "WeaponModel.h"

WeaponModel::WeaponModel()
{
}

WeaponModel::~WeaponModel()
{
}

void WeaponModel::explode(bool isRight)
{
	mIsRunLeftToRight = isRight;
	if (isRight)
	{
		mSprite->setFlippedX(false);
	}
	else
	{
		mSprite->setFlippedX(true);
	}
}

void WeaponModel::update()
{
	if (isAlive())
	{
		if (mIsRunLeftToRight)
		{
			setPosition(getPosition() + Vec2(runStep, 0));
		}
		else
		{
			setPosition(getPosition() - Vec2(runStep, 0));
		}
		Rect rect;
		if (mSpriteOwner->getPosition().x <= 400)
		{
			rect = Rect(0, 0, 800, 10000);
		}
		else
		{
			rect = Rect(mSpriteOwner->getPosition().x - 400, 0, 800, 10000);
		}

		//out of screen
		if (!rect.containsPoint(getPosition()))
		{
			setAlive(false);
		}
		log("mc  %f", mSpriteOwner->getPosition().x);
	}
}