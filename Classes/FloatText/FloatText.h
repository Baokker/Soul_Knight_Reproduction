/*
* @file   FloatText.h
* @author fbc
* @date   2021/6/14
* @modified name date
*/

#ifndef __FLOATTEXT_H__
#define __FLOATTEXT_H__

#include"cocos2d.h"

using namespace std;
USING_NS_CC;

class FloatText :public Label
{
public:
	bool init(Vec2 position,float time);
	static FloatText* create(string text, Vec2 position, float duration, int fontsize = 20);

	int distance = 15;
	float duration = 0.5;
};
#endif