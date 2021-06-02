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

class Enemy:public Sprite
{
	friend class SafeScene;
	friend class BattleScene;
	public:
		bool init();
		void Shoot(Bullet* bullet);
		void Wandering();
		~Enemy();
		CREATE_FUNC_WITH_FILE(Enemy);
	private:
		Weapon *weapon = nullptr;
		bool isInBattle = true;
};
#endif