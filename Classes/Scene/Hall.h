#ifndef _HALL_H_
#define _HALL_H_

#include "cocos2d.h"
#include "Const.h"
#include "Character/Knight.h"
#include "MapRoom.h"

USING_NS_CC;

class Hall : public MapRoom 
{
	CREATE_FUNC(Hall);
	friend class BattleScene;
public:
	bool init();
	bool boundaryCheck(Knight* knight, int& ispeedX, int& ispeedY);
private:
protected:
};

#endif  // _HALL_H_