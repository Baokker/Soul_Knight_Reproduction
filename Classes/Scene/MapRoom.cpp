#include "MapRoom.h"
#include "BattleScene.h"
#include "string.h"

bool MapRoom::init()
{
	upLeftX = 0, upLeftY = 0, downRightX = 0, downRightY = 0;
	this->scheduleUpdate();
	return true;
}

void MapRoom::createFloor(int X, int Y, int layer)
{
	string sceneType;
	//sceneType = BattleScene::getSceneType();
	sceneType = "Forest";
	int floorType;
	floorType = rand()%3;
	string dir;
	switch (floorType)
	{
	case 0:dir = "Map//" + sceneType + "//floor1.png"; break;
	case 1:dir = "Map//" + sceneType + "//floor2.png"; break;
	case 2:dir = "Map//" + sceneType + "//floor3.png"; break;
	}
	Sprite* floor;
	floor = Sprite::create(dir);
	this->addChild(floor);
	floor->setGlobalZOrder(layer);
	floor->setPosition(X, Y);
}

void MapRoom::createWall(int X, int Y, int layer, bool addShadow)
{
	string sceneType;
	//sceneType = BattleScene::getSceneType();
	sceneType = "Forest";
	int wallType;
	wallType = rand() % 2;
	string dir;
	switch (wallType)
	{
	case 0:dir = "Map//" + sceneType + "//wall1.png"; break;
	case 1:dir = "Map//" + sceneType + "//wall2.png"; break;
	}
	Sprite* wall=nullptr;
	wall = Sprite::create(dir, Rect(0, 0, 40, 40));		//upside,to show the layer diff
	this->addChild(wall,layer);
	vecWall.pushBack(wall);
	wall->setGlobalZOrder(layer);
	wall->setPosition(X, Y+WALLHEIGHT-FLOORHEIGHT);
	wall = Sprite::create(dir, Rect(0, 35, 40, 25));	//down part
	this->addChild(wall,KNIGHTLAYER-2);
	wall->setGlobalZOrder(KNIGHTLAYER-2);
	wall->setPosition(X, Y + WALLHEIGHT - FLOORHEIGHT - 30);

	if (addShadow)
	{
		Sprite* shadow;
		shadow = Sprite::create("Map//RectShadow.png");
		shadow->setGlobalZOrder(KNIGHTLAYER - 1);
		shadow->setPosition(20, -8);
		shadow->setOpacity(140);
		wall->addChild(shadow);
	}
}

void MapRoom::createMap()
{
	int X = upLeftX - (dir % 2 == 0 ? 0 : FLOORWIDTH);
	int Y = upLeftY + (dir % 2 == 0 ? FLOORHEIGHT : 0);

	int tempX, tempY;
	tempX = X; tempY = Y;
	for (int i = Height - 1; i >= 0; i--)
	{
		for (int j = 0; j <= Width - 1; j++)
		{
			if ((dir % 2 == 0) && i == 0)
				createWall(tempX, tempY, KNIGHTLAYER + 1, false);
			else if ((dir % 2 == 0) && i == Height - 1)
				createWall(tempX, tempY, KNIGHTLAYER - 1, true);
			else if ((dir % 2 == 1) && j == 0)
				createWall(tempX, tempY, KNIGHTLAYER + 1, false);
			else if ((dir % 2 == 1) && j == Width - 1)
				createWall(tempX, tempY, KNIGHTLAYER + 1, false);
			else
				createFloor(tempX, tempY, KNIGHTLAYER - 2);
			tempX += FLOORWIDTH;
		}
		tempX = X;
		tempY -= FLOORHEIGHT;
	}
}

Knight* MapRoom::getKnight()
{
	return knight;
}

bool MapRoom::boundaryCheck(Knight* knight, int& ispeedX, int& ispeedY) 
{
	int knightX = knight->getPositionX();
	int knightY = knight->getPositionY();

	if (knightX >= upLeftX - FLOORWIDTH && knightX <= downRightX + FLOORWIDTH && knightY <= upLeftY + FLOORHEIGHT && knightY >= downRightY - FLOORHEIGHT)
	{
		if (ispeedX > 0 && knightX >= downRightX) ispeedX = 0;
		if (ispeedX < 0 && knightX <= upLeftX) ispeedX = 0;
		if (ispeedY > 0 && knightY >= upLeftY) ispeedY = 0;
		if (ispeedY < 0 && knightY <= downRightY) ispeedY = 0;
		return true;
	}
	return false;
}

void MapRoom::changePositionBy(int deltaX, int deltaY)
{
	upLeftX += deltaX, upLeftY += deltaY;
	downRightX += deltaX, downRightY += deltaY;

	for (auto child : getChildren()) 
	{
		float curX = child->getPositionX();
		float curY = child->getPositionY();
		child->setPosition(Point(curX + deltaX, curY + deltaY));
	}
}