/*
* @file   Boxroom.h
* @author wlf
* @date   2021/5/14
* @modified name date
*/


#include"Statue.h"

bool Statue::init()
{
	srand(time(0));
	bufftype = rand() % 3;
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	

	return true;
}

bool Statue::isstatuewithknight(Knight* knight)
{
	if (this->getBoundingBox().intersectsRect(knight->getBoundingBox()) && isopened == false)
	{
		if (getChildByName("reminder1") == nullptr && Lab_logo == false)
		{
			statueLab[bufftype] = FloatText::create("Pay " + Value(this->money_spend[bufftype]).asString() + " money to increase MaxHP by 1", Vec2(getContentSize().width / 2, getContentSize().height + 10), 2, 40);
			addChild(statueLab[bufftype], 1, "reminder1");
			Lab_logo = true;
		}
		if (this->isopened == false && knight->j_press == true&& knight->GetMoney() >= money_spend[bufftype])
		{
			knight->SetMoney(knight->GetMoney() - money_spend[bufftype]);
			knight->Getbuff(this->bufftype);
			this->isopened = true;
		}
		else if (knight->j_press == true && knight->GetMoney() < money_spend[bufftype])
		{
			if (getChildByName("reminder2") == nullptr)
			{
				if (Lab_logo2)
				{
					statueLab[bufftype]->setVisible(false);
					Lab_logo2 = false;
				}
				statueLab_buy = FloatText::create("You are so poor, so pitiful.", Vec2(getContentSize().width / 2, getContentSize().height + 10), 1, 40);
				this->addChild(statueLab_buy, 1, "reminder2");
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

