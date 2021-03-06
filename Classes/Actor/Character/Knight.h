/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include"..\Actor.h"
#include<cmath>
#include<string>

//#include<Scene/SafeScene.h> this will cause two header files contain each other!

class Knight : public Actor
{
	friend class SafeScene;
	friend class BattleScene;
	friend class Statue;
	friend class Box;
	friend class Store;

	//the format should go like the following:
	public://mostly unwritten
		/*
		* @author fbc
		* @date 2021/5/15
		* @function create a sprite of Knight
		*/
		bool init();

		void setKnightKeyboardListener();

		void initWeapon();
		void AttackwithGun(Bullet *bullet);
		Weapon* Getweapon();
		void SwitchWeapon();
		bool CheckifHavingWeapon(Weapon* target);
		bool PickupWeapon(Weapon* pickedweapon);

		Rect AttackMelee();
		Rect AttackMeleeWithGun();

		bool CheckifDie();
		bool CheckifMPenough();
		bool CheckifCanAttack();
		void SetChangeDirection();
		void SetAnimate();

		void Getbuff(int num);

		void deductHP(int damage);  //Blood deduction
		void resumeShield();        //Restore armor

		void SetHP(int num);
		int GetHP();
		void SetMP(int num);
		int GetMP();
		void SetMaxHP(int num);
		int GetMaxHP();
		void SetMaxMP(int num);
		int GetMaxMP();
		void AddMP(int num);

		void SetShield(int num);
		int GetShield();
		void SetMaxShield(int num);
		int GetMaxShield();

		int GetMoney();
		void SetMoney(int num);
		void AddMoney(int num);

		void MoveinSafeScene();

		void SetisInConfusion(bool flag);
		bool GetisinConfusion();

		~Knight();

		CREATE_FUNC_WITH_FILE(Knight);
		CREATE_FUNC_WITH_DEFAULT_FILE(Knight,"Character\\Knight.png");
	private:
		int MaxHP = 5;
		int HP = 5;
		int MaxMP = 200;
		int MP = 200;
		int MaxShield = 5;
		int Shield = 5;

		static int Money;
		bool j_press = false;
		
		Weapon* weapon[2] = {};
		int Holding = 0;//decide which weapon to hold
		
		bool isMoving = false;
		
		bool isShooting = false;
		bool isMeleeing = false;
		
		bool isWeaponChanged = false;
		
		bool isPickingupWeapon = false;
		bool isHavingOneWeapon = false;
		bool isHavingTwoWeapon = true;
		Animate* MoveAnimate = nullptr;

		int present;
		bool Soundeffect;

		bool isInConfusion = false;
		bool isGoingBattle = false;
		time_t preAttackedTime = 0, curTime = 0;
};
#endif