#include "Hall.h"
#include "BattleScene.h"

bool Hall::init() 
{
	upLeftX = 0, upLeftY = 0, downRightX = 0, downRightY = 0;
	Height = SIZEHALL;
	Width = SIZEHALL;
	this->scheduleUpdate();
	return true;
}

bool Hall::boundaryCheck(Knight* knight, float& ispeedX, float& ispeedY)
{
	int knightX = knight->getPositionX();
	int knightY = knight->getPositionY();

	if (dir % 2 == 1)
	{
		if (knightX >= upLeftX - FLOORWIDTH && knightX <= downRightX + FLOORWIDTH &&
			knightY <= upLeftY + FLOORHEIGHT + 30 && knightY >= downRightY - FLOORHEIGHT - 15)
		{
			if (ispeedX > 0 && knightX >= downRightX)
				ispeedX = .0f;
			else if (ispeedX < 0 && knightX <= upLeftX)
				ispeedX = .0f;
		}
	}
	else {
		if (knightX >= upLeftX - FLOORWIDTH - 30 && knightX <= downRightX + FLOORWIDTH + 30 &&
			knightY <= upLeftY + FLOORHEIGHT && knightY >= downRightY - FLOORHEIGHT)
		{
			if (ispeedY > 0 && knightY >= upLeftY + FLOORHEIGHT / 2)
				ispeedY = .0f;
			else if (ispeedY < 0 && knightY <= downRightY)
				ispeedY = .0f;
		}
	}

	if (knightX > upLeftX - FLOORWIDTH && knightX < downRightX + FLOORWIDTH &&
		knightY < upLeftY + FLOORHEIGHT && knightY > downRightY - FLOORHEIGHT)
		return true;
	return false;
}
