/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

USING_NS_CC;

#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include<cocos2d.h>
#include"Const.h"
#include"Weapon/Weapon.h"
#include"Bullet/Bullet.h"
//#include<Scene/SafeScene.h> this will cause two header files contain each other!

class Knight : public Sprite
{
	friend class SafeScene;
	friend class Weapon;
	//the format should go like the following:
	public://mostly unwritten
		/*
		* @author fbc
		* @date 2021/5/15
		* @function create a sprite of Knight
		*/
		virtual bool init();
		void setKnightKeyboardListener();
		void initWeapon();
		void AttackwithGun(Bullet *bullet);
		void SwitchWeapon();
		void AttackMelee();
		void MoveinSafeScene();
		void WeaponFollow();//useless now
		~Knight();
		CREATE_FUNC_WITH_FILE(Knight);
	private:
		int MaxHP = 5;
		int HP = 5;
		int MaxMP = 200;
		int MP = 200;
		int MaxShield = 5;
		int Shield = 5;

		int Money = 0;
		
		int MoveSpeed = 10;
		int MoveSpeedX = 0;
		int MoveSpeedY = 0;
		
		Weapon* weapon[2] = {};
		int Holding = 0;//decide which weapon to hold
		
		bool isMoving = false;
		
		bool isShooting = false;
		bool isMeleeing = false;
		
		bool isWeaponChanged = false;
		
		bool isHavingOneWeapon = true;
		bool isHavingTwoWeapon = false;
		Animate* MoveAnimate = nullptr;
};
#endif