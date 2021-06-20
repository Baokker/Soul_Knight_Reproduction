#include"Store.h"

bool Store::init()
{
	//srand(time(0));
	goodstype = rand() % 3;//notice
	auto visibleSize = Director::getInstance()->getVisibleSize();

	setScale(0.5);

	cost = rand() % 10 + 10;

	goods[HP_ADD] = Sprite::create("Scene//1.png");
	goods[HP_ADD]->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 150));
	goods[MP_ADD] = Sprite::create("Scene//add_MP.png");
	goods[MP_ADD]->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 150));

	switch (rand() % 6)
	{
		case 0:
			storeweapon = FishGun::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 1:
			storeweapon = SubmachineGun::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 2:
			storeweapon = Spear::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 3:
			storeweapon = ShotGun::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 4:
			storeweapon = LaserGun::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 5:
			storeweapon = MagicGun::create();
			storeweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;

		default:
			break;
	}

	return true;
}

bool Store::isstorewithknight(Knight* knight)
{
	
	if (this->getBoundingBox().intersectsRect(knight->getBoundingBox()) && this->isopened == false)
	{
		if (getChildByName("reminder1") == nullptr && Lab_logo == false)
		{
			storeLab = FloatText::create("need cost "+std::to_string(cost)+" money", Vec2(getContentSize().width / 2, getContentSize().height + 10), 2, 40);
			this->addChild(storeLab, 99, "reminder1");
			Lab_logo = true;
		}
		if (this->isopened == false && knight->j_press == true && knight->GetMoney() >= cost)
		{
			knight->SetMoney(knight->GetMoney() - cost);
			this->setVisible(false);
			isopened = true;
			if (goodstype <= 1)
				goods[goodstype]->setVisible(true);
			else
				storeweapon->setVisible(true);
			knight->j_press = false;
		}
		else if (knight->j_press == true && knight->GetMoney() < cost)
		{
			if (getChildByName("reminder2") == nullptr)
			{
				if (Lab_logo2)
				{
					storeLab->setVisible(false);
					Lab_logo2 = false;
				}
				storeLab_buy = FloatText::create("You are so poor, so pitiful.", Vec2(getContentSize().width / 2, getContentSize().height + 10), 1, 40);
				this->addChild(storeLab_buy, 99, "reminder2");
			}
		}
		return true;
	}
	else
	{
		Lab_logo = false;
		Lab_logo2 = true;
	}
	return false;
}

bool Store::isgoodswithknight(Knight* knight)
{
	Rect boundingbox;
	if (goodstype <= 1)
		boundingbox = goods[goodstype]->getBoundingBox();
	else
		boundingbox = storeweapon->getBoundingBox();

	if (boundingbox.intersectsRect(knight->getBoundingBox()) && isopened == true && knight->j_press == true)
	{
		if (this->goodstype == 0)
		{
			if (goods[0]->isVisible())
			{
				knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
				this->goods[0]->setVisible(false);
			}
		}
		else if (this->goodstype == 1)
		{
			if (goods[1]->isVisible())
			{
				knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
				this->goods[1]->setVisible(false);
			}
		}
		else if (this->goodstype == 2)//weapon
		{
			if (getChildByName("pick_up_weapon_reminder2") == nullptr)
				addChild(FloatText::create("Click J to pick it up", Vec2(storeweapon->getPositionX(), storeweapon->getPositionY() + 20), 3), 99, "pick_up_weapon_reminder2");
			if (knight->PickupWeapon(storeweapon))
			{
				swap(knight->weapon[knight->Holding], storeweapon);
				knight->weapon[knight->Holding]->retain();
				knight->weapon[knight->Holding]->removeFromParent();
				knight->weapon[knight->Holding]->initCheckCD();
				Director::getInstance()->getRunningScene()->addChild(knight->weapon[knight->Holding]);

				storeweapon->retain();
				storeweapon->removeFromParent();
				storeweapon->initCheckCD();
				getBindRoom()->addChild(storeweapon);
			}
		}
	}


	return false;
}

void Store::checkstore(float centerX, float centerY, Knight* knight)
{
	//if (knight->getPositionX() <= x + 30 && knight->getPositionX() >= x - 30 && )
	//{
	//	if (knight->getPositionY() < y + 10 && knight->getPositionY() > y - 10)
	//	{
	//		knight->SetMoveSpeedX(0);
	//	}
	//}

	if (knight->getPositionX() <= centerX + 90 && knight->getPositionX() >= centerX - 90 && knight->getPositionY() <= centerY + 90 && knight->getPositionY() >= centerY - 90)
	{
		if (centerY - 40 < knight->getPositionY() && knight->getPositionY() < centerY + 70) 
		{
			if (knight->getPositionX() < centerX && knight->getPositionX() >= centerX - 60 && knight->GetMoveSpeedX() > 0)
				knight->SetMoveSpeedX(.0f);
			else if (knight->getPositionX() > centerX && knight->getPositionX() <= centerX + 60 && knight->GetMoveSpeedX() < 0)
				knight->SetMoveSpeedX(.0f);
		} //no else
		if (centerX - 50 < knight->getPositionX() && knight->getPositionX() < centerX + 50) 
		{
			if (knight->getPositionY() < centerY && knight->getPositionY() >= centerY - 50 && knight->GetMoveSpeedY() > 0)
				knight->SetMoveSpeedY(.0f);
			else if (knight->getPositionY() > centerY && knight->getPositionY() <= centerY + 80 && knight->GetMoveSpeedY() < 0)
				knight->SetMoveSpeedY(.0f);
		}
	}
}

BattleRoom* Store::getBindRoom()
{
	return bindRoom;
}

void Store::setBindRoom(BattleRoom* battleroom)
{
	bindRoom = battleroom;
}
