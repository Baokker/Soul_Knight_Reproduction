/*
* @file   Enemy.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include"..\Actor.h"

class Enemy:public Actor
{
	friend class SafeScene;
	friend class BattleScene;
	public:
		bool init();
		void AttackwithGun(Bullet* bullet);
		Rect AttackMelee();
		void Wandering();

		bool GetisInBattle();
		void SetMAX_HP(int num);
		int GetMAX_HP();
		int GetHP();
		void SetHP(int num);
		void SetWeapon(Weapon* myweapon);
		Weapon* GetWeapon();

		void SetAI();

		bool CheckifDie();
		void Die();

		bool GetisAlive();
		void SetisAlive(bool flag);

		CREATE_FUNC_WITH_FILE(Enemy);
		CREATE_FUNC_WITH_DEFAULT_FILE(Enemy, "Enemy\Alien\enemy002.png");
	private:
		Weapon* weapon = nullptr;
		bool isInBattle = false;
		bool isAlive = true;
		int MAX_HP = 10;
		int HP = 10;
};

class GunEnemy :public Enemy
{
	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	void AttackwithGun(Bullet* bullet);
	CREATE_FUNC_WITH_FILE(GunEnemy);
	CREATE_FUNC_WITH_DEFAULT_FILE(GunEnemy, "Enemy\\Alien\\enemy002.png");
private:
};

class MeleeEnemy :public Enemy
{
	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	Rect AttackMelee();
	CREATE_FUNC_WITH_FILE(MeleeEnemy);
	CREATE_FUNC_WITH_DEFAULT_FILE(MeleeEnemy, "Enemy\Alien\enemy001.png");
private:
};
#endif