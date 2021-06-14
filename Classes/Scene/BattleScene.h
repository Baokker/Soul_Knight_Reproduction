#pragma once
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "..\Actor\Character\Knight.h"
#include "BattleRoom.h"
#include "Hall.h"
#include "..\Const.h"
#include "cocos2d.h"
#include <queue>

USING_NS_CC;
using std::queue;
using std::vector;
using std::string;

class BattleScene : public Scene 
{
	friend class SafeScene;
	friend class Knight;
	friend class Weapon;
	static constexpr int SIZEMTX = 5;
	static constexpr int MAXROOM = 6; // temporarily make it 6
	CREATE_FUNC(BattleScene);

public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float delta) override;

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);
	void menuCloseCallbackSet(cocos2d::Ref* pSender);

private:
	void updatePos();
	void initRoom();
	void getNextRoom(int, int, BattleRoom*, queue<BattleRoom*>&);
	void randomGenerate(int, int);
	void setHallWithWidth(Hall*, const BattleRoom*, const BattleRoom*);
	void setHallWithHeight(Hall*, const BattleRoom*, const BattleRoom*);
	void connectRoom(BattleRoom*);
	static string sceneType;
	int cntRoom = 0;
	Knight* knight;
	Vector<Hall*> vecHall;
	Vector<Bullet*> vecBullet;

	BattleRoom* beginRoom = nullptr;
	BattleRoom* endRoom = nullptr;
	BattleRoom* battleRoom[SIZEMTX][SIZEMTX] = { nullptr };  // rooms

	//useless now
	//int SelectedBulletNum = 0;
	//int MaxBulletNum = 200;
	//vector<Bullet*> bullets = vector<Bullet*>(MaxBulletNum);//bullets
};

#endif
