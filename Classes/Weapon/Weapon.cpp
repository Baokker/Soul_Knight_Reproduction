/*
* @file   Weapon.cpp
* @author fbc
* @date   2021/5/24
*/

#include"Weapon.h"

bool Weapon::init()
{
	setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	return true;
}

void Weapon::Shoot(Bullet* bullet){}

void Weapon::Attack(){}

bool Gun::init()
{
	if (!Weapon::init())
		return false;

	SetType(isGun);
	Setdamage(2);

	return true;
}

void Gun::Shoot(Bullet* bullet)
{
	bullet->setPosition(getPosition());
	bullet->setVisible(true);
	bullet->damage = Getdamage();
	bullet->MoveSpeed = GetBulletspeed();
	if (isFlippedX())
	{
		bullet->MoveSpeedX = -bullet->MoveSpeed;
	}
	else
	{
		bullet->MoveSpeedX = +bullet->MoveSpeed;
	}
}

int Gun::GetBulletspeed()
{
	return Bulletspeed;
}

int Weapon::Getdamage()
{
	return damage;
}

int Weapon::GetType()
{
	return Type;
}

void Gun::SetBulletspeed(int num)
{
	Bulletspeed = num;
}

void Weapon::Setdamage(int num)
{
	damage = num;
}

void Weapon::SetType(int num)
{
	Type = num;
}

bool Melee::init()
{
	if (!Weapon::init())
		return false;

	Setdamage(3);
	SetType(isMelee);
	return true;
}

void Melee::Attack()
{
}
