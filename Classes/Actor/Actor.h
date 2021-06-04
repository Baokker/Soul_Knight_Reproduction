/*
* @file   Actor.h
* @author fbc
* @date   2021/6/4
* @modified name date
*/

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include<cocos2d.h>
#include"..\Const.h"
#include"Weapon/Weapon.h"
#include"Bullet/Bullet.h"

USING_NS_CC;

class Actor : public Sprite
{
	friend class SafeScene;
	friend class BattleScene;

public:
	bool init();
	virtual void AttackwithGun(Bullet* bullet);
	virtual void AttackMelee();
	int GetMoveSpeed();
	int GetMoveSpeedX();
	int GetMoveSpeedY();

	void SetMoveSpeed(int num);
	void SetMoveSpeedX(int num);
	void SetMoveSpeedY(int num);

	CREATE_FUNC(Actor);
private:
	int MoveSpeed = 10;
	int MoveSpeedX = 0;
	int MoveSpeedY = 0;
};

#endif