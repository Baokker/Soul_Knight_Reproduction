/*
* @file   Poison.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __POISON_H__
#define __POISON_H__

#include"cocos2d.h"
#include"..\Actor\Character\Knight.h"
#include"..\Actor\Enemy\Enemy.h"
#include <Const.h>
#include"..\FloatText\FloatText.h"

USING_NS_CC;

class Poison :public Sprite
{
public:
	bool init();
	int Getdamage();
	void Setdamage(int num);
	bool BindwithKnight(Enemy* enemy, Knight* knight);
	static Poison* createAndBindwithKnight(Enemy* enemy, Knight* knight);

	CREATE_FUNC_WITH_FILE(Poison);
	CREATE_FUNC_WITH_DEFAULT_FILE(Poison, "Item//Poison.png");
private:
	int damage = 1;
	int Curtime = 0;
};

#endif