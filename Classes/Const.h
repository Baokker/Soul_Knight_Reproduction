#ifndef _CONST_H_
#define _CONST_H_
#include "cocos2d.h"

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

#endif  // !_CONST_H_
