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

	auto KnightEventListenerKeyboard = EventListenerKeyboard::create();

	KnightEventListenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event* event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_CAPITAL_W)
		{
			
			if (sprite->getPositionY() + MoveSpeed > FRAME_SIZE_Y)
				sprite->setPosition(sprite->getPositionX(), FRAME_SIZE_Y);
			else
				sprite->setPosition(sprite->getPositionX(), sprite->getPositionY() + MoveSpeed);
		}

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(KnightEventListenerKeyboard, sprite);//forget this sentence!!for it I stopped for a week!!
}
/*
Animate* MoveUpinSafeScene()
{
	return Animate::create();
}

Animate* MoveDowninSafeScene()
{
	return Animate::create();
}

Animate* MoveLeftinSafeScene()
{
	return Animate::create();
}

Animate* MoveRightinSafeScene()
{
	return Animate::create();
}
*/
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

	scheduleUpdate();
	sprite->scheduleUpdate();
	return true;


}

void Knight::MoveinSafeScene()
{
	float duration = 0.1;
	if (sprite->getPositionY() + MoveSpeed > FRAME_SIZE_Y)
		sprite->setPosition(sprite->getPositionX(), FRAME_SIZE_Y);
	else
		sprite->setPosition(sprite->getPositionX(), sprite->getPositionY() + MoveSpeed);
}


