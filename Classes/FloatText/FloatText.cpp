/*
* @file   FloatText.cpp
* @author fbc
* @date   2021/6/14
* @modified name date
*/

#include "FloatText.h"
#include"Actor/Character/Knight.h"

using namespace std;

bool FloatText::init(Vec2 position,float time)
{
    setPosition(position.x, position.y + distance);
    //Director::getInstance()->getRunningScene()->addChild(this);
    auto disappear = [this](float) {
        removeFromParentAndCleanup(true);
    };

    setGlobalZOrder(10);
    scheduleOnce(disappear, time, "disappear");
    return true;
}

FloatText* FloatText::create(string text, Vec2 position, float duration, int fontsize)//don't need to set default number
{
    auto ret = new (std::nothrow) FloatText();

    if (ret && ret->initWithTTF(text, "fonts\\Facon.ttf", fontsize) && ret->init(position, duration))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}
