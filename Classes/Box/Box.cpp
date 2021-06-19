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
	proptype = rand() % 3;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	props[HP_ADD] = Sprite::create("Scene//1.png");
	props[HP_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[MP_ADD] = Sprite::create("Scene//add_MP.png");
	props[MP_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[MONEY_ADD] = Sprite::create("Scene//add_gold.png");
	props[MONEY_ADD]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[WEAPON] = Sprite::create("Scene//fire_gun.png");
	props[WEAPON]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


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
			props[proptype]->setVisible(true);
			knight->j_press = false;
		}

		return true;
	}
	return false;
}

bool Box::ispropswithknight(Knight* knight)
{
	if (props[proptype]->getBoundingBox().intersectsRect(knight->getBoundingBox()))
	{
		if (this->isopened == true && knight->j_press == true)
		{
			if (this->proptype == 0)
			{
				knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
				this->props[0]->setVisible(false);
			}


			else if (this->proptype == 1)
			{
				knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
				this->props[1]->setVisible(false);
			}
			else if (this->proptype == 2)
			{
				knight->SetMoney(knight->GetMoney() + 5);
				this->props[2]->setVisible(false);
			}
		}
	}
	return false;
}


