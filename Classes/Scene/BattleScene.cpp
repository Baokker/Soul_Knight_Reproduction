#include "BattleScene.h"
#include "SafeScene.h"
#include"SetScene.h"

Scene* BattleScene::createScene() { return BattleScene::create(); }
void BattleScene::menuCloseCallbackEnd(Ref* pSender) { Director::getInstance()->popScene(); }

bool BattleScene::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->knight = Knight::create();

	this->addChild(knight);
	this->addChild(knight->weapon[knight->Holding], 1);

	knight->MoveSpeedX = knight->MoveSpeedY = 0;
	knight->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	knight->setGlobalZOrder(6);
	knight->weapon[knight->Holding]->setGlobalZOrder(6);

	initRoom();
	connectRoom(beginRoom);
	//menu_exit
	auto exitImg = MenuItemImage::create("menu//exit.png", "menu//exit01.png", CC_CALLBACK_1(BattleScene::menuCloseCallbackEnd_menu, this));
	auto exitmenu = Menu::create(exitImg, NULL);
	exitmenu->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));
	this->addChild(exitmenu, 100);
	exitmenu->setGlobalZOrder(10);
	//menu_set
	auto setItem = MenuItemImage::create("menu\\set.png", "menu\\set.png", CC_CALLBACK_1(BattleScene::menuCloseCallbackSet_menu, this));
	auto setmenu = Menu::create(setItem, NULL);
	setmenu->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 100));
	this->addChild(setmenu, 20);
	setmenu->setGlobalZOrder(10);
	//Status Bar
	auto StatusBackGround = Sprite::create("Character//StatusBackground.png");

	BloodLoadingBar = ui::LoadingBar::create("Character//StatusBlood.png");
	ArmorLoadingBar = ui::LoadingBar::create("Character//StatusArmor.png");
	MPLoadingBar = ui::LoadingBar::create("Character//StatusMP.png");

	BloodLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	ArmorLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	MPLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);

	StatusBackGround->setPosition(80, 680);
	BloodLoadingBar->setPosition(Vec2(89, 698));
	ArmorLoadingBar->setPosition(Vec2(89, 680));
	MPLoadingBar->setPosition(Vec2(89, 664));

	this->addChild(StatusBackGround, 100);
	this->addChild(BloodLoadingBar, 100);
	this->addChild(ArmorLoadingBar, 100);
	this->addChild(MPLoadingBar, 100);
	StatusBackGround->setGlobalZOrder(10);
	BloodLoadingBar->setGlobalZOrder(10);
	ArmorLoadingBar->setGlobalZOrder(10);
	MPLoadingBar->setGlobalZOrder(10);
	HPLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);
	armorLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);
	MPLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);

	HPLabel->setPosition(Vec2(89, 698));
	armorLabel->setPosition(Vec2(89, 680));
	MPLabel->setPosition(Vec2(89, 664));


	this->addChild(HPLabel, 100);
	this->addChild(armorLabel, 100);
	this->addChild(MPLabel, 100);
	HPLabel->setGlobalZOrder(10);
	armorLabel->setGlobalZOrder(10);
	MPLabel->setGlobalZOrder(10);
	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float delta) 
{
	//check if die
	if (knight->CheckifDie())
	{
		auto safescene = SafeScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
	}

	updatePos();	
	
	//Status update
	BloodLoadingBar->setPercent(this->knight->GetHP() * 100 / 5);
	ArmorLoadingBar->setPercent(this->knight->GetShield() * 100 / 5);
	MPLoadingBar->setPercent(float(this->knight->GetMP()) / 200.0f * 100);

	HPLabel->setString(Value(this->knight->HP).asString() + "/5");
	armorLabel->setString(Value(this->knight->Shield).asString() + "/5");
	MPLabel->setString(Value(this->knight->MP).asString() + "/200");
	//
	//check
	if (knight->isMeleeing)
	{
		knight->AttackMelee();
		knight->isMeleeing = false;
	}
	else if (knight->isShooting)
	{
		auto bullet = Bullet::create("Bullet/yellowbullet.png");
		addChild(bullet, 40);
		knight->AttackwithGun(bullet);
		//knight->deductHP(2);
		knight->isShooting = false;
	}
	knight->resumeShield();
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

void BattleScene::menuCloseCallbackEnd_menu(Ref* pSender)
{
	//Director::getInstance()->popScene();
	auto safescene = SafeScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
}
void BattleScene::menuCloseCallbackSet_menu(Ref* pSender)
{
	auto setscene = SetScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}