/*
* @file   Knight.cpp
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include<cocos2d.h>
#include<cmath>
#include<string>
#include"Knight.h"
#include"..//Const.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
	log("Error while loading:%s\n",filename);
}

Knight::~Knight()
{
	MoveAnimate->release();
}

void Knight::setKnightKeyboardListener()
{
	auto KnightEventListenerKeyboard = EventListenerKeyboard::create();
	
	KnightEventListenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keycode, Event* event)
	{
		switch (keycode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_CAPITAL_W:
			{
				MoveSpeedY = MoveSpeed;
				if (!isMoving)
				{
					sprite->runAction(MoveAnimate);
					isMoving = true;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_CAPITAL_A:
			{
				MoveSpeedX = -MoveSpeed;
				if (!isMoving)
				{
					sprite->runAction(MoveAnimate);
					isMoving = true;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_CAPITAL_S:
			{
				MoveSpeedY = -MoveSpeed;
				if (!isMoving)
				{
					sprite->runAction(MoveAnimate);
					isMoving = true;
				}
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_CAPITAL_D:
			{
				MoveSpeedX = MoveSpeed;
				if (!isMoving)
				{
					sprite->runAction(MoveAnimate);
					isMoving = true;
				}
				break;
			}
		}
	};

	KnightEventListenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event* event) {
		switch (keycode)
		{
			case EventKeyboard::KeyCode::KEY_W:
			case EventKeyboard::KeyCode::KEY_CAPITAL_W:
			{
				MoveSpeedY = 0;
				sprite->stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_CAPITAL_A:
			{
				MoveSpeedX = 0;
				sprite->stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_CAPITAL_S:
			{
				MoveSpeedY = 0;
				sprite->stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_CAPITAL_D:
			{
				MoveSpeedX = 0;
				sprite->stopAllActions();
				isMoving = false;
				break;
			}
		}
	};

	if (MoveSpeedX != 0 && MoveSpeedY != 0)
	{
		MoveSpeedX = MoveSpeedX / MoveSpeed * MoveSpeed/(sqrt(2));
		MoveSpeedY = MoveSpeedY / MoveSpeed * MoveSpeed/(sqrt(2));
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(KnightEventListenerKeyboard, sprite);//forget this sentence!!for it I stopped for a week!!
}

bool Knight::init()
{
	//init
	sprite= Sprite::create("Character\\Knight.png");
	if (sprite == NULL)
	{
		problemLoading("Character\\Knight.png");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//keyboard
	setKnightKeyboardListener();

	//animate
	auto MoveAnimation = Animation::create();
	std::string filename;
	for (int i = 1; i <= 2; i++)
	{
		filename = "Character\\Knight" + std::to_string(i) + ".png";
		MoveAnimation->addSpriteFrameWithFile(filename);
	}
	MoveAnimation->setLoops(-1);
	MoveAnimation->setDelayPerUnit(0.1);
	MoveAnimation->setRestoreOriginalFrame(true);
	MoveAnimate = Animate::create(MoveAnimation);
	MoveAnimate->retain();

	return true;
}



