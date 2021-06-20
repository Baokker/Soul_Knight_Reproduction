/*
* @file   Poison.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#include"Poison.h"

bool Poison::init()
{
    Setdamage(1);

    SetDuration(3);

    if (!Debuff::init())
        return false;

    addChild(FloatText::create("in this area you will deduct 1 HP per second", Vec2(getContentSize().width/2, getContentSize().height + 5), GetDuration(), 15));
	return true;
}

bool Poison::BindwithKnight(Knight* knight)
{
    Debuff::BindwithKnight(knight);

    auto checkknight = [this, knight](float)
    {
        if (getBoundingBox().containsPoint(knight->getPosition()) && GetCurtime() == 0)
            knight->deductHP(Getdamage());
        SetCurtime(GetCurtime() == 59 ? 0 : GetCurtime() + 1);
    };

    schedule(checkknight, FPS, "checkknight");
    return true;
}

Poison* Poison::createAndBindwithKnight(Knight* knight)
{
    Poison* pRet = new(std::nothrow) Poison(); 
    if (pRet && pRet->initWithFile("Item\\Poison.png") && pRet->init() && pRet->BindwithKnight(knight))
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
