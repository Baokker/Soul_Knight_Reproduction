#pragma once
#ifndef _BATTLEROOM_H
#define _BATTLEROOM_H

#include "cocos2d.h"
#include "MapRoom.h"
#include "Character/Knight.h"
#include "Const.h"

USING_NS_CC;

class Statue;

class BattleRoom : public MapRoom 
{
	friend class BattleScene;
	static bool createRoom(BattleRoom*&, BattleRoom*, int, int, int);

public:
	CREATE_FUNC(BattleRoom);

	virtual bool init();
	void addMapElement();
	bool boundaryCheck(Knight*, int&, int&);
	void setCenter(int, int);
	void createDoor(int, int, int layer);
	void closeDoor();
	void openDoor();

private:
	int centerX, centerY;
	int x, y;
	bool visDir[CNTDIR] = { false }, visDirCpy[CNTDIR];

protected:
	Vector<Sprite*> openedDoor;
	Vector<Sprite*> closedDoor;

};
#endif