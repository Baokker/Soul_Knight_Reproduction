/*
* @file   Enemy.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include<cocos2d.h>
#include"Weapon/Weapon.h"
#include"Bullet/Bullet.h"
USING_NS_CC;

class Enemy
{
	friend class SafeScene;
	friend class BattleScene;
	public:
		bool init();
		void Shoot(Weapon& weapon,Bullet& bullet);
		bool isBindwithWeapon(Weapon& weapon);
		void Wandering();
		void WeaponFollow(Weapon& weapon);
	private:
		Sprite* sprite;
		bool isInBattle = false;
		int isShoot = 0;
};
#endif