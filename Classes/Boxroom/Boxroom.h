/*
* @file   Boxroom.h
* @author wlf
* @date   2021/5/29
* @modified name date
*/
//#ifndef __STARTSCENE_H__//save time
//#define __STARTSCENE_H__

#include<cocos2d.h>
#include"..//Actor/Character/knight.h"
#include"..//Const.h"
#include<cmath>
#include<string>

USING_NS_CC;

class Box :public Sprite
{
	friend class SafeScene;
	friend class Knight;
public:
	virtual bool init();
	bool isboxwithknight(Knight* knight);
	bool ispropswithknight(Knight* knight);

	CREATE_FUNC_WITH_DEFAULT_FILE(Box, "Scene//box.png");

private:
	Knight* knight = nullptr;
	Sprite* props[3];
	bool isopened = false;
	int proptype;
};

//#endif



