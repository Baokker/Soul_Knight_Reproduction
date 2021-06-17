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
#include"..\Bullet\Bullet.h"
#include<vector>

USING_NS_CC;
using std::string;

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

		void initCheckCD();

		bool CheckifCanAttack();

		int GetCurtime();
		void SetCurtime(int num);

		int GetCD();
		void SetCD(int num);

	private:
		int Type = isGun;//default,can set it in inheritance
		int damage = 0;
		int CD = 30;
		int Curtime = 0;
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

	string GetBulletPath();
	void SetBulletPath(string path);

	Rect Attack();//the gun should also have melee function but with lower damages
private:
	string BulletPath = "Bullet\\Bullet1.png";
	int Bulletspeed = 10;
	int MeleeDamage = 4;
};

class SubmachineGun :public Gun
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
	CREATE_FUNC_WITH_FILE(SubmachineGun);
	CREATE_FUNC_WITH_DEFAULT_FILE(SubmachineGun, "Weapon\\SubmachineGun.png");

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

	Animate* GetAnimate();
	void SetAnimate(Animate* my_animate);

	Rect Attack();//Melee
	CREATE_FUNC_WITH_FILE(Melee);//for creating specific weapon
	CREATE_FUNC(Melee);//for enemy
	~Melee();
private:
	Animate* animate = nullptr;
	//bool isAnimateRunning = false;
	bool isStartAnimate = false;
};

class Spear :public Melee
{
	friend class Actor;

	friend class Knight;

	friend class Enemy;
	friend class GunEnemy;
	friend class MeleeEnemy;

	friend class SafeScene;
	friend class BattleScene;
public:
	bool initAnimate();
	bool init();
	CREATE_FUNC_WITH_FILE(Spear);
	CREATE_FUNC_WITH_DEFAULT_FILE(Spear, "Weapon\\Spear.png");

};
#endif