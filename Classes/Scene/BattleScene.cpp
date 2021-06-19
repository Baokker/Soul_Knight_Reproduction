#include "BattleScene.h"
#include "SafeScene.h"

Scene* BattleScene::createScene() { return BattleScene::create(); }

void BattleScene::menuCloseCallbackEnd(Ref* pSender) 
{
	//Director::getInstance()->popScene();
	auto safescene = SafeScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
}

void BattleScene::menuCloseCallbackSet(Ref* pSender)
{
	auto setscene = SetScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}

void BattleScene::SetLoadingBar()
{
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
}

void BattleScene::SetMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//menu_exit
	auto exitImg = MenuItemImage::create("menu//exit.png", "menu//exit01.png", CC_CALLBACK_1(BattleScene::menuCloseCallbackEnd, this));
	exitImg->setScale(0.75);
	exitImg->setGlobalZOrder(10);
	auto exitmenu = Menu::create(exitImg, NULL);
	exitmenu->setPosition(Vec2(visibleSize.width - 80, visibleSize.height - 100));
	this->addChild(exitmenu, 100);

	auto exitSprite = Sprite::create("menu\\exit.png");
	exitSprite->setScale(0.75);
	exitSprite->setPosition(Vec2(visibleSize.width - 80, visibleSize.height - 100));
	this->addChild(exitSprite);
	exitSprite->setGlobalZOrder(10);


	//menu_set
	auto setItem = MenuItemImage::create("menu\\set.png", "menu\\set.png", CC_CALLBACK_1(BattleScene::menuCloseCallbackSet, this));
	setItem->setScale(0.75);
	auto setmenu = Menu::create(setItem, NULL);
	setmenu->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 100));
	this->addChild(setmenu, 20);

	auto setSprite = Sprite::create("menu\\set.png");
	setSprite->setScale(0.75);
	setSprite->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 100));
	this->addChild(setSprite);
	setSprite->setGlobalZOrder(10);
}

void BattleScene::UpdateLoadingBar()
{
	//Status update
	BloodLoadingBar->setPercent(this->knight->GetHP() * 100 / knight->MaxHP);
	ArmorLoadingBar->setPercent(this->knight->GetShield() * 100 / knight->MaxShield);
	MPLoadingBar->setPercent(float(this->knight->GetMP()) / float(knight->MaxMP) * 100);

	HPLabel->setString(Value(this->knight->HP).asString() + "/" + Value(this->knight->MaxHP).asString());
	armorLabel->setString(Value(this->knight->Shield).asString() + "/" + Value(this->knight->MaxShield).asString());
	MPLabel->setString(Value(this->knight->MP).asString() + "/" + Value(this->knight->MP).asString());
}

void BattleScene::updateAttack()
{
	if (knight->isMeleeing)
	{
		for (auto enemy : curRoom->vecEnemy)
		{
			if (knight->AttackMelee().intersectsRect(enemy->getBoundingBox()))
			{
				enemy->SetHP(enemy->GetHP() - dynamic_cast<Melee*>(knight->weapon[knight->Holding])->Getdamage());
			}

			knight->isMeleeing = false;
		}
	}
	else if (knight->isShooting)
	{
		auto bullet = Bullet::create("Bullet/yellowbullet.png");
		addChild(bullet);
		int minDis = WALLWIDTH * SIZEROOM;
		for (auto enemy : curRoom->vecEnemy)
		{
			int distance = sqrt(pow(knight->weapon[0]->getPosition().x - enemy->getPosition().x, 2) + pow(knight->weapon[0]->getPosition().y - enemy->getPosition().y, 2));
			if (distance < minDis)
			{
				minDis = distance;
				int mx = enemy->getPosition().x - knight->weapon[0]->getPosition().x;
				int my = enemy->getPosition().y - knight->weapon[0]->getPosition().y;
				bullet->MoveSpeedX = bullet->MoveSpeed * mx / distance;
				bullet->MoveSpeedY = bullet->MoveSpeed * my / distance;
			}

		}
		vecBullet.pushBack(bullet);
		bullet->setGlobalZOrder(6);
		knight->AttackwithGun(bullet);
		knight->isShooting = false;
	}
}

void BattleScene::updateBullet(Bullet* bullet, Enemy* enemy)
{
	if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
	{
		enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
		bullet->setVisible(false);
		bullet->stopAllActions();
		bullet->MoveSpeedX = bullet->MoveSpeedY = 0;
		bullet->removeFromParentAndCleanup(true);
		bullet->setPosition(curRoom->upLeftY + 20, curRoom->upLeftX - 20);
		/*for (int index = 0; index < vecBullet.size(); index++)
		{
			if (vecBullet.at(index) == bullet)
				vecBullet.erase(index);
		}*/
	}
}

bool BattleScene::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->knight = Knight::create();

	this->addChild(knight);
	this->addChild(knight->weapon[0]);
	this->addChild(knight->weapon[1]);
	
	knight->MoveSpeedX = knight->MoveSpeedY = 0;
	knight->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	knight->setGlobalZOrder(6);
	knight->weapon[0]->setGlobalZOrder(6);
	knight->weapon[1]->setGlobalZOrder(6);

	initRoom();
	connectRoom(beginRoom);

	SetLoadingBar();
	SetMenu();

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float delta) 
{
	//check if die
	if (knight->CheckifDie())
	{
		auto safescene = SafeScene::CreateScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
	}
	updateAll();
	updateAttack();

	if (curRoom->box != nullptr)
	{
		if (curRoom->box->isboxwithknight(knight))
		{
			if (curRoom->box->isopened == false && knight->j_press == true)
			{
				curRoom->box->setVisible(false);
				curRoom->box->isopened = true;
				curRoom->box->props[curRoom->box->proptype]->setVisible(true);
				knight->j_press = false;
			}
		}
		if (curRoom->box->ispropswithknight(knight) && curRoom->box->isopened == true && knight->j_press == true)
		{
			if (curRoom->box->proptype == 0)
			{
				knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
				curRoom->box->props[0]->setVisible(false);
			}
			else if (curRoom->box->proptype == 1)
			{
				knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
				curRoom->box->props[1]->setVisible(false);
			}
		}
	}
	
	UpdateLoadingBar();
}

void BattleScene::updateAll() 
{
	float ispeedX = knight->MoveSpeedX;
	float ispeedY = knight->MoveSpeedY;
	for (int y = 0; y < SIZEMTX; y++)
	{
		for (int x = 0; x < SIZEMTX; x++)
		{
			if (battleRoom[x][y] == nullptr) continue;
			if (battleRoom[x][y]->boundaryCheck(knight, ispeedX, ispeedY))
				curRoom = battleRoom[x][y];
			if (curRoom != nullptr&&!curRoom->visited)
			{
				curRoom->visited = true;
				if (curRoom->roomType == NORMAL)
				{
					curRoom->closeDoor();
					curRoom->addEnemy();
				}
			}
			if (curRoom != nullptr&&curRoom->roomType == NORMAL)
			{
				if (curRoom->allKilled())
					curRoom->openDoor();
			}
		}
	}
	if(!vecBullet.empty())
	for (auto bullet : vecBullet)
	{
		for (auto enemy : curRoom->vecEnemy)
		{
			if (vecBullet.empty())
				continue;
			updateBullet(bullet, enemy);
			//AI
			if (!enemy->GetisAlive()) {}
			else
			{
				enemy->AImonitor(knight);
				//srand(time(NULL));
				if (enemy->CheckifDie())
					enemy->Die();
				else if (enemy->GetisInBattle() && rand() % 10 < 1)//attack!
				//if it is a meleeenemy just change the code related to attack 
				{
					if (enemy->GetType() == GUN)
					{
						auto EnemyBullet = Bullet::create();
						EnemyBullet->setGlobalZOrder(6);
						enemy->AttackwithGun(EnemyBullet);
					}
					else if (enemy->GetType() == MELEE)
					{
						auto meleerect = enemy->AttackMelee();
						if (meleerect.intersectsRect(knight->getBoundingBox()))
							knight->deductHP(enemy->GetWeapon()->Getdamage());
					}
				}
			}
		}
		for (auto wall : curRoom->vecWall)
		{
			if (vecBullet.empty())
				continue;
			if (bullet->getBoundingBox().intersectsRect(wall->getBoundingBox()))
			{
				bullet->setVisible(false);
				bullet->stopAllActions();
				bullet->MoveSpeedX = bullet->MoveSpeedY = 0;
				bullet->removeFromParentAndCleanup(true);
			}
		}
		if (vecBullet.empty())
			continue;
	}

	if (curRoom == endRoom && knight->getBoundingBox().intersectsRect(curRoom->endPortal->getBoundingBox()))
	{
		if (knight->isGoingBattle)
		{
			BattleScene::knight->retain();
			BattleScene::knight->removeFromParent();
			auto battlescene = BattleScene::create();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, battlescene, Color3B(255, 255, 255)));
			return;
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
	for (auto bullet : vecBullet)
	{
		bullet->setPosition(bullet->getPosition().x - ispeedX, bullet->getPosition().y - ispeedY);
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
			BattleRoom* Room = battleRoom[x][y];
			if (Room == nullptr) continue;
			else if (Room == beginRoom)
				Room->roomType = BEGIN;
			else if (Room == endRoom)
				Room->roomType = END;
			else
			{
				int special;
				special = rand() % 2;
				if (special&&!Type.empty())
				{
					special = rand() % Type.size();
					Room->roomType = Type.at(special);
					Type.erase(Type.begin()+special);
				}
				else
					Room->roomType = NORMAL;
			}
			Room->knight = knight;
			Room->addMapElement();
			memcpy(Room->visDirCpy, Room->visDir, sizeof(Room->visDir));
		}
	}
}

void BattleScene::randomGenerate(int stX, int stY) 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	queue<BattleRoom*> roomQueue;

	BattleRoom*& room = battleRoom[stX][stY]; // the pointer will be changed
	room = BattleRoom::create();
	this->beginRoom = room;

	room->x = stX, room->y = stY;
	room->setCenter(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(room, 0);

	roomQueue.push(room);
	cntRoom++;

	while (!roomQueue.empty()) 
	{
		BattleRoom* curRoom = roomQueue.front();
		roomQueue.pop();
		// getNextRoomDirection
		getNextRoom(curRoom->x, curRoom->y, curRoom, roomQueue);
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
	if (cntRoom <= 2 && cntDirChosen == 0)
		cntDirChosen=1;
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