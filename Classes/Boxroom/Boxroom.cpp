/*
* @file   Boxroom.h
* @author wlf
* @date   2021/5/14
* @modified name date
*/


#include"Boxroom.h"


USING_NS_CC;

bool Box::init()
{
	srand(time(0));
	proptype = rand() % 2;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	props[0] = Sprite::create("Scene/1.png");
	props[0]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[1] = Sprite::create("Scene//add_MP.png");
	props[1]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	props[2] = Sprite::create("Scene//fire_gun.png");
	props[2]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));



	return true;
}

bool Box::isboxwithknight(Knight* knight)
{
	return this->getBoundingBox().intersectsRect(knight->getBoundingBox());
}

bool Box::ispropswithknight(Knight* knight)
{
	return props[proptype]->getBoundingBox().intersectsRect(knight->getBoundingBox());
}


