#ifndef _CONST_H_
#define _CONST_H_
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


//fbc
constexpr int FRAME_SIZE_X = 1280;
constexpr int FRAME_SIZE_Y = 720;

constexpr int WeaponAndHeroDistance = 40;

constexpr float FPS = 1 / 60;

constexpr int isGun = -1;
constexpr int isMelee = -2;//½üÕ½ in chinese
constexpr int Pistol = 1;
//string PistolBulletPath = "Bullet\\PistolBullet.png";

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


#endif  // !_CONST_H_
