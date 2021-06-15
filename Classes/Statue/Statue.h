#pragma once
/*
* @file   Statue.h
* @author wlf
* @date   2021/5/29
* @modified name date
*/


#include<cocos2d.h>
#include"..//Actor/Character/knight.h"
#include"..//Const.h"
#include<cmath>
#include<string>

USING_NS_CC;

class Statue :public Sprite
{
	friend class SafeScene;
	friend class Knight;
public:
	virtual bool init();
	bool isstatuewithknight(Knight* knight);

	CREATE_FUNC_WITH_DEFAULT_FILE(Statue, "Statue\\statue1.png");

private:
	Knight* knight = nullptr;
	bool isopened = false;
	int bufftype;
};

