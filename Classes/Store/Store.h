#pragma once
#ifndef __STORE_H__//save time
#define __STORE_H__

#include<cocos2d.h>
#include"..//Actor/Character/knight.h"
#include"..//Const.h"
#include<cmath>
#include<string>
#include"..\FloatText\FloatText.h"
#include"Scene/BattleRoom.h"

USING_NS_CC;

class Store :public Sprite
{
	friend class SafeScene;
	friend class BattleScene;
	friend class BattleRoom;
	friend class Knight;
public:
	virtual bool init();

	bool isstorewithknight(Knight* knight);
	bool isgoodswithknight(Knight* knight);
	void checkstore(float x, float y, Knight* knight);

	BattleRoom* getBindRoom();
	void setBindRoom(BattleRoom* battleroom);

	CREATE_FUNC_WITH_DEFAULT_FILE(Store, "Scene//Store.png");

private:
	Knight* knight = nullptr;
	Sprite* goods[3];
	FloatText* storeLab;
	FloatText* storeLab_buy;

	Weapon* storeweapon = nullptr;

	bool isopened = false;
	bool Lab_logo = false;
	bool Lab_logo2 = true;
	int goodstype;

	BattleRoom* bindRoom;
	int cost;
	
};

#endif