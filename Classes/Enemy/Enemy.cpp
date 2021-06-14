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
	//enemy
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);

	//weapon
	weapon = Weapon::create();//don't need an image of weapon

	auto WeaponFollow = [this](float) {
		if (isFlippedX())//right direction as default
		{
			this->weapon->setPosition(this->getPosition());
			this->weapon->setFlippedX(false);
		}
		else
		{
			this->weapon->setPosition(this->getPosition());
			this->weapon->setFlippedX(true);
		}
	};

	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

void Enemy::Shoot(Bullet* bullet)
{
	weapon->Shoot(bullet);
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
			if (getPositionY() < Director::getInstance()->getWinSize().height)
			{
				setPosition(getPositionX(), getPositionY() + distance);
				if (isFlippedX())
				{
					setFlippedX(false);
				}
			}
			break;
		case DOWN:
			if (getPositionY() > 0)
			{
				setPosition(getPositionX(), getPositionY() - distance);
				if (isFlippedX())
				{
					setFlippedX(false);
				}
			}
			break;
		case LEFT:
			if (getPositionX() > 0)
			{
				setPosition(getPositionX() - distance, getPositionY());
				if (!isFlippedX())
				{
					setFlippedX(true);
				}
			}
			break;
		case RIGHT:
			if (getPositionX() < Director::getInstance()->getWinSize().width)
			{
				setPosition(getPositionX() + distance, getPositionY());
				if (isFlippedX())
				{
					setFlippedX(false);
				}
			}
			break;
		default:
			break;
	}
}

Enemy::~Enemy()
{
}
