/*
* @file   Actor.cpp
* @author fbc
* @date   2021/6/4
* @modified name date
*/

#include"Actor.h"

bool Actor::init() { return true; }

void Actor::AttackwithGun(Bullet* bullet){}

void Actor::AttackMelee(){}

int Actor::GetMoveSpeed()
{
	return MoveSpeed;
}

int Actor::GetMoveSpeedX()
{
	return MoveSpeedX;
}

int Actor::GetMoveSpeedY()
{
	return MoveSpeedY;
}

void Actor::SetMoveSpeed(int num)
{
	MoveSpeed = num;
}

void Actor::SetMoveSpeedX(int num)
{
	MoveSpeedX = num;
}

void Actor::SetMoveSpeedY(int num)
{
	MoveSpeedY = num;
}

