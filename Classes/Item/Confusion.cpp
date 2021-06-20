/*
* @file   Confusion.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#include"Confusion.h"

bool Confusion::init()
{
    SetDuration(5);

    setScale(3);

    if (!Debuff::init())
        return false;

    addChild(FloatText::create("in this area you will move in opposed direction", Vec2(getContentSize().width / 2, getContentSize().height + 5), GetDuration(), 15));
    return true;
}

bool Confusion::BindwithKnight(Knight* knight)
{
    Debuff::BindwithKnight(knight);

    auto changeknightspeed = [this, knight](float)
    {
        if (getBoundingBox().containsPoint(knight->getPosition()))
        {
            knight->SetisInConfusion(true);
        }
        else
        {
            knight->SetisInConfusion(false);
        }
    };

    schedule(changeknightspeed, FPS, "changeknightspeed");

    auto recoverknightspeed = [this, knight](float)
    {
        unschedule("changeknightspeed");
        knight->SetisInConfusion(false);
    };

    scheduleOnce(recoverknightspeed, GetDuration() - 0.1, "recoverknightspeed");
    return true;
}

Confusion* Confusion::createAndBindwithKnight(Knight* knight)
{
    Confusion* pRet = new(std::nothrow) Confusion();
    if (pRet && pRet->initWithFile("Item\\Confusion.png") && pRet->init() && pRet->BindwithKnight(knight))
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
