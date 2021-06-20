/*
* @file   Box.h
* @author wlf
* @date   2021/5/14
* @modified name date
*/

#include"Box.h"

bool Box::init()
{
	srand(time(0));
	proptype = rand() % 4;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	props[HP_ADD] = Sprite::create("Scene//1.png");
	props[HP_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[MP_ADD] = Sprite::create("Scene//add_MP.png");
	props[MP_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[MONEY_ADD] = Sprite::create("Scene//add_gold.png");
	props[MONEY_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	switch (rand() % 6)
	{
		case 0:
			boxweapon = FishGun::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 1:
			boxweapon = SubmachineGun::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 2:
			boxweapon = Spear::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 3:
			boxweapon = ShotGun::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 4:
			boxweapon = LaserGun::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;
		case 5:
			boxweapon = MagicGun::create();
			boxweapon->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			break;

		default:
			break;
	}

	return true;
}

bool Box::isboxwithknight(Knight* knight)
{
	if (this->getBoundingBox().intersectsRect(knight->getBoundingBox()))
	{
		if (getChildByName("reminder") == nullptr)
		{
			addChild(FloatText::create("Press J to open the Box", Vec2(getContentSize().width / 2, getContentSize().height + 10), 2), 1, "reminder");
		}
		if (isopened == false && knight->j_press == true)
		{
			this->setVisible(false);
			isopened = true;
			if (proptype <= 2)
				props[proptype]->setVisible(true);
			else
				boxweapon->setVisible(true);
			knight->j_press = false;
		}

		return true;
	}
	return false;
}

bool Box::ispropswithknight(Knight* knight)
{
	Rect boundingbox;
	if (proptype <= 2)
		boundingbox = props[proptype]->getBoundingBox();
	else
		boundingbox = boxweapon->getBoundingBox();

	if (boundingbox.intersectsRect(knight->getBoundingBox()))
	{
		if (this->isopened == true && knight->j_press == true)
		{
			if (this->proptype == 0)
			{
				if (props[0]->isVisible())
				{
					knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
					this->props[0]->setVisible(false);
				}
			}
			else if (this->proptype == 1)
			{
				if (props[1]->isVisible())
				{
					knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
					this->props[1]->setVisible(false);
				}
			}
			else if (this->proptype == 2)
			{
				if (props[2]->isVisible())
				{
					knight->SetMoney(knight->GetMoney() + 5);
					this->props[2]->setVisible(false);
				}
			}
			else if (this->proptype == 3)
			{
				if (getChildByName("pick_up_weapon_reminder2") == nullptr)
					addChild(FloatText::create("Click J to pick it up", Vec2(boxweapon->getPositionX(), boxweapon->getPositionY() + 20), 3), 99, "pick_up_weapon_reminder2");
				if (knight->PickupWeapon(boxweapon))
				{
					swap(knight->weapon[knight->Holding], boxweapon);
					knight->weapon[knight->Holding]->retain();
					knight->weapon[knight->Holding]->removeFromParent();
					knight->weapon[knight->Holding]->initCheckCD();
					Director::getInstance()->getRunningScene()->addChild(knight->weapon[knight->Holding]);

					boxweapon->retain();
					boxweapon->removeFromParent();
					boxweapon->initCheckCD();
					getBindRoom()->addChild(boxweapon);
				}
			}
		}
	}
	return false;
}

BattleRoom* Box::getBindRoom()
{
	return bindRoom;
}

void Box::setBindRoom(BattleRoom* battleroom)
{
	bindRoom = battleroom;
}


