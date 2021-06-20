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

void Enemy::SetEnemyCD(int num)
{
	EnemyCD = num;
}

int Enemy::GetEnemyCD()
{
	return EnemyCD;
}

void Enemy::initEnemyCD()
{
}

int Enemy::GetEnemyCurtime()
{
	return EnemyCurtime;
}

void Enemy::SetEnemyCurtime(int num)
{
	EnemyCurtime = num;
}

void GunEnemy::initEnemyCD()
{
	auto checkenemycd = [this](float)
	{
		if (GetEnemyCurtime() < 0 + BulletNumAtaTime * GetWeapon()->GetCD() && GetWeapon()->CheckifCanAttack() && !GetisInBattle())
		{
			SetisInBattle(true);
		}
		else
		{
			SetisInBattle(false);
		}

		SetEnemyCurtime(GetEnemyCurtime() == GetEnemyCD() ? 0 : GetEnemyCurtime() + 1);
	};

	schedule(checkenemycd, FPS, "checkenemycd");
}

void Enemy::Wandering()
{
	//srand(time(NULL));
	int frequency = 30;
	int isMoving = random() % frequency;
	if (isMoving <= frequency - 5)
		return;
	int direction = random() % 4;
	const int distance = 30;
	switch (direction)
	{
		case UP:
			//if (getPositionY() + distance < Director::getInstance()->getWinSize().height)
		{
			auto bindRoom = getBindRoom();
			float toX, toY;
			toX = getPositionX(); toY = getPositionY() + distance;
			if (bindRoom->boundaryCheck(this, toX, toY))
			{
				runAction(MoveTo::create(0.5, Vec2(getPositionX(), getPositionY() + distance)));
			}
			else
			{
				int distanceX, distanceY, distance_;
				distance_ = sqrt(pow(double(getPositionX() - bindRoom->centerX), 2) + pow(double(getPositionY() - bindRoom->centerY), 2));
				distanceX = 10 * (getPositionX() - bindRoom->centerX) / distance_;
				distanceY = 10 * (getPositionY() - bindRoom->centerY) / distance_;
				runAction(MoveBy::create(0.5, Vec2(-distanceX, -distanceY)));
			}
		}
		break;
		case DOWN:
			//if (getPositionY() - distance > 0)
		{
			auto bindRoom = getBindRoom();
			float toX, toY;
			toX = getPositionX(); toY = getPositionY() - distance;
			if (bindRoom->boundaryCheck(this, toX, toY))
			{
				runAction(MoveTo::create(0.5, Vec2(getPositionX(), getPositionY() - distance)));
			}
			else
			{
				int distanceX, distanceY, distance_;
				distance_ = sqrt(pow(double(getPositionX() - bindRoom->centerX), 2) + pow(double(getPositionY() - bindRoom->centerY), 2));
				distanceX = 10 * (getPositionX() - bindRoom->centerX) / distance_;
				distanceY = 10 * (getPositionY() - bindRoom->centerY) / distance_;
				runAction(MoveBy::create(0.5, Vec2(-distanceX, -distanceY)));
			}
		}
		break;
		case LEFT:
			//if (getPositionX() - distance > 0)
		{
			auto bindRoom = getBindRoom();
			float toX, toY;
			toX = getPositionX() - distance; toY = getPositionY();
			if (bindRoom->boundaryCheck(this, toX, toY))
			{
				runAction(MoveTo::create(0.5, Vec2(getPositionX() - distance, getPositionY())));
			}
			else
			{
				int distanceX, distanceY, distance_;
				distance_ = sqrt(pow(double(getPositionX() - bindRoom->centerX), 2) + pow(double(getPositionY() - bindRoom->centerY), 2));
				distanceX = 10 * (getPositionX() - bindRoom->centerX) / distance_;
				distanceY = 10 * (getPositionY() - bindRoom->centerY) / distance_;
				runAction(MoveBy::create(0.5, Vec2(-distanceX, -distanceY)));
			}
			if (!isFlippedX())
			{
				setFlippedX(true);
			}
		}
		break;
		case RIGHT:
			//if (getPositionX() + distance < Director::getInstance()->getWinSize().width)
		{
			auto bindRoom = getBindRoom();
			float toX, toY;
			toX = getPositionX() + distance; toY = getPositionY();
			if (bindRoom->boundaryCheck(this, toX, toY))
			{
				runAction(MoveTo::create(0.5, Vec2(getPositionX() + distance, getPositionY())));
			}
			else
			{
				int distanceX, distanceY, distance_;
				distance_ = sqrt(pow(double(getPositionX() - bindRoom->centerX), 2) + pow(double(getPositionY() - bindRoom->centerY), 2));
				distanceX = 10 * (getPositionX() - bindRoom->centerX) / distance_;
				distanceY = 10 * (getPositionY() - bindRoom->centerY) / distance_;
				runAction(MoveBy::create(0.5, Vec2(-distanceX, -distanceY)));
			}
			//setPosition(getPositionX() + distance, getPositionY());
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

BattleRoom* Enemy::getBindRoom()
{
	return bindRoom;
}

void Enemy::setBindRoom(BattleRoom* battleroom)
{
	bindRoom = battleroom;
}

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
	if (distance >= GetAttackRange() || distance < 5)
	{
		if (distance >= GetAttackRange())
		{
			SetisInBattle(false);
			Wandering();
		}
		return;
	}
	else
	{
		if (GetWeapon()->CheckifCanAttack())
			SetisInBattle(true);
		else
			SetisInBattle(false);

		//srand(time(NULL));
		//if (rand() % 4 < 1)
		//	setPosition(getPositionX() + GetMoveSpeed() * distanceX / distance, getPositionY() + GetMoveSpeed() * distanceY / distance);
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

Poison* Enemy::MakePoison(Knight* knight)
{
	auto poison = Poison::createAndBindwithKnight(knight);
	poison->setPosition(getPosition());

	//Director::getInstance()->getRunningScene()->addChild(poison, 3);//need to adjust with battlescene

	getBindRoom()->addChild(poison);
	return poison;
}

Confusion* Enemy::MakeConfusion(Knight* knight)
{
	auto confusion = Confusion::createAndBindwithKnight(knight);
	confusion->setPosition(getPosition());

	getBindRoom()->addChild(confusion);
	//Director::getInstance()->getRunningScene()->addChild(confusion);//need to adjust with battlescene

	return confusion;
}

Explosion* Enemy::MakeExplosion(Knight* knight)
{
	auto explosion = Explosion::createAndBindwithKnight(knight);
	explosion->setPosition(getPosition());

	//Director::getInstance()->getRunningScene()->addChild(explosion, 3);//need to adjust with battlescene
	getBindRoom()->addChild(explosion);

	return explosion;
}

Slowdown* Enemy::MakeSlowdown(Knight* knight)
{
	auto slowdown = Slowdown::createAndBindwithKnight(knight);
	slowdown->setPosition(getPosition());

	//Director::getInstance()->getRunningScene()->addChild(slowdown, 3);//need to adjust with battlescene
	getBindRoom()->addChild(slowdown);

	return slowdown;
}

void Enemy::SetAttackRange(int num)
{
	AttackRange = num;
}

int Enemy::GetAttackRange()
{
	return AttackRange;
}

bool Enemy::GetisInBattle()//judge if die first
{
	return CheckifDie() ? false : isInBattle;
}

void Enemy::SetisInBattle(bool flag)
{
	isInBattle = flag;
}

void Enemy::SetMAX_HP(int num){MAX_HP = num;}

int Enemy::GetMAX_HP(){return MAX_HP;}

int Enemy::GetHP(){return HP;}

void Enemy::SetHP(int num)
{
	if (GetHP() > num)
	{
		addChild(FloatText::create(std::to_string(num-GetHP()), Vec2(getContentSize().width / 2, getContentSize().height + rand()%6*5), 0.5 , 25));
	}
	HP = num;
}

void Enemy::SetWeapon(Weapon* myweapon){weapon = myweapon;}

bool GunEnemy::init()
{
	if (!Enemy::init())
		return false;

	//enemy
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height);

	//weapon
	auto gun = EnemyGun::create();//don't need an image of weapon
	SetWeapon(gun);

	GetWeapon()->SetCD(60);

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
	SetAttackRange(GUN_ENEMY_ATTACK_RANGE);
	SetShortesetApproachDistance(180);
	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

void GunEnemy::AImonitor(Knight* knight)
{
	Enemy::AImonitor(knight);

	if (rand() % 3 == 0)
		Wandering();
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
	GetWeapon()->Setdamage(3);

	GetWeapon()->SetCD(300);

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
	SetAttackRange(MELEE_ENEMY_ATTACK_RANGE);
	SetShortesetApproachDistance(60);
	schedule(WeaponFollow, FPS, "WeaponFollow");
	return true;
}

Rect MeleeEnemy::AttackMelee()
{
	return dynamic_cast<Melee*>(GetWeapon())->Attack();
}

void MeleeEnemy::AImonitor(Knight* knight)
{
	Enemy::AImonitor(knight);

	if (GetisInBattle())
	{
		auto movebyX = knight->getPositionX() - getPositionX() - 10;
		auto movebyY = knight->getPositionY() - getPositionY() - 10;

		auto visiblesize = Director::getInstance()->getVisibleSize();

		if (getPositionX() + movebyX > visiblesize.width || getPositionX() + movebyX < 0)
			movebyX = 0;
		if (getPositionY() + movebyY > visiblesize.height || getPositionY() + movebyY < 0)
			movebyY = 0;
		auto bindRoom = getBindRoom();
		float toX, toY;
		toX = getPositionX() + movebyX; toY = getPositionY() + movebyY;
		bindRoom->boundaryCheck(this, toX, toY);
		movebyX = toX - getPositionX(); movebyY = toY - getPositionY();
		if (movebyX || movebyY)
		{
			runAction(MoveBy::create(30 * FPS, Vec2(movebyX, movebyY)));
		}
	}
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

