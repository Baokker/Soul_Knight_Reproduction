#pragma once
#ifndef _MAPROOM_H_
#define _MAPROOM_H_

#include "cocos2d.h"
#include "Const.h"
#include "Actor\Character\Knight.h"

USING_NS_CC;

class MapRoom : public Node
{
	friend class BattleScene;
	friend class Hall;
public:
	CREATE_FUNC(MapRoom);

	virtual bool init();
	virtual void createMap();
	virtual void changePositionBy(int, int);
	virtual bool boundaryCheck(Knight*, int&, int&);
	void createFloor(int, int, int);
	void createWall(int, int, int, bool);
	Knight* getKnight();

protected:
	int upLeftX, upLeftY, downRightX, downRightY;
	int dir;
	Knight* knight = nullptr;
	int Height, Width;  // cnt of sprites in Height and Width
};

#endif  // _MAP_H_
