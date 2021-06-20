/*
* @file   Explosion.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#include"Explosion.h"
#include"Scene/SetScene.h"

bool Explosion::init()
{
    SetDuration(0.1);

    Setdamage(2);

    //audio effect
    auto setscene = SetScene::create();
    this->present = setscene->present;
    this->Soundeffect = setscene->Soundeffect;
    if (Soundeffect)
    {
        auto audiodeductHP = AudioEngine::play2d("music\\Explosion.mp3", false);
        AudioEngine::setVolume(audiodeductHP, present / 100.0f);
    }

    if (!Debuff::init())
        return false;

    addChild(FloatText::create("explosion!!be careful!!", Vec2(getContentSize().width / 2, getContentSize().height + 5), GetDuration(), 15));
    return true;
}

bool Explosion::BindwithKnight(Knight* knight)
{
    Debuff::BindwithKnight(knight);

    auto explode = [this, knight](float)
    {
        if (getBoundingBox().containsPoint(knight->getPosition()))
        {
            knight->deductHP(Getdamage());
            removeFromParentAndCleanup(true);
        }
    };

    schedule(explode, FPS, "explode");
    return true;
}

Explosion* Explosion::createAndBindwithKnight(Knight* knight)
{
    Explosion* pRet = new(std::nothrow) Explosion();
    if (pRet && pRet->initWithFile("Item\\Explosion.png") && pRet->init() && pRet->BindwithKnight(knight))
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
