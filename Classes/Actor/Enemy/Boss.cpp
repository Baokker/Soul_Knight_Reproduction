#include "Boss.h"
#include"..\Character\Knight.h"

/*
* @file   Boss.cpp
* @author fbc
* @date   2021/6/16
* @modified name date
*/

bool Boss::init()
{
	if (!GunEnemy::init())
		return false;

	setScale(2);
	int BOSS_HP = 100;
	SetHP(100);
	SetMAX_HP(100);
	GetWeapon()->SetCD(600);

	return true;
}

void Boss::AttackwithGun(Bullet* bullet)
{
	dynamic_cast<Gun*>(GetWeapon())->Shoot(bullet);
}

Rect Boss::AttackMelee()
{
	runAction(RotateBy::create(0.5, 360));
	auto Curposition = getPosition();
	auto AttackRange = getContentSize().width;

	GetWeapon()->SetCurtime(1);
	return Rect(Curposition.x - AttackRange / 2, Curposition.y - AttackRange / 2, AttackRange, AttackRange);
}

void Boss::Teleport(Knight* knight)
{
	auto fadeout = FadeOut::create(0.5);
	auto moveto = MoveTo::create(0.01, knight->getPosition());
	auto fadein = FadeIn::create(0.5);
	auto seq = Sequence::create(fadeout, moveto, fadein, NULL);
	runAction(seq);

	GetWeapon()->SetCurtime(1);
}

void Boss::ShootManyBullets(vector<Bullet*> bullets)//unadapted
{
	double pi = 3.1415;
	int num = 20;
	for (int i = 0; i < num; i++)
	{
		AttackwithGun(bullets.at(i));
		bullets.at(i)->SetMoveSpeedX(GetMoveSpeed() * cos(2 * pi / num * i));
		bullets.at(i)->SetMoveSpeedY(GetMoveSpeed() * sin(2 * pi / num * i));
	}
}

void Boss::AImonitor(Knight* knight)
{
	Enemy::AImonitor(knight);
}
