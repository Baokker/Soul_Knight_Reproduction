#include "BattleScene.h"
Scene* BattleScene::createScene() { return BattleScene::create(); }
void BattleScene::menuCloseCallbackEnd(Ref* pSender) { Director::getInstance()->popScene(); }

bool BattleScene::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->knight = Knight::create("Character\\Knight.png");

	this->addChild(knight);
	this->addChild(knight->weapon[knight->Holding]);
	knight->MoveSpeedX = knight->MoveSpeedY = 0;
	knight->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	knight->setGlobalZOrder(6);
	knight->weapon[knight->Holding]->setGlobalZOrder(6);

	initRoom();
	connectRoom(beginRoom);
	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float delta) 
{
	updatePos();	

	if (knight->isMeleeing)
	{
		knight->AttackMelee();
		knight->isMeleeing = false;
	}
	else if (knight->isShooting)
	{
		auto bullet = Bullet::create("Bullet/yellowbullet.png");
		addChild(bullet, 10);
		knight->AttackwithGun(bullet);
		knight->isShooting = false;
	}
}

void BattleScene::updatePos() 
{
	int ispeedX = knight->MoveSpeedX;
	int ispeedY = knight->MoveSpeedY;

	for (int y = 0; y < SIZEMTX; y++) 
	{
		for (int x = 0; x < SIZEMTX; x++) 
		{
			if (battleRoom[x][y] == nullptr) continue;
			BattleRoom* curRoom = battleRoom[x][y];
			bool inRoom = curRoom->boundaryCheck(knight, ispeedX, ispeedY);
			if (inRoom) 
			{
				for (int dir = 0; dir < CNTDIR; dir++) 
				{
					if (curRoom->visDir[dir] == false) continue;
					BattleRoom* nextRoom = battleRoom[x + DIRX[dir]][y + DIRY[dir]];
				}
			}
		}
	}
	for (auto hall : vecHall) 
	{
		bool inHall = hall->boundaryCheck(knight, ispeedX, ispeedY);
	}

	for (int y = 0; y < SIZEMTX; y++) 
	{
		for (int x = 0; x < SIZEMTX; x++) 
		{
			if (battleRoom[x][y] == nullptr) continue;
			BattleRoom* curRoom = battleRoom[x][y];
			curRoom->centerX -= ispeedX, curRoom->centerY -= ispeedY;
			curRoom->changePositionBy(-ispeedX, -ispeedY);
		}
	}
	for (auto hall : vecHall)
	{ 
		hall->changePositionBy(-ispeedX, -ispeedY);
	}
}

void BattleScene::initRoom()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	cntRoom = 0;

	for (int y = 0; y < SIZEMTX; y++) 
	{ 
		for (int x = 0; x < SIZEMTX; x++) 
		{
			battleRoom[x][y] = nullptr;
		}
	}
	srand((time(0)));

	randomGenerate(SIZEMTX / 2, 1 + rand() % 3);

	for (int y = 0; y < SIZEMTX; y++) 
	{
		for (int x = 0; x < SIZEMTX; x++) 
		{
			BattleRoom* curRoom = battleRoom[x][y];
			if (curRoom == nullptr) continue;

			curRoom->knight = knight;
			curRoom->addMapElement();
			memcpy(curRoom->visDirCpy, curRoom->visDir, sizeof(curRoom->visDir));
		}
	}
}

void BattleScene::randomGenerate(int stX, int stY) 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	queue<BattleRoom*> q;

	BattleRoom*& room = battleRoom[stX][stY]; // the pointer will be changed
	room = BattleRoom::create();
	this->beginRoom = room;

	room->x = stX, room->y = stY;
	room->setCenter(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(room, 0);

	q.push(room);
	cntRoom++;

	while (!q.empty()) 
	{
		BattleRoom* curRoom = q.front();
		q.pop();
		// getNextRoomDirection
		getNextRoom(curRoom->x, curRoom->y, curRoom, q);
	}
}

void BattleScene::getNextRoom(int x, int y, BattleRoom* curRoom, queue<BattleRoom*>& q) 
{
	if (cntRoom >= MAXROOM) return;
	srand(time(0));

	vector<int> vecDir;  //save dirctions can go

	for (int dir = 0; dir < 4; dir++)
	{
		if (curRoom->visDir[dir]) continue;  //have  been connected

		int toX = x + DIRX[dir], toY = y + DIRY[dir];
		if (toX < 0 || toX >= SIZEMTX || toY < 0 || toY >= SIZEMTX) continue;  //beyond

		vecDir.push_back(dir);  // directions can go
	}

	if (vecDir.empty()) return;  //no dirction can go

	int cntDirChosen = rand() % vecDir.size();
	// randomly choose direction

	for (int i = 0; i < cntDirChosen; i++)
	{
		int dirIndex = rand() % cntDirChosen;
		int dir = vecDir.at(dirIndex);
		vecDir.erase(vecDir.begin() + dirIndex);
		int toX = x + DIRX[dir], toY = y + DIRY[dir];

		if (battleRoom[toX][toY] == beginRoom) return;

		BattleRoom*& nextRoom = battleRoom[toX][toY];  // the pointer will be changed
		if (BattleRoom::createRoom(nextRoom, curRoom, dir, toX, toY)) 
		{
			this->addChild(nextRoom);
			q.push(nextRoom);
			endRoom = nextRoom;
			cntRoom++;
		}
		assert(battleRoom[toX][toY] != nullptr);
		assert(battleRoom[toX][toY] != beginRoom);
		if (cntRoom >= MAXROOM || curRoom == beginRoom || vecDir.empty()) return;
	}
}

void BattleScene::setHallWithWidth(Hall* hall, const BattleRoom* fromRoom,	const BattleRoom* nextRoom) 
{
	hall->Width = ROOMDISTANCE - fromRoom->Width / 2 - nextRoom->Width / 2 - 1;

	hall->upLeftX = fromRoom->centerX + FLOORWIDTH * (fromRoom->Width / 2 + 1);
	hall->upLeftY = fromRoom->centerY + FLOORHEIGHT * (SIZEHALL / 2 -1);

	hall->downRightX = nextRoom->centerX - FLOORWIDTH * (nextRoom->Width / 2 + 1);
	hall->downRightY = nextRoom->centerY - FLOORHEIGHT * (SIZEHALL / 2 -1);
	hall->createMap();
}

void BattleScene::setHallWithHeight(Hall* hall,	const BattleRoom* fromRoom,	const BattleRoom* nextRoom) 
{
	hall->Height =	ROOMDISTANCE - fromRoom->Height / 2 - nextRoom->Height / 2 - 1;

	hall->upLeftX = fromRoom->centerX - FLOORWIDTH * (SIZEHALL / 2 - 1);
	hall->upLeftY =	fromRoom->centerY - FLOORHEIGHT * (fromRoom->Height / 2 + 1);

	hall->downRightX = nextRoom->centerX + FLOORWIDTH * (SIZEHALL / 2 - 1);
	hall->downRightY = nextRoom->centerY + FLOORHEIGHT * (nextRoom->Height / 2 + 1);
	hall->createMap();
}

void BattleScene::connectRoom(BattleRoom* curRoom)
{
	assert(curRoom != nullptr);
	for (int dir = 0; dir < 4; dir++) 
	{ //4 directions
		if (curRoom->visDirCpy[dir] == false) continue;
		int toX = curRoom->x + DIRX[dir];
		int toY = curRoom->y + DIRY[dir];

		auto nextRoom = battleRoom[toX][toY];

		auto hall = Hall::create();
		hall->knight = knight;
		hall->dir = dir;

		switch (dir) 
		{
		case RIGHT:
			setHallWithWidth(hall, curRoom, nextRoom);
			break;
		case UP:
			setHallWithHeight(hall, nextRoom, curRoom);
			break;
		case LEFT:
			setHallWithWidth(hall, nextRoom, curRoom);
			break;
		case DOWN:
			setHallWithHeight(hall, curRoom, nextRoom);
			break;
		}

		this->addChild(hall);
		vecHall.pushBack(hall);

		curRoom->visDirCpy[dir] = false;
		nextRoom->visDirCpy[(dir + 2) % 4] = false;  //have connected
		connectRoom(nextRoom);
	}
}