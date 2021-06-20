/*
* @file   Slowdown.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#include"Slowdown.h"

bool Slowdown::init()
{
    SetDuration(5);

    setScale(3);

    if (!Debuff::init())
        return false;

    addChild(FloatText::create("in this area you will move slowly", Vec2(getContentSize().width / 2, getContentSize().height + 5), GetDuration(), 15));
    return true;
}

bool Slowdown::BindwithKnight(Knight* knight)
{
    Debuff::BindwithKnight(knight);

    auto changeknightspeed = [this, knight](float)
    {
        if (getBoundingBox().containsPoint(knight->getPosition()))
        {
            knight->SetMoveSpeed(5);
        }
        else
        {
            knight->SetMoveSpeed(10);
        }
    };

    schedule(changeknightspeed, FPS, "changeknightspeed");

    auto recoverknightspeed = [this, knight](float)
    {
        unschedule("changeknightspeed");
        knight->SetMoveSpeed(10);
    };

    scheduleOnce(recoverknightspeed, GetDuration() - 0.1, "recoverknightspeed");
    return true;
}

Slowdown* Slowdown::createAndBindwithKnight(Knight* knight)
{
    Slowdown* pRet = new(std::nothrow) Slowdown();
    if (pRet && pRet->initWithFile("Item\\Slowdown.png") && pRet->init() && pRet->BindwithKnight(knight))
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
