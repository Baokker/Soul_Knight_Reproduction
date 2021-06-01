/*
* @file   Enemy.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Enemy.h"
#include"cocos2d.h"

USING_NS_CC;

bool Enemy::init()
{
	sprite = Sprite::create("Enemy\\Alien\\enemy001.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	sprite->setPosition(visibleSize.width/2, visibleSize.height/2);

	return true;
}

void Enemy::Shoot(Weapon& weapon,Bullet& bullet)
{
	//bullet.init();
	weapon.Shoot(bullet);
}

/*
Bullet* Enemy::Shoot()
{
	Bullet bullet;
	bullet.init();
	if (sprite->isFlippedX())
	{
		bullet.MoveSpeedX = -bullet.MoveSpeed;
	}
	else
	{
		bullet.MoveSpeedX = +bullet.MoveSpeed;
	}
	return &bullet;
}
*/


bool Enemy::isBindwithWeapon(Weapon& weapon)
{
	return sprite->getBoundingBox().intersectsRect(weapon.sprite->getBoundingBox());//key sentences!!
}

void Enemy::WeaponFollow(Weapon& weapon)
{
	if (!sprite->isFlippedX())//right direction as default
	{
		weapon.sprite->setPosition(sprite->getPositionX() + WeaponAndHeroDistance, sprite->getPositionY());
		weapon.sprite->setFlippedX(false);
	}
	else
	{
		weapon.sprite->setPosition(sprite->getPositionX() - WeaponAndHeroDistance, sprite->getPositionY());
		weapon.sprite->setFlippedX(true);
	}
}

void Enemy::Wandering()
{
	srand(time(NULL));
	int frequency = 30;
	int isMoving = random() % frequency;
	if (isMoving <= frequency - 5)
		return;
	int direction = random() % 4;
	const int distance = 5;
	switch (direction)
	{
		case UP:
			if (sprite->getPositionY() + distance < Director::getInstance()->getWinSize().height)
			{
				sprite->setPosition(sprite->getPositionX(), sprite->getPositionY() + distance);
				if (sprite->isFlippedX())
				{
					sprite->setFlippedX(false);
				}
			}
			break;
		case DOWN:
			if (sprite->getPositionY() + distance > 0)
			{
				sprite->setPosition(sprite->getPositionX(), sprite->getPositionY() - distance);
				if (sprite->isFlippedX())
				{
					sprite->setFlippedX(false);
				}
			}
			break;
		case LEFT:
			if (sprite->getPositionX() + distance > 0)
			{
				sprite->setPosition(sprite->getPositionX() - distance, sprite->getPositionY());
				if (!sprite->isFlippedX())
				{
					sprite->setFlippedX(true);
				}
			}
			break;
		case RIGHT:
			if (sprite->getPositionX() + distance < Director::getInstance()->getWinSize().width)
			{
				sprite->setPosition(sprite->getPositionX() + distance, sprite->getPositionY());
				if (sprite->isFlippedX())
				{
					sprite->setFlippedX(false);
				}
			}
			break;
		default:
			break;
	}
}