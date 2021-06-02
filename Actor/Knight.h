/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/
#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "cocos2d.h"
//#include<Scene/SafeScene.h> this will cause two header files contain each other!
USING_NS_CC;
class Hall;
class BattleRoom;
class Knight : public Node//reorginaze the arrangement of Knight
{
	friend class SafeScene;
	//the format should go like the following:
public://mostly unwritten
	void attack();
	void move();
	int MoveSpeedX = 0;
	int MoveSpeedY = 0;
	Sprite* sprite;

	CREATE_FUNC(Knight);

	void bindBattleRoom(BattleRoom*);

	void bindHall(Hall*);
	/*
	* @author fbc
	* @date 2021/5/15
	* @function create a sprite of Knight
	*/
	virtual bool init();
	void setKnightKeyboardListener();
	~Knight();
private:
	int MaxHP = 5;
	int HP = 5;
	int MaxMP = 200;
	int MP = 200;
	int MaxShield = 5;
	int Shield = 5;
	int Money = 0;
	int MoveSpeed = 10;

	bool isMoving = false;
	Animate* MoveAnimate;


	BattleRoom* atBattleRoom = nullptr;
	Hall* atHall = nullptr;

};
#endif