#include "BattleRoom.h"
#include "BattleScene.h"

void BattleRoom::setCenter(int X, int Y) { centerX = X, centerY = Y; }

bool BattleRoom::init() {
	centerX = 0, centerY = 0;
	upLeftX = 0, upLeftY = 0;
	downRightX = 0, downRightY = 0;
	x = 0, y = 0;
	Height = SIZEROOM, Width = SIZEROOM;

	memset(visDir, false, sizeof(visDir));
	knight = nullptr;
	this->scheduleUpdate();
	return true;
}

bool BattleRoom::createRoom(BattleRoom*& nextRoom, BattleRoom* curRoom, int dir, int toX, int toY) {
	if (nextRoom != nullptr) 
	{
		// room was built, no not need to build again
		curRoom->visDir[dir] = true;
		nextRoom->visDir[(dir + 2) % CNTDIR] = true;
		// just connect them if nextRoom is not beginRoom
		return false;
	}

	nextRoom = BattleRoom::create();

	nextRoom->x = toX, nextRoom->y = toY;
	nextRoom->setCenter(curRoom->centerX + DIRX[dir] * CENTERDIS, curRoom->centerY + DIRY[dir] * CENTERDIS);
	curRoom->visDir[dir] = true;
	nextRoom->visDir[(dir + 2) % CNTDIR] = true;
	return true;
}

void BattleRoom::createDoor(int X, int Y, int layer) 
{
	Sprite* doorOpen;
	doorOpen = Sprite::create("Map//doorOpen.png");
	this->addChild(doorOpen, KNIGHTLAYER - 2);
	doorOpen->setGlobalZOrder(KNIGHTLAYER - 2);
	doorOpen->setPosition(X, Y);
	doorOpen->setVisible(true);
	openedDoor.pushBack(doorOpen);

	Sprite* doorClose;
	doorClose = Sprite::create("Map//doorClose.png");
	this->addChild(doorClose, layer);
	doorClose->setGlobalZOrder(layer);
	doorClose->setPosition(X, Y + FLOORHEIGHT / 2);
	doorClose->setVisible(false);  // closeDoor images are not visible at first
	closedDoor.pushBack(doorClose);
}

void BattleRoom::addMapElement() {
	const int X = centerX - FLOORWIDTH * (Width / 2);
	const int Y = centerY + FLOORHEIGHT * (Height / 2);
	//(X, Y) is upLeft Position;
	upLeftX = X + FLOORWIDTH, upLeftY = Y - FLOORHEIGHT;

	downRightX = X + FLOORWIDTH * (Width - 2);
	downRightY = Y - FLOORHEIGHT * (Height - 2);

	int curX = X, curY = Y;
	for (int H = Height - 1; H >= 0; H--) 
	{
		for (int W = 0; W <= Width - 1; W++)
		{
			if (H == 0 || H == Height - 1 || W == 0 || W == Width - 1) 
			{
				if (((W == 0) && visDir[LEFT] && (Height / 2 - 2 <= H) && (H <= Height / 2 - 2 + SIZEHALL - 3)) ||
					((W == Width - 1) && visDir[RIGHT] && (Height / 2 - 2 <= H) && (H <= Height / 2 - 2 + SIZEHALL - 3)) ||
					((H == 0) && visDir[DOWN] && (Width / 2 - 2 <= W) && (W <= Width / 2 - 2 + SIZEHALL - 3)) ||
					((H == Height - 1) && visDir[UP] && (Width / 2 - 2 <= W) &&	(W <= Width / 2 - 2 + SIZEHALL - 3))) 
				{
					if (H != Height - 1)
						createDoor(curX, curY, KNIGHTLAYER + 1);
					else
						createDoor(curX, curY, KNIGHTLAYER - 1);
				}
				else if (H != Height - 1 || W == 0 || W == Width - 1) 
				{
					if (H == Height / 2 + SIZEHALL - 4)
						createWall(curX, curY, KNIGHTLAYER + 1, true);
					else
						createWall(curX, curY, KNIGHTLAYER + 1, false);
				}
				else if (visDir[UP] && H == Height - 1 && (W == Width / 2 - 3 || W == Width / 2 + SIZEHALL - 4))
				{
					createWall(curX, curY, KNIGHTLAYER + 2, true);
				}
				else
				{
					if (H == Height - 1)  //add shadow to the upside wall
						createWall(curX, curY, KNIGHTLAYER - 1, true);
					else
						createWall(curX, curY, KNIGHTLAYER - 1, false);
				}
			}
			else 
			{
				createFloor(curX, curY, KNIGHTLAYER - 2);
			}

			curX += FLOORWIDTH;
		}
		curX = X, curY -= FLOORHEIGHT;
	}
}
void BattleRoom::closeDoor() 
{
	for (auto sprite : openedDoor) 
	{
		sprite->setVisible(false);
	}

	for (auto sprite : closedDoor) 
	{
		sprite->setVisible(true);
	}
}

void BattleRoom::openDoor() 
{
	for (auto sprite : openedDoor)
	{
		sprite->setVisible(true);
	}

	for (auto sprite : closedDoor)
	{
		sprite->setVisible(false);
	}
}

bool BattleRoom::boundaryCheck(Knight* knight, int& ispeedX, int& ispeedY) 
{
	int knightX = knight->getPositionX();
	int knightY = knight->getPositionY();

	if (knightX >= upLeftX - FLOORWIDTH && knightX <= downRightX + FLOORWIDTH && knightY <= upLeftY + FLOORHEIGHT && knightY >= downRightY - FLOORHEIGHT) 
	{
			if (((upLeftY + FLOORHEIGHT / 2 - FLOORHEIGHT * (Height / 2 - 3)) >=knightY && knightY >= (downRightY + FLOORHEIGHT * (Height / 2 - 3))))  //check the door
			{
				if (ispeedX > 0 && knightX >= downRightX && !visDir[RIGHT])
					ispeedX = 0;
				if (ispeedX < 0 && knightX <= upLeftX && !visDir[LEFT])
					ispeedX = 0;
			}
			else if (upLeftX + FLOORHEIGHT * (Height / 2 - 3) <= knightX && knightX <= downRightX - FLOORHEIGHT * (Height / 2 - 3)) 
			{
				if (ispeedY > 0 && knightY >= upLeftY + FLOORHEIGHT / 2 && !visDir[UP])
					ispeedY = 0;
				if (ispeedY < 0 && knightY <= downRightY && !visDir[DOWN])
					ispeedY = 0;
			}
			else 
			{
				if (ispeedX > 0 && knightX >= downRightX) ispeedX = 0;
				if (ispeedX < 0 && knightX <= upLeftX) ispeedX = 0;
				if (ispeedY > 0 && knightY >= upLeftY) ispeedY = 0;
				if (ispeedY < 0 && knightY <= downRightY) ispeedY = 0;
			}
		return true;
	}
	return false;
}
