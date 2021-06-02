/*
* @file   Weapon.cpp
* @author fbc
* @date   2021/5/24
*/

#include"Weapon.h"
#include"cocos2d.h"

USING_NS_CC;

bool Weapon::init()
{
	setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	
	return true;
}

void Weapon::Shoot(Bullet* bullet)
{
	bullet->setPosition(getPosition());
	bullet->setVisible(true);
	bullet->damage = damage;
	bullet->MoveSpeed = Bulletspeed;
	if (isFlippedX())
	{
		bullet->MoveSpeedX = -bullet->MoveSpeed;
	}
	else
	{
		bullet->MoveSpeedX = +bullet->MoveSpeed;
	}
}

void Weapon::Attack()
{
}

