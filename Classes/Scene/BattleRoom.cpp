#include "BattleRoom.h"
#include "BattleScene.h"
#include "Box/Box.h"
#include "Actor/Enemy/Boss.h"

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

void BattleRoom::addMapElement() 
{
	if (roomType != NORMAL && roomType != END)
	{
		Width -= 6;
		Height -= 6;
		if (roomType == BOX)
		{
			box = Box::create();
			box->setBindRoom(this);
			box->setPosition(centerX, centerY);
			this->addChild(box);
			box->setGlobalZOrder(5);
			if (box->proptype <= 2)
			{
				box->props[box->proptype]->setPosition(centerX, centerY);
				this->addChild(box->props[box->proptype]);
				box->props[box->proptype]->setGlobalZOrder(5);
				box->props[box->proptype]->setVisible(false);
			}
			else
			{
				box->boxweapon->setPosition(centerX, centerY);
				this->addChild(box->boxweapon);
				box->boxweapon->setGlobalZOrder(5);
				box->boxweapon->setVisible(false);
			}

		}
		else if (roomType == STATUE)
		{
			statue = Statue::create();
			statue->setPosition(centerX, centerY);
			this->addChild(statue);
			statue->setGlobalZOrder(5);
		}
		else if (roomType == BEGIN)
		{
			store = Store::create();
			store->setBindRoom(this);
			store->setPosition(centerX - 150, centerY + 120);
			store->setGlobalZOrder(5);
			this->addChild(store);
			if (store->goodstype <= 1)
			{
				store->goods[store->goodstype]->setPosition(centerX - 150, centerY + 60);
				store->goods[store->goodstype]->setGlobalZOrder(5);
				store->goods[store->goodstype]->setVisible(false);
				this->addChild(store->goods[store->goodstype]);
			}
			else
			{
				store->storeweapon->setPosition(centerX - 150, centerY + 60);
				this->addChild(store->storeweapon);
				store->storeweapon->setGlobalZOrder(5);
				store->storeweapon->setVisible(false);
			}
		}
		if (roomType == BOSS)
		{
			Width += 6;
			Height += 6;
			boss = Boss::create();
			boss->setBindRoom(this);
			boss->setPosition(centerX, centerY);
			this->addChild(boss);
			addChild(boss->GetWeapon(), 4);
			boss->setGlobalZOrder(5);
			vecEnemy.pushBack(boss);
		}
	}
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
	if (roomType == END)
	{
		Sprite* portal = Sprite::create("Map//portal.png");
		endPortal = portal;
		portal->setPosition(centerX, centerY);
		addChild(portal);
		portal->setGlobalZOrder(5);
	}
}

void BattleRoom::setGunEnemy(GunEnemy* enemy,int X,int Y)
{
	//vecEnemy.pushBack(enemy);
	addChild(enemy);
	enemy->setGlobalZOrder(6);
	addChild(enemy->GetWeapon());
	enemy->GetWeapon()->setGlobalZOrder(6);
	enemy->setPosition(X, Y);
	//enemy->setPosition(X, Y);
}

void BattleRoom::setMeleeEnemy(MeleeEnemy* enemy, int X, int Y)
{
	//vecEnemy.pushBack(enemy);
	addChild(enemy);
	enemy->setGlobalZOrder(6);
	addChild(enemy->GetWeapon());
	enemy->GetWeapon()->setGlobalZOrder(6);
	enemy->setPosition(X, Y);
	//enemy->setPosition(X, Y);
}

void BattleRoom::addEnemy()
{
	//srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		int type;
		type = rand() % 2;		//1 for gun,0 for melee
		if (type)
		{
			auto gunenemy = GunEnemy::create(sceneType);
			gunenemy->bindRoom = this;
			vecEnemy.pushBack(gunenemy);
			vecGunEnemy.pushBack(gunenemy);
		}
		else
		{
			auto meleeenemy = MeleeEnemy::create(sceneType);
			meleeenemy->bindRoom = this;
			vecEnemy.pushBack(meleeenemy);
			vecMeleeEnemy.pushBack(meleeenemy);
			//setEnemy(enemy, rand() % (downRightX - upLeftX + 1) + upLeftX, rand() % (upLeftY - downRightY + 1) + downRightY);
		}
	}
	for (auto gunenemy : vecGunEnemy)
	{
		setGunEnemy(gunenemy, rand() % (downRightX - upLeftX + 1) + upLeftX, rand() % (upLeftY - downRightY + 1) + downRightY);
	}
	for (auto meleeenemy : vecMeleeEnemy)
	{
		setMeleeEnemy(meleeenemy, rand() % (downRightX - upLeftX + 1) + upLeftX, rand() % (upLeftY - downRightY + 1) + downRightY);
	}
}

void BattleRoom::closeDoor() 
{
	doorOpen = false;
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
	doorOpen = true;
	for (auto sprite : openedDoor)
	{
		sprite->setVisible(true);
	}

	for (auto sprite : closedDoor)
	{
		sprite->setVisible(false);
	}
}

bool BattleRoom::boundaryCheck(Node* node, float& ispeedX, float& ispeedY) 
{
	int nodeX = node->getPositionX();
	int nodeY = node->getPositionY();

	if (nodeX >= upLeftX - FLOORWIDTH && nodeX <= downRightX + FLOORWIDTH && nodeY <= upLeftY + FLOORHEIGHT && nodeY >= downRightY - FLOORHEIGHT) 
	{
		if (doorOpen)
		{
			if (((upLeftY + FLOORHEIGHT / 2 - FLOORHEIGHT * (Height / 2 - 3)) >= nodeY && nodeY >= (downRightY + FLOORHEIGHT * (Height / 2 - 3))))  //check the door
			{
				if (ispeedX > 0 && nodeX >= downRightX && !visDir[RIGHT])
					ispeedX = 0;
				if (ispeedX < 0 && nodeX <= upLeftX && !visDir[LEFT])
					ispeedX = 0;
			}
			else if (upLeftX + FLOORHEIGHT * (Height / 2 - 3) <= nodeX && nodeX <= downRightX - FLOORHEIGHT * (Height / 2 - 3))
			{
				if (ispeedY > 0 && nodeY >= upLeftY + FLOORHEIGHT / 2 && !visDir[UP])
					ispeedY = 0;
				if (ispeedY < 0 && nodeY <= downRightY && !visDir[DOWN])
					ispeedY = 0;
			}
			else
			{
				if (ispeedX > 0 && nodeX >= downRightX) ispeedX = 0;
				if (ispeedX < 0 && nodeX <= upLeftX) ispeedX = 0;
				if (ispeedY > 0 && nodeY >= upLeftY) ispeedY = 0;
				if (ispeedY < 0 && nodeY <= downRightY) ispeedY = 0;
			}
		}
		else 
		{
			if (ispeedX > 0 && nodeX >= downRightX) ispeedX = 0;
			if (ispeedX < 0 && nodeX <= upLeftX) ispeedX = 0;
			if (ispeedY > 0 && nodeY >= upLeftY) ispeedY = 0;
			if (ispeedY < 0 && nodeY <= downRightY) ispeedY = 0;
		}
		return true;
	}
	return false;
}

bool BattleRoom::allKilled()
{
	if(!vecEnemy.empty())
		for (auto enemy : vecEnemy)
		{
			if (!(enemy->CheckifDie()))
				return false;
		}
	return true;
}