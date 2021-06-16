/*
* @file   Enemy.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Enemy.h"
#include"..\Character\Knight.h"

bool Enemy::init()
{
	if (!Actor::init())
		return false;

	SetMoveSpeed(5);
	SetShortesetApproachDistance(60);
	isInBattle = false;
	return true;
}

void Enemy::AttackwithGun(Bullet* bullet)
{
	dynamic_cast<Gun*>(GetWeapon())->Shoot(bullet);
}

Rect Enemy::AttackMelee()
{
	return Rect();
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

Weapon* Enemy::GetWeapon(){	return weapon;}

void Enemy::AImonitor(Knight* knight)//need knight to adjust
{
	if (!GetisAlive())
		return;
	int distanceX = knight->getPositionX() - getPositionX();
	if (distanceX > 0)
	{
		setFlippedX(false);
	}
	else if (distanceX < 0)
	{
		setFlippedX(true);
	}

	int distanceY = knight->getPositionY() - getPositionY();
	int distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
	if (distance >= ATTACK_RANGE || distance <= GetShortestApproachDistance())
	{
		if (distance >= ATTACK_RANGE)
		{
			SetisInBattle(false);
			Wandering();
		}
		return;
	}
	else
	{
		SetisInBattle(true);
		srand(time(NULL));
		if (rand() % 4 < 1)
			setPosition(getPositionX() + GetMoveSpeed() * distanceX / distance, getPositionY() + GetMoveSpeed() * distanceY / distance);
	}

	return;
}

bool Enemy::CheckifDie(){return GetHP() <= 0;}

void Enemy::Die()
{
	SetisAlive(false);
	stopAllActions();
	setVisible(false);
	setPosition(0, 0);
	unschedule("WeaponFollow");
}

int Enemy::GetType()
{
	return Type;
}

void Enemy::SetType(int type)
{
	Type = type;
}

bool Enemy::GetisAlive()
{
	return isAlive;
}

void Enemy::SetisAlive(bool flag)
{
	isAlive = flag;
}

void Enemy::SetShortesetApproachDistance(int num)
{
	ShortestApproachDistance = num;
}

int Enemy::GetShortestApproachDistance()
{
	return ShortestApproachDistance;
}

bool Enemy::GetisInBattle(){return isInBattle;}

void Enemy::SetisInBattle(bool flag)
{
	isInBattle = flag;
}

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
			GetWeapon()->setFlippedX(true);
		}
		else
		{
			GetWeapon()->setPosition(getPosition());
			GetWeapon()->setFlippedX(false);
		}
	};

	SetType(GUN);
	SetShortesetApproachDistance(180);
	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

void GunEnemy::AttackwithGun(Bullet* bullet)
{
	dynamic_cast<Gun*>(GetWeapon())->Shoot(bullet);
}

GunEnemy* GunEnemy::create(std::string scenetype)
{
	GunEnemy* pRet = new(std::nothrow) GunEnemy(); 
	if (pRet && pRet->initWithFile("Enemy\\"+scenetype+"\\enemy002.png") && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet;
		pRet = nullptr; 
		return nullptr; 
	} 
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

	SetType(MELEE);
	SetShortesetApproachDistance(60);
	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

Rect MeleeEnemy::AttackMelee()
{
	return dynamic_cast<Melee*>(GetWeapon())->Attack();
}

MeleeEnemy* MeleeEnemy::create(std::string scenetype)
{
	MeleeEnemy* pRet = new(std::nothrow) MeleeEnemy();
	if (pRet && pRet->initWithFile("Enemy\\" + scenetype + "\\enemy001.png") && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

