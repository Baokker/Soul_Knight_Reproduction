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

USING_NS_CC;

class Weapon :public Node
{
	friend class Knight;
	friend class SafeScene;
	friend class Enemy;
	friend class Bullet;
	public:
		bool init();
		bool Enemyinit();
		Bullet* Shoot();
		void Shoot(Bullet& bullet);
		void Attack();//Melee
		//virtual void update(float delta) override;
		void bindWithKnight(Knight* master);
		void bindWithEnemy(Enemy* enemy);
		//Weapon();
		//Weapon(int WeaponType, int WeaponName);
	private:
		Sprite* sprite;
		int Type = isGun;//default,can set it in inheritance
		Knight* knight;
		Enemy* enemy;
};
#endif