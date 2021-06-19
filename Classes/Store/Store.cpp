#include"Store.h"

bool Store::init()
{
	srand(time(0));
	goodstype = rand() % 3;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	goods[HP_ADD] = Sprite::create("Scene//1.png");
	goods[HP_ADD]->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 150));
	goods[MP_ADD] = Sprite::create("Scene//add_MP.png");
	goods[MP_ADD]->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 150));
	goods[WEAPON - 1] = Sprite::create("Scene//fire_gun.png");
	goods[WEAPON - 1]->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 + 150));

	return true;
}

bool Store::isstorewithknight(Knight* knight)
{
	
	if (this->getBoundingBox().intersectsRect(knight->getBoundingBox()) && this->isopened == false)
	{
		if (getChildByName("reminder1") == nullptr && Lab_logo == false)
		{
			storeLab = FloatText::create("need 15 money", Vec2(getContentSize().width / 2, getContentSize().height + 10), 2, 40);
			this->addChild(storeLab, 1, "reminder1");
			Lab_logo = true;
		}
		if (this->isopened == false && knight->j_press == true && knight->GetMoney() >= 15)
		{
			knight->SetMoney(knight->GetMoney() - 15);
			this->setVisible(false);
			this->isopened = true;
			this->goods[this->goodstype]->setVisible(true);
			knight->j_press = false;
		}
		else if (knight->j_press == true && knight->GetMoney() < 15)
		{
			if (getChildByName("reminder2") == nullptr)
			{
				if (Lab_logo2)
				{
					storeLab->setVisible(false);
					Lab_logo2 = false;
				}
				storeLab_buy = FloatText::create("You are so poor, so pitiful.", Vec2(getContentSize().width / 2, getContentSize().height + 10), 1, 40);
				this->addChild(storeLab_buy, 1, "reminder2");
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
	if (goods[goodstype]->getBoundingBox().intersectsRect(knight->getBoundingBox()) && isopened == true && knight->j_press == true)
	{
		if (this->goodstype == 0)
		{
			knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
			this->goods[0]->setVisible(false);
		}
		else if (this->goodstype == 1)
		{
			knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
			this->goods[1]->setVisible(false);
		}
		else if (this->goodstype == 2)
		{
			knight->SetMoney(knight->GetMoney() + 5);
			this->goods[2]->setVisible(false);
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