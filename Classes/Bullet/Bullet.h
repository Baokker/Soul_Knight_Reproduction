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

class Bullet:public Sprite
/*
it goes like that: in the scene we initialize a vector of bullets and addchild in the scene but set invisible in the init() function.
the bullet will schedule itself so once the character use the weapon to shoot the bullet(which means the weapon sets the movespeed )
it will go itself,and disappear(setvisible(false),stopallactions) itself.
*/

{
	friend class Weapon;
	friend class Knight;
	friend class Enemy;
	friend class SafeScene;
public:
	bool init() override;
	Weapon* BindwithWeapon(Weapon* weapon);
	//bool initBulletwithWeapon(Weapon* weapon);
	//bool Enemyinit(Enemy* enemy);
	//virtual void update(float delta);

	void Move();
private:
	Sprite* sprite = nullptr;
	int damage = 2;
	int MoveSpeed = 10;
	int MoveSpeedX = 0;
	int MoveSpeedY = 0;

};
#endif