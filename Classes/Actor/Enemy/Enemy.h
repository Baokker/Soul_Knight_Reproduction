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
		void SetisInBattle(bool flag);
		void SetMAX_HP(int num);
		int GetMAX_HP();
		int GetHP();
		void SetHP(int num);
		void SetWeapon(Weapon* myweapon);
		Weapon* GetWeapon();

		void AImonitor(Knight* knight);

		bool CheckifDie();
		void Die();

		bool GetisAlive();
		void SetisAlive(bool flag);

		void SetShortesetApproachDistance(int num);
		int GetShortestApproachDistance();

		CREATE_FUNC_WITH_FILE(Enemy);
		CREATE_FUNC_WITH_DEFAULT_FILE(Enemy, "Enemy\Alien\enemy002.png");
	private:
		int ShortestApproachDistance = 60;//the enemy can't overlap with the knight
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
	void AttackwithGun(Bullet* bullet) override;
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
	Rect AttackMelee() override;
	CREATE_FUNC_WITH_FILE(MeleeEnemy);
	CREATE_FUNC_WITH_DEFAULT_FILE(MeleeEnemy, "Enemy\\Alien\\enemy001.png");
private:
};
#endif