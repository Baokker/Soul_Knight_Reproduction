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

void BattleScene::SetMoneyLabel()
{
	MoneyLabel = Label::createWithTTF("gold : 0", "fonts/Facon.ttf", 30);
	MoneyLabel->setPosition(870, 630);
	this->addChild(MoneyLabel, 100);
	MoneyLabel->setGlobalZOrder(10);
}

void BattleScene::SetCheckpoint()
{
	CheckpointLabel = Label::createWithTTF("Checkpoint  : 1 - 1", "fonts/Facon.ttf", 30);
	CheckpointLabel->setPosition(870, 670);
	this->addChild(CheckpointLabel, 100);
	CheckpointLabel->setGlobalZOrder(10);
}

void BattleScene::UpdateMoneyLabel()
{
	MoneyLabel->setString("Money : " + Value(this->knight->GetMoney()).asString());
}

void BattleScene::UpdateLoadingBar()
{
	//Status update
	BloodLoadingBar->setPercent(this->knight->GetHP() * 100 / knight->MaxHP);
	ArmorLoadingBar->setPercent(this->knight->GetShield() * 100 / knight->MaxShield);
	MPLoadingBar->setPercent(float(this->knight->GetMP()) / float(knight->MaxMP) * 100);

	HPLabel->setString(Value(this->knight->HP).asString() + "/" + Value(this->knight->MaxHP).asString());
	armorLabel->setString(Value(this->knight->Shield).asString() + "/" + Value(this->knight->MaxShield).asString());
	MPLabel->setString(Value(this->knight->MP).asString() + "/" + Value(this->knight->MaxMP).asString());
}

void BattleScene::updateAttack()
{
	if (knight->isMeleeing)
	{
		if (knight->CheckifMPenough())
		{
			knight->SetMP(knight->GetMP() - knight->Getweapon()->GetconsumeMP());
			for (auto enemy : curRoom->vecEnemy)
			{
				if (knight->AttackMelee().intersectsRect(enemy->getBoundingBox()))
				{
					enemy->SetHP(enemy->GetHP() - dynamic_cast<Melee*>(knight->weapon[knight->Holding])->Getdamage());
				}
				knight->isMeleeing = false;
			}
		}
	}
	else if (knight->isShooting)
	{
		if (knight->CheckifMPenough())
		{
			auto bullet = Bullet::create();
			addChild(bullet);
			knight->SetMP(knight->GetMP() - knight->Getweapon()->GetconsumeMP());
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
					bullet->setRotation(-atan2(my, mx) * 180 / 3.14);
				}
			}
			vecBullet.pushBack(bullet);
			bullet->setGlobalZOrder(6);
			bullet->setOwner(KNIGHT);
			knight->AttackwithGun(bullet);
			knight->isShooting = false;
		}
		else
		{
			for (auto enemy : curRoom->vecEnemy)
			{
				if (knight->AttackMeleeWithGun().intersectsRect(enemy->getBoundingBox()))
				{
					enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->GetMeleeDamage());
				}

				knight->isMeleeing = false;
			}
		}
	}

	for (auto enemy : curRoom->vecEnemy)
	{
		//AI
		if (!enemy->GetisAlive()) {}
		else
		{
			enemy->AImonitor(knight);
			if (enemy->CheckifDie())
			{
				knight->AddMoney(2);
				knight->AddMP(5);
				if (rand() % 3 == 0)
				{
					switch (rand() % 4)
					{
						case 0:
							enemy->MakeExplosion(knight);
							break;
						case 1:
							enemy->MakePoison(knight);
							break;
						case 2:
							enemy->MakeConfusion(knight);
						case 3:
							enemy->MakeSlowdown(knight);
						default:
							break;
					}
				}
				enemy->Die();
			}

			else if (enemy->GetisInBattle() && rand() % 10 < 1)//attack!
			//if it is a meleeenemy just change the code related to attack 
			{
				if (enemy->GetType() == GUN)
				{
					auto EnemyBullet = Bullet::create();
					this->addChild(EnemyBullet);
					int distance = sqrt(pow(knight->getPosition().x - enemy->getPosition().x, 2) + pow(knight->getPosition().y - enemy->getPosition().y, 2));
					int mx = knight->getPosition().x - enemy->getPosition().x; 
					int my = knight->getPosition().y - enemy->getPosition().y;
					EnemyBullet->MoveSpeedX = EnemyBullet->MoveSpeed * mx / distance;
					EnemyBullet->MoveSpeedY = EnemyBullet->MoveSpeed * my / distance;
					EnemyBullet->setOwner(ENEMY);

					EnemyBullet->setRotation(-atan2(my, mx)*180/3.14);

					vecBullet.pushBack(EnemyBullet);
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

	if (curRoom->boss != nullptr)
	{
		if (!curRoom->boss->GetisAlive()) {}
		else
		{
			curRoom->boss->AImonitor(knight);
			if (curRoom->boss->CheckifDie())
			{
				knight->AddMoney(25);
				curRoom->boss->Die();
			}
			else if (curRoom->boss->GetisInBattle())//attack!
			{
				switch (rand() % 7)
				{
					case 0:
						if (curRoom->boss->AttackMelee().intersectsRect(knight->getBoundingBox()))//problem
						{
							knight->deductHP(curRoom->boss->GetWeapon()->Getdamage());
						}
						break;
					case 1:
						curRoom->boss->Teleport(knight);
						break;
					case 2:
						curRoom->boss->MakeConfusion(knight);
						curRoom->boss->GetWeapon()->SetCurtime(1);
						break;
					case 3:
						curRoom->boss->MakeExplosion(knight);
						curRoom->boss->GetWeapon()->SetCurtime(1);
						break;
					case 4:
						curRoom->boss->MakePoison(knight);
						curRoom->boss->GetWeapon()->SetCurtime(1);
						break;
					case 5:
						for (int i = 0; i < 5; i++)
						{
							auto EnemyBullet = Bullet::create();
							this->addChild(EnemyBullet);
							int distance = sqrt(pow(knight->getPosition().x - curRoom->boss->getPosition().x, 2) + pow(knight->getPosition().y - curRoom->boss->getPosition().y, 2));
							int mx = knight->getPosition().x - curRoom->boss->getPosition().x;
							int my = knight->getPosition().y - curRoom->boss->getPosition().y;
							EnemyBullet->MoveSpeedX = EnemyBullet->MoveSpeed * mx / distance;
							EnemyBullet->SetMoveSpeedX(EnemyBullet->GetMoveSpeedX() + rand() % 5 - 2);
							EnemyBullet->MoveSpeedY = EnemyBullet->MoveSpeed * my / distance;
							EnemyBullet->SetMoveSpeedY(EnemyBullet->GetMoveSpeedY() + rand() % 5 - 2);

							EnemyBullet->setOwner(ENEMY);

							EnemyBullet->setRotation(-atan2(EnemyBullet->GetMoveSpeedY(), EnemyBullet->GetMoveSpeedX()) * 180 / 3.14);

							vecBullet.pushBack(EnemyBullet);
							EnemyBullet->setGlobalZOrder(6);
							curRoom->boss->AttackwithGun(EnemyBullet);

						}
						break;
					case 6:
						curRoom->boss->MakeSlowdown(knight);
						break;
				}

			}
		}
	}
}

void BattleScene::updateBullet(Bullet* bullet, Enemy* enemy)
{
	if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && !bullet->GetisUseless() && bullet->getOwner() == KNIGHT)
	{
		enemy->SetHP(enemy->GetHP() - bullet->Getdamage());
		bullet->setVisible(false);
		bullet->stopAllActions();
		bullet->MoveSpeedX = bullet->MoveSpeedY = 0;
		bullet->removeFromParentAndCleanup(true);
		bullet->SetisUseless(true);
	}
	if (bullet->getBoundingBox().intersectsRect(knight->getBoundingBox()) && !bullet->GetisUseless() && bullet->getOwner() == ENEMY)
	{
		knight->deductHP(bullet->Getdamage());
		bullet->setVisible(false);
		bullet->stopAllActions();
		bullet->MoveSpeedX = bullet->MoveSpeedY = 0;
		bullet->removeFromParentAndCleanup(true);
		bullet->SetisUseless(true);
	}
}

void BattleScene::Updatecheckpoint()
{
	CheckpointLabel->setString("Checkpoint: " + Value(level / 5 + 1).asString() + " - " + Value(level % 5 + 1).asString());
}

string BattleScene::getSceneType()
{
	return sceneType;
}

BattleScene* BattleScene::createwithOriginalKnightAndLevel(Knight* originalknight, int prelevel)
{
	BattleScene* pRet = new(std::nothrow) BattleScene();
		if (pRet && pRet->initwithOriginalKnightAndLevel(originalknight,prelevel)) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
}

bool BattleScene::init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	srand(time(NULL));
	sceneType = SceneType.at(rand() % SceneType.size());

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

	SetMoneyLabel();
	SetLoadingBar();
	SetMenu();
	SetCheckpoint();

	this->scheduleUpdate();
	return true;
}

void BattleScene::update(float delta) 
{
	//check if die
	if (knight->CheckifDie())
	{
		auto safescene = SafeScene::create();
		safescene->knight->SetMoney(0);
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
	}
	updateAll();
	updateAttack();

	if (curRoom->box != nullptr)
	{
		curRoom->box->isboxwithknight(knight);
		curRoom->box->ispropswithknight(knight);
	}
	if (curRoom->store != nullptr)
	{
		curRoom->store->checkstore(510, 790, knight);
		curRoom->store->isstorewithknight(knight);
		curRoom->store->isgoodswithknight(knight);
	}
	if (curRoom->statue !=nullptr)
		curRoom->statue->isstatuewithknight(knight);

	Updatecheckpoint();
	UpdateMoneyLabel();
	UpdateLoadingBar();
}

bool BattleScene::initwithOriginalKnightAndLevel(Knight* originalknight,int prelevel)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	srand(time(NULL));
	sceneType = SceneType.at(rand() % SceneType.size());

	originalknight->retain();
	originalknight->weapon[0]->retain();
	originalknight->weapon[1]->retain();

	originalknight->removeFromParent();
	originalknight->weapon[0]->removeFromParent();
	originalknight->weapon[1]->removeFromParent();

	knight = originalknight;
	
	knight->resumeShield();
	knight->SetChangeDirection();
	knight->weapon[0]->initCheckCD();
	knight->weapon[1]->initCheckCD();

	this->level = prelevel + 1;

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

	SetMoneyLabel();
	SetLoadingBar();
	SetMenu();
	SetCheckpoint();

	this->scheduleUpdate();
	return true;

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
			if (curRoom != nullptr && !curRoom->visited)
			{
				curRoom->visited = true;
				if (curRoom->roomType == NORMAL)
				{
					curRoom->closeDoor();
					curRoom->addEnemy();
				}
				else if (curRoom->roomType == BOSS)
				{
					curRoom->closeDoor();
				}
			}
			if (curRoom != nullptr && curRoom->roomType == NORMAL)
			{
				if (curRoom->allKilled())
					curRoom->openDoor();
			}
			if (curRoom != nullptr && curRoom->roomType == BOSS && curRoom->allKilled())
			{
				if (curRoom->endPortal == nullptr)
				{
					Sprite* portal = Sprite::create("Map//portal.png");
					curRoom->endPortal = portal;
					portal->setPosition(curRoom->centerX, curRoom->centerY);
					curRoom->addChild(portal);
					portal->setGlobalZOrder(5);
				}
			}
		}
	}
	if (!vecBullet.empty())
		for (auto bullet : vecBullet)
		{
			for (auto enemy : curRoom->vecEnemy)
			{
				if (vecBullet.empty())
					continue;
				updateBullet(bullet, enemy);

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
					bullet->SetisUseless(true);
				}
			}
			if (vecBullet.empty())
				continue;
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
		if (!bullet->GetisUseless())
			bullet->setPosition(bullet->getPosition().x - ispeedX, bullet->getPosition().y - ispeedY);
	}
	if (curRoom->roomType == END && knight->getBoundingBox().intersectsRect(curRoom->endPortal->getBoundingBox())
		|| (curRoom->roomType == BOSS && curRoom->endPortal != nullptr) && knight->getBoundingBox().intersectsRect(curRoom->endPortal->getBoundingBox()))
	{
		if (knight->isGoingBattle)
		{
			auto battlescene = BattleScene::createwithOriginalKnightAndLevel(knight,level);
			Director::getInstance()->replaceScene(battlescene);
			return;
		}
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
			{
				if ((level + 1 ) % 5 == 0)//notice
					Room->roomType = BOSS;
				else
					Room->roomType = END;
			}
			else
			{
				int special;
				special = rand() % 2;
				if (special && !Type.empty())
				{
					special = rand() % Type.size();
					Room->roomType = Type.at(special);
					Type.erase(Type.begin() + special);
				}
				else
					Room->roomType = NORMAL;
			}
			Room->knight = knight;
			Room->sceneType = getSceneType();
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
	if (cntRoom <= 5 && cntDirChosen == 0)
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
		hall->sceneType = sceneType;
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