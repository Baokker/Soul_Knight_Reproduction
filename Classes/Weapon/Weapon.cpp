/*
* @file   Weapon.cpp
* @author fbc
* @date   2021/5/24
*/

#include"Weapon.h"
#include"cocos2d.h"

USING_NS_CC;
/*
Weapon::Weapon()
{
	//init();
}

void Weapon::update(float delta)
{

}
*/



void Weapon::bindWithKnight(Knight* master)
{
	knight = master;
}

bool Weapon::init()
{
	sprite = Sprite::create("Weapon\\Pistol.png");
	sprite->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	return true;
}

bool Weapon::Enemyinit()
{
	sprite = Sprite::create();
	sprite->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	return true;
}


Bullet* Weapon::Shoot()
{
	Bullet bullet;
	bullet.init();
	bullet.sprite->setPosition(sprite->getPosition());

	return NULL;
}


void Weapon::Shoot(Bullet& bullet)
{
	bullet.sprite->setPosition(sprite->getPosition());
	bullet.sprite->setVisible(true);
	if (sprite->isFlippedX())
	{
		bullet.MoveSpeedX = -bullet.MoveSpeed;
	}
	else
	{
		bullet.MoveSpeedX = +bullet.MoveSpeed;
	}

	//damage set,and so on
}

