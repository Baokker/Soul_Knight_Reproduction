/*
* @file   Enemy.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Enemy.h";

bool Enemy::init()
{
	if (!Actor::init())
		return false;

	return true;
}

void Enemy::AttackwithGun(Bullet* bullet){}

void Enemy::AttackMelee(){}

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

Weapon* Enemy::GetWeapon(){	return weapon;}

bool Enemy::GetisInBattle(){return isInBattle;}

void Enemy::SetMAX_HP(int num){MAX_HP = num;}

int Enemy::GetMAX_HP(){return MAX_HP;}

int Enemy::GetHP(){return HP;}

void Enemy::SetHP(int num){HP = num;}

void Enemy::SetWeapon(Weapon* myweapon){weapon = myweapon;}

bool GunEnemy::init()
{
	if (!Enemy::init())
		return false;

	//enemy
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);

	//weapon
	auto gun = Gun::create();//don't need an image of weapon
	SetWeapon(gun);

	auto WeaponFollow = [this](float) {
		if (isFlippedX())//right direction as default
		{
			GetWeapon()->setPosition(getPosition());
			GetWeapon()->setFlippedX(false);
		}
		else
		{
			GetWeapon()->setPosition(getPosition());
			GetWeapon()->setFlippedX(true);
		}
	};

	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

void GunEnemy::AttackwithGun(Bullet* bullet)
{
	dynamic_cast<Gun*>(GetWeapon())->Shoot(bullet);
}

bool MeleeEnemy::init()
{
	if (!Enemy::init())
		return false;

	//enemy
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);

	//weapon
	auto melee = Melee::create();//don't need an image of weapon
	SetWeapon(melee);

	auto WeaponFollow = [this](float) {
		if (isFlippedX())//right direction as default
		{
			GetWeapon()->setPosition(this->getPosition());
			GetWeapon()->setFlippedX(false);
		}
		else
		{
			GetWeapon()->setPosition(this->getPosition());
			GetWeapon()->setFlippedX(true);
		}
	};

	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

void MeleeEnemy::AttackMelee()
{
	dynamic_cast<Melee*>(GetWeapon())->Attack();
}

