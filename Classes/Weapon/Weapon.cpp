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

Rect Weapon::Attack() { return Rect(); }

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
}

int Gun::GetBulletspeed() { return Bulletspeed; }

int Weapon::Getdamage() { return damage; }

int Weapon::GetType() { return Type; }

void Gun::SetBulletspeed(int num) { Bulletspeed = num; }

int Gun::GetMeleeDamage() { return MeleeDamage; }

void Gun::SetMeleeDamage(int num) { MeleeDamage = num; }

Rect Gun::Attack()
{
	runAction(RotateBy::create(0.2, 360));

	auto result = Rect(getPositionX() - MELEE_WIDTH / 2, getPositionY() - MELEE_HEIGHT / 2, MELEE_WIDTH, MELEE_HEIGHT);
	return result;
}

void Weapon::Setdamage(int num) { damage = num; }

void Weapon::SetType(int num) { Type = num; }

bool Melee::init()
{
	if (!Weapon::init())
		return false;

	Setdamage(5);
	SetType(isMelee);
	return true;
}

bool Melee::initAnimate()//default as knight's sword
{
	auto MeleeAnimation = Animation::create();
	std::string filename;
	for (int i = 1; i <= 4; i++)
	{
		filename = "Weapon\\Sword"+std::to_string(i)+".png";
		MeleeAnimation->addSpriteFrameWithFile(filename);
	}
	MeleeAnimation->setDelayPerUnit(0.025);
	MeleeAnimation->setRestoreOriginalFrame(true);
	animate = Animate::create(MeleeAnimation);
	animate->retain();

	return animate != nullptr;
}

Rect Melee::Attack()
{
	if (animate != nullptr)
	{
		if (!isStartAnimate)
		{
			isStartAnimate = true;
			runAction(animate);
		}
		else
		{
			if (animate->isDone())
				runAction(animate);
		}
	}

	auto result = Rect(getPositionX() - MELEE_WIDTH / 2, getPositionY() - MELEE_HEIGHT / 2, MELEE_WIDTH, MELEE_HEIGHT);
	return result;
}

Melee::~Melee()
{
	if (animate != nullptr)
		animate->release();
}
