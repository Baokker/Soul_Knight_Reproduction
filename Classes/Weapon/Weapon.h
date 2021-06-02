/*
* @file   Weapon.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include<cocos2d.h>
#include"Const.h"
#include"Bullet/Bullet.h"
#include<vector>

USING_NS_CC;

class Weapon :public Sprite
{
	friend class Knight;
	friend class SafeScene;
	friend class Enemy;
	friend class Bullet;
	public:
		bool init();
		bool Enemyinit();
		void Shoot(Bullet* bullet);
		void Attack();//Melee
		CREATE_FUNC_WITH_FILE(Weapon);
		CREATE_FUNC(Weapon);
	private:
		int Type = isGun;//default,can set it in inheritance
		int damage = 2;
		int Bulletspeed = 10;
};
#endif