#pragma once

#ifndef __BATTLE_ROOM_H__
#define __BATTLE_ROOM_H__

#include "cocos2d.h"

class BattleRoom : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    void createRoom(int, int);
    void createHall(int, int,int);
    void createFloor(int, int, int);
    void createWall(int, int, int);
    void createDoor(int, int, int);
    bool scene[5][5];
    void createBattleScene(bool* , int );
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* events);

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleRoom);
private:
    cocos2d::Sprite* _player;

};

#endif // __BATTLE_ROOM_H__
