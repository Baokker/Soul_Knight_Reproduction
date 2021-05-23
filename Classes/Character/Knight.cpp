/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include<cocos2d.h>
#include"Knight.h"
#include"..//Const.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
	log("Error while loading:%s\n",filename);
}

void Knight::setKnightKeyboardListener()
{

}

bool Knight::init()
{
	sprite= Sprite::create("Character\\Knight.png");
	if (sprite == NULL)
	{
		problemLoading("Character\\Knight.png");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//setKnightKeyboardListener();

	scheduleUpdate();
	sprite->scheduleUpdate();
	return true;
}

void Knight::MoveinSafeScene()
{
	float duration = 0.1;
	
	if (KeyMap[EventKeyboard::KeyCode::KEY_W] || KeyMap[EventKeyboard::KeyCode::KEY_CAPITAL_W])//a little need to modified
	{
		if (sprite->getPositionY() + MoveSpeed > FRAME_SIZE_Y)
			sprite->setPosition(sprite->getPositionX(), FRAME_SIZE_Y);
		else
			sprite->setPosition(sprite->getPositionX(), sprite->getPositionY()+MoveSpeed);

	}
}


