#ifndef _BULLET_H_
#define _BULLET_H_
#include "Model.h"
class Bullet : public Model
{
private:
	const int RUN_STEP = 10;
	cocos2d::Sprite* mSpriteOwner;
public:
	Bullet(cocos2d::Layer* layer, cocos2d::Sprite *sprite, int owner, cocos2d::Sprite* spriteOwner);
	Bullet();
	~Bullet();

	void explode(bool isRight);

	void update(int runStep);
};
#endif