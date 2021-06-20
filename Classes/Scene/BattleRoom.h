#pragma once
#ifndef _BATTLEROOM_H
#define _BATTLEROOM_H

#include "cocos2d.h"
#include "MapRoom.h"
#include "..\Actor\Character\Knight.h"
#include "..\Const.h"

#include "Store/Store.h"
#include "Box/Box.h"
#include "Statue/Statue.h"
#include "Actor/Enemy/Enemy.h"

USING_NS_CC;
using std::string;

class Statue;
class Boss;

class BattleRoom : public MapRoom 
{
	friend class BattleScene;
	friend class Enemy;
	static bool createRoom(BattleRoom*&, BattleRoom*, int, int, int);

public:
	CREATE_FUNC(BattleRoom);

	virtual bool init();
	void addMapElement();
	bool boundaryCheck(Node*, float&, float&);
	void setCenter(int, int);
	void createDoor(int, int, int layer);
	void closeDoor();
	void openDoor();
	void addEnemy();
	void setGunEnemy(GunEnemy*,int,int);
	void setMeleeEnemy(MeleeEnemy*, int, int);
	bool allKilled();

private:
	int centerX, centerY;
	int x, y;
	bool visDir[CNTDIR] = { false }, visDirCpy[CNTDIR];
	Box* box = nullptr;
	Statue* statue = nullptr;
	Store* store = nullptr;
	Boss* boss = nullptr;

protected:
	Vector<Sprite*> openedDoor;
	Vector<Sprite*> closedDoor;
	Vector<Enemy*> vecEnemy;
	Vector<GunEnemy*> vecGunEnemy;
	Vector<MeleeEnemy*> vecMeleeEnemy;
	bool visited = false;
	bool doorOpen = true;
	int roomType;
	Sprite* endPortal = nullptr;

};
#endif
