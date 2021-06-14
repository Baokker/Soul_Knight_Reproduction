/*
* @file   Weapon.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include<cocos2d.h>
#include"..\Const.h"
#include"..\Bullet\Bullet.h"
#include<vector>

USING_NS_CC;

class Weapon :public Sprite
{
	friend class Actor;

	friend class Knight;

	friend class Enemy;
	friend class GunEnemy;
	friend class MeleeEnemy;

	friend class SafeScene;
	friend class BattleScene;
	public:
		virtual bool init();
		void Shoot(Bullet* bullet);
		Rect Attack();//Melee
		CREATE_FUNC_WITH_FILE(Weapon);//for creating specific weapon
		CREATE_FUNC(Weapon);//for enemy

		int Getdamage();
		int GetType();
		void Setdamage(int num);
		void SetType(int num);
	private:
		int Type = isGun;//default,can set it in inheritance
		int damage = 0;
};

class Gun :public Weapon
{
	friend class Actor;

	friend class Knight;

	friend class Enemy;
	friend class GunEnemy;
	friend class MeleeEnemy;

	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	void Shoot(Bullet* bullet);
	CREATE_FUNC_WITH_FILE(Gun);//for creating specific weapon
	CREATE_FUNC(Gun);//for enemy

	int GetBulletspeed();
	void SetBulletspeed(int num);
	int GetMeleeDamage();
	void SetMeleeDamage(int num);
	Rect Attack();//the gun should also have melee function but with lower damages
private:
	int Bulletspeed = 10;
	int MeleeDamage = 4;
};

class FireGun:public Gun
{
	friend class Actor;

	friend class Knight;

	friend class Enemy;
	friend class GunEnemy;
	friend class MeleeEnemy;

	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	void Shoot(Bullet* bullet);
	CREATE_FUNC_WITH_FILE(FireGun);//for creating specific weapon
	//CREATE_FUNC_WITH_DEFAULT_FILE(Weapon, "Weapon\\Pistol.png");//for knight

private:
};

class Melee :public Weapon
{
	friend class Actor;

	friend class Knight;

	friend class Enemy;
	friend class GunEnemy;
	friend class MeleeEnemy;

	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	bool initAnimate();//default as knight's sword


	Rect Attack();//Melee
	CREATE_FUNC_WITH_FILE(Melee);//for creating specific weapon
	CREATE_FUNC(Melee);//for enemy
	~Melee();
private:
	Animate* animate = nullptr;
	//bool isAnimateRunning = false;
	bool isStartAnimate = false;
};
#endif