/*
* @file   Weapon.cpp
* @author fbc
* @date   2021/5/24
*/

#include"Weapon.h"

bool Weapon::init()
{
	setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	initCheckCD();

	return true;
}

void Weapon::Shoot(Bullet* bullet){}

Rect Weapon::Attack() { return Rect(); }

bool Gun::init()
{
	if (!Weapon::init())
		return false;

	SetCD(12);
	SetType(isGun);
	Setdamage(2);
	SetBulletPath("Bullet\\defualt_bullet.png");
	return true;
}

void Gun::Shoot(Bullet* bullet)
{
	bullet->initWithFile(BulletPath);
	bullet->setPosition(getPosition());
	bullet->setVisible(true);
	bullet->Setdamage(Getdamage());
	bullet->SetMoveSpeed(GetBulletspeed());

	SetCurtime(1);
}

int Gun::GetBulletspeed() { return Bulletspeed; }

int Weapon::Getdamage() { return damage; }

int Weapon::GetType() { return Type; }

void Gun::SetBulletspeed(int num) { Bulletspeed = num; }

int Gun::GetMeleeDamage() { return MeleeDamage; }

void Gun::SetMeleeDamage(int num) { MeleeDamage = num; }

string Gun::GetBulletPath()
{
	return BulletPath;
}

void Gun::SetBulletPath(string path)
{
	BulletPath = path;
}

Rect Gun::Attack()
{
	runAction(RotateBy::create(0.2, 360));

	SetCurtime(1);

	auto result = Rect(getPositionX() - MELEE_WIDTH / 2, getPositionY() - MELEE_HEIGHT / 2, MELEE_WIDTH, MELEE_HEIGHT);
	return result;
}

void Weapon::Setdamage(int num) { damage = num; }

void Weapon::SetType(int num) { Type = num; }

void Weapon::initCheckCD()
{
	auto checkcd = [this](float)
	{
		if (GetCurtime() == 0)
			return;
		SetCurtime(GetCurtime() == GetCD() + 1 ? 0 : GetCurtime() + 1);
	};

	schedule(checkcd, FPS, "checkcd");
}

bool Weapon::CheckifCanAttack()
{
	return GetCurtime() == 0;
}

int Weapon::GetCurtime()
{
	return Curtime;
}

void Weapon::SetCurtime(int num)
{
	Curtime = num;
}

int Weapon::GetconsumeMP()
{
	return consumeMP;
}

void Weapon::SetconsumeMP(int num)
{
	consumeMP = num;
}

int Weapon::GetCD()
{
	return CD;
}

void Weapon::SetCD(int num)
{
	CD = num;
}

bool ShotGun::init()
{
	if (!Gun::init())
		return false;

	SetCD(120);
	SetconsumeMP(8);
	Setdamage(20);
	SetBulletspeed(5);
	SetBulletPath("Bullet\\ShotGunBullet.png");

	return true;
}

bool LaserGun::init()
{
	if (!Gun::init())
		return false;

	SetCD(10);
	SetconsumeMP(4);
	Setdamage(8);
	SetBulletspeed(10);
	SetBulletPath("Bullet\\LaserGunBullet.png");

	return true;
}

bool MagicGun::init()
{
	if (!Gun::init())
		return false;

	SetCD(30);
	SetconsumeMP(5);
	Setdamage(12);
	SetBulletspeed(30);
	SetBulletPath("Bullet\\MagicGunBullet.png");

	return true;
}

bool Melee::init()
{
	if (!Weapon::init())
		return false;

	SetCD(20);
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

Animate* Melee::GetAnimate()
{
	return animate;
}

void Melee::SetAnimate(Animate* my_animate)
{
	animate = my_animate;
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

	SetCurtime(1);

	auto result = Rect(getPositionX() - MELEE_WIDTH / 2, getPositionY() - MELEE_HEIGHT / 2, MELEE_WIDTH, MELEE_HEIGHT);
	return result;
}

Melee::~Melee()
{
	if (animate != nullptr)
		animate->release();
}

bool Spear::initAnimate()
{
	auto SpearAnimation = Animation::create();
	std::string filename;
	for (int i = 1; i <= 5; i++)
	{
		filename = "Weapon\\Spear" + std::to_string(i) + ".png";
		SpearAnimation->addSpriteFrameWithFile(filename);
	}
	SpearAnimation->setDelayPerUnit(0.025);
	SpearAnimation->setRestoreOriginalFrame(true);
	SetAnimate(Animate::create(SpearAnimation));
	GetAnimate()->retain();

	return GetAnimate() != nullptr;
}

bool Spear::init()
{
	if (!Melee::init())
		return false;

	SetconsumeMP(2);
	SetCD(30);
	initAnimate();
	Setdamage(8);

	return true;
}

bool SubmachineGun::init()
{
	if (!Gun::init())
		return false;

	SetCD(6);
	SetconsumeMP(1);
	Setdamage(3);
	SetBulletspeed(12);
	SetBulletPath("Bullet\\SubmachineGunBullet.png");

	return true;
}

bool FishGun::init()
{
	if (!Gun::init())
		return false;

	SetCD(30);
	SetconsumeMP(3);
	Setdamage(4);
	SetBulletspeed(8);
	SetBulletPath("Bullet\\FishBullet.png");

	return true;
}

bool EnemyGun::init()
{
	if (!Weapon::init())
		return false;

	SetCD(30);
	SetType(isGun);
	Setdamage(1);
	SetBulletPath("Bullet\\Bullet1.png");
	return true;

}
