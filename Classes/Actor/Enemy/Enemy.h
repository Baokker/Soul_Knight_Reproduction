/*
* @file   Enemy.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include"..\Actor.h"
#include"..\..\Item\Poison.h"
#include"..\..\Item\Explosion.h"
#include"..\..\Item\Debuff.h"
#include"..\..\Item\Confusion.h"
#include"..\..\Item\Slowdown.h"
#include"Scene/BattleRoom.h"


class Enemy:public Actor
{
	friend class SafeScene;
	friend class BattleScene;
	friend class BattleRoom;
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

		BattleRoom* getBindRoom();
		void setBindRoom(BattleRoom* battleroom);

		void AImonitor(Knight* knight);

		bool CheckifDie();
		void Die();

		void SetEnemyCD(int num);
		int GetEnemyCD();
		void initEnemyCD();

		int GetEnemyCurtime();
		void SetEnemyCurtime(int num);

		int GetType();
		void SetType(int type);

		bool GetisAlive();
		void SetisAlive(bool flag);

		void SetShortesetApproachDistance(int num);
		int GetShortestApproachDistance();

		Poison* MakePoison(Knight* knight);
		Confusion* MakeConfusion(Knight* knight);
		Explosion* MakeExplosion(Knight* knight);
		Slowdown* MakeSlowdown(Knight* knight);

		void SetAttackRange(int num);
		int GetAttackRange();

		CREATE_FUNC_WITH_FILE(Enemy);
		CREATE_FUNC_WITH_DEFAULT_FILE(Enemy, "Enemy\\Alien\\enemy002.png");
	private:
		int ShortestApproachDistance = 60;//the enemy can't overlap with the knight
		Weapon* weapon = nullptr;
		bool isInBattle = false;
		bool isAlive = true;
		int MAX_HP = 10;
		int HP = 10;
		int Type = GUN;
		int AttackRange = 0;
		BattleRoom* bindRoom=nullptr;
		int EnemyCD = 360;
		int EnemyCurtime = 0;
};

class GunEnemy :public Enemy
{
	friend class SafeScene;
	friend class BattleScene;
public:
	void initEnemyCD();
	bool init();
	void AImonitor(Knight* knight);
	void AttackwithGun(Bullet* bullet) override;
	CREATE_FUNC_WITH_FILE(GunEnemy);
	CREATE_FUNC_WITH_DEFAULT_FILE(GunEnemy, "Enemy\\Alien\\enemy002.png");
	static GunEnemy* create(std::string scenetype);
private:
	int BulletNumAtaTime = 3;
};

class MeleeEnemy :public Enemy
{
	friend class SafeScene;
	friend class BattleScene;
public:
	bool init();
	Rect AttackMelee() override;
	void AImonitor(Knight* knight);

	CREATE_FUNC_WITH_FILE(MeleeEnemy);
	CREATE_FUNC_WITH_DEFAULT_FILE(MeleeEnemy, "Enemy\\Alien\\enemy001.png");
	static MeleeEnemy* create(std::string scenetype);
private:
};
#endif