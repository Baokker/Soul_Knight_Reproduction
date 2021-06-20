#ifndef _CONST_H_
#define _CONST_H_

#include<string>
#include<map>
#include "cocos2d.h"

//hyq
constexpr int CNTDIR = 4;

enum Direction { RIGHT, UP, LEFT, DOWN };
constexpr int DIRX[CNTDIR] = { 1, 0, -1, 0 };  // right up left down
constexpr int DIRY[CNTDIR] = { 0, 1, 0, -1 };  // right up left down
constexpr int FLOORWIDTH = 40;
constexpr int FLOORHEIGHT = 40;
constexpr int WALLWIDTH = 40;
constexpr int WALLHEIGHT = 60;
constexpr int SIZEHALL = 7;
constexpr int CENTERDIS = 39 * 40;
constexpr int ROOMDISTANCE = 39;
constexpr int SIZEROOM = 19;
constexpr int KNIGHTLAYER = 6;
constexpr int BEGIN = 1;
constexpr int END = 2;
constexpr int BOX = 3;
constexpr int STATUE = 4;
constexpr int NORMAL = 0;

constexpr int BOSS = 5;
constexpr int KNIGHT = 0;
constexpr int ENEMY = 1;

//fbc
using std::string;
using std::vector;

const vector<string> SceneType{ "Alien" ,"Forest","Ghost","Ice","Knight","Lava","Skeleton" };

constexpr int WeaponAndHeroDistance = 50;

constexpr float FPS = 1 / 60;

constexpr int isGun = -1;
constexpr int isMelee = -2;//½üÕ½ in chinese
constexpr int Pistol = 1;

constexpr int MELEE_WIDTH = 120;
constexpr int MELEE_HEIGHT = 120;

constexpr int GUN_ENEMY_ATTACK_RANGE = 400;
constexpr int MELEE_ENEMY_ATTACK_RANGE = 250;

constexpr int MELEE = 0;
constexpr int GUN = 1;

//two template function
#define CREATE_FUNC_WITH_FILE(__TYPE__) \
static __TYPE__* create(const char* filename) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithFile(filename) && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define CREATE_FUNC_WITH_DEFAULT_FILE(__TYPE__,__FILE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithFile(__FILE__) && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}


//wlf
constexpr int  HP_ADD = 0;
constexpr int MP_ADD = 1;
constexpr int MONEY_ADD = 2;
constexpr int SHIELD_ADD = 2;
constexpr int WEAPON = 3;

#endif  // !_CONST_H_
