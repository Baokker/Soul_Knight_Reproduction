/*
* @file   Boxroom.h
* @author wlf
* @date   2021/5/14
* @modified name date
*/


#include"Statue.h"

bool Statue::init()
{
	srand(time(0));
	bufftype = rand() % 3;
	//auto visibleSize = Director::getInstance()->getVisibleSize();

	return true;
}

bool Statue::isstatuewithknight(Knight* knight)
{
	return this->getBoundingBox().intersectsRect(knight->getBoundingBox());
}

