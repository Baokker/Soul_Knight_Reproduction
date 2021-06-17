/*
* @file   Boss.h
* @author fbc
* @date   2021/6/16
* @modified name date
*/

#ifndef __BOSS_H__
#define __BOSS_H__

#include"Enemy.h"
#include<cmath>

/*
brainstorm its function:shoot many bullet;throw falling stones from the sky;rotate to create a circle
*/
class Boss :public GunEnemy
{
	friend class SafeScene;
	friend class BattleScene;

	public:
		bool init();

		void AttackwithGun(Bullet* bullet);
		Rect AttackMelee();

		void Teleport(Knight* knight);//shunyi in chinese
		void ShootManyBullets(vector<Bullet*>);

		void AImonitor(Knight* knight);
		CREATE_FUNC_WITH_FILE(Boss);
		CREATE_FUNC_WITH_DEFAULT_FILE(Boss, "Enemy\\Boss1.png");
};

#endif