/*
* @file   Bullet.h
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#ifndef __BULLET_H__
#define __BULLET_H__

#include<cocos2d.h>
#include<Const.h>
#include<map>

USING_NS_CC;

class Bullet :public Sprite
	/*
	it goes like that: in the scene we initialize a vector of bullets and addchild in the scene but set invisible in the init() function.
	the bullet will schedule itself so once the character use the weapon to shoot the bullet(which means the weapon sets the movespeed )
	it will go itself,and disappear(setvisible(false),stopallactions) itself.
	*/

{
	friend class Weapon;
	friend class Gun;
	friend class FireGun;
	friend class Melee;
	friend class SafeScene;
	friend class BattleScene;
public:
	void SetMoveSpeed(int);
	int GetMoveSpeedX();
	void Setdamage(int);
	int GetMoveSpeed();
	void SetMoveSpeedY(int);
	void SetMoveSpeedX(int);
	int GetMoveSpeedY();
	bool init();

	bool GetisUseless();
	void SetisUseless(bool flag);
	int getOwner();
	void setOwner(int owner);
	int Getdamage();

	CREATE_FUNC_WITH_FILE(Bullet);
	CREATE_FUNC_WITH_DEFAULT_FILE(Bullet, "Bullet/defualt_bullet.png");
private:
	int damage = 0;
	int MoveSpeed = 10;
	int MoveSpeedX = 10;
	int MoveSpeedY = 0;

	bool isUseless = false;
	int Owner = KNIGHT;
	//animation
};
#endif