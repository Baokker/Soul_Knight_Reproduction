/*
* @file   Bullet.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Bullet.h"

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

int Bullet::Getdamage()
{
	return damage;
}

void Bullet::Setdamage(int num)
{
	damage = num;
}

int Bullet::GetMoveSpeed()
{
	return MoveSpeed;
}

void Bullet::SetMoveSpeed(int num)
{
	MoveSpeed = num;
}

int Bullet::GetMoveSpeedX()
{
	return MoveSpeedX;
}

void Bullet::SetMoveSpeedX(int num)
{
	MoveSpeedX = num;
}

int Bullet::GetMoveSpeedY()
{
	return MoveSpeedY;
}

void Bullet::SetMoveSpeedY(int num)
{
	MoveSpeedY = num;
}
