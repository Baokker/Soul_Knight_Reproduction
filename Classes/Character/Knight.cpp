/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include<cocos2d.h>
#include"Knight.h"


USING_NS_CC;

static void problemLoading(const char* filename)
{
	log("Error while loading:%s\n",filename);
}


bool Knight::init()
{
	sprite = Sprite::create("Character\\Knight.png");
	if (sprite == NULL)
	{
		problemLoading("Character\\Knight_right.png");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	return true;
}



