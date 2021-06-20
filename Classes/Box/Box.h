/*
* @file   Box.h
* @author wlf
* @date   2021/5/29
* @modified name date
*/

#ifndef __BOX_H__//save time
#define __BOX_H__

#include<cocos2d.h>
#include"..//Actor/Character/knight.h"
#include"..//Const.h"
#include<cmath>
#include<string>
#include"..\FloatText\FloatText.h"
#include"Scene/BattleRoom.h"

USING_NS_CC;
using namespace std;

class Box :public Sprite
{
	friend class SafeScene;
	friend class BattleScene;
	friend class BattleRoom;
	friend class Knight;
public:
	virtual bool init();
	bool isboxwithknight(Knight* knight);
	bool ispropswithknight(Knight* knight);
	BattleRoom* getBindRoom();
	void setBindRoom(BattleRoom* battleroom);

	CREATE_FUNC_WITH_DEFAULT_FILE(Box, "Scene//box.png");

private:
	Knight* knight = nullptr;
	Sprite* props[4];
	bool isopened = false;
	Weapon* boxweapon = nullptr;
	int proptype;
	BattleRoom* bindRoom;
};

#endif



