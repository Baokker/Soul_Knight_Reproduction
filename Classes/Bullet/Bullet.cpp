/*
* @file   Bullet.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Bullet.h"
#include"cocos2d.h"
#include"..\Const.h"

USING_NS_CC;

static void ProblemLoading(const char* filename)
{
	log("Error while loading:%s\n", filename);
}

bool Bullet::init()
{
	setPosition(0, 0);
	setVisible(false);

	auto Move = [this](float) {//float is necessary!!
		setPosition(getPositionX() + MoveSpeedX, getPositionY() + MoveSpeedY);
	};

	auto Disappear = [this](float) {
		auto visiblesize = Director::getInstance()->getVisibleSize();
		if (getPositionX() > visiblesize.width || getPositionY() > visiblesize.height)
		{
			setVisible(false);
			stopAllActions();
			MoveSpeedX = MoveSpeedY = 0;
			removeFromParentAndCleanup(true);
		}
	};	

	schedule(Move, FPS, "Move");
	schedule(Disappear, FPS, "Disappear");

	return true;
}

Rect Bullet::Attack()
{
	auto result = Rect(getPositionX() - BULLET_WIDTH / 2, getPositionY() - BULLET_HEIGHT / 2, BULLET_WIDTH, BULLET_HEIGHT);
	return result;
}
