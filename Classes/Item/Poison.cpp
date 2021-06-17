/*
* @file   Poison.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#include"Poison.h"

bool Poison::init()
{
	auto disappear = [this](float)
	{
		removeFromParentAndCleanup(true);
	};

    int time = 3;

	scheduleOnce(disappear, time, "disappear");

    addChild(FloatText::create("in this area you will deduct 1 HP per second", Vec2(getContentSize().width/2, getContentSize().height + 5), time, 15));
	return true;
}

int Poison::Getdamage()
{
	return damage;
}

void Poison::Setdamage(int num)
{
	damage = num;
}

bool Poison::BindwithKnight(Enemy* enemy, Knight* knight)
{
    setPosition(enemy->getPosition());

    auto checkknight = [this, knight](float)
    {
        if (getBoundingBox().intersectsRect(knight->getBoundingBox()) && Curtime == 0)
            knight->deductHP(Getdamage());
        Curtime = Curtime == 59 ? 0 : Curtime + 1;
    };

    schedule(checkknight, FPS, "checkknight");
    return true;
}

Poison* Poison::createAndBindwithKnight(Enemy* enemy, Knight* knight)
{
    Poison* pRet = new(std::nothrow) Poison(); 
    if (pRet && pRet->initWithFile("Item\\Poison.png") && pRet->init() && pRet->BindwithKnight(enemy, knight))
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
