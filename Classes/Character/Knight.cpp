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
			//move
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
			//attack
			case EventKeyboard::KeyCode::KEY_J:
			case EventKeyboard::KeyCode::KEY_CAPITAL_J:
			{	
				if (weapon[Holding].Type == isGun)
					isShooting = true;
				else if (weapon[Holding].Type == isMelee)
					isMeleeing = true;
				break;
			}
			//switch weapon
			case EventKeyboard::KeyCode::KEY_K:
			case EventKeyboard::KeyCode::KEY_CAPITAL_K:
			{	
				SwitchWeapon();
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

void Knight::AttackwithGun(Bullet &bullet)
{
	weapon[Holding].Shoot(bullet);
}

void Knight::AttackMelee()
{
	//HoldingWeapon->Attack();
}

/*
void Knight::Attack()
{
	if (weapon[Holding].Type == isGun)
		AttackwithGun();
	else if (weapon[Holding].Type == isMelee)
		AttackMelee();
}
*/

void Knight::SwitchWeapon()//the scene should also update!
{
	if (isHavingOneWeapon)
		return;

	if (Holding == 0)
	{
		Holding = 1;
	}
	else if (Holding == 1)
	{
		Holding = 0;
	}	
}

void Knight::initWeapon()
{
	weapon[0].init();
	weapon[0].sprite->setPosition(sprite->getPositionX() + WeaponAndHeroDistance, sprite->getPositionY());
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

	//weapon
	initWeapon();

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

void Knight::MoveinSafeScene()
{
	/*
	let fbc explain how to make the knight move. it has two parts:
	firstly,create a keyboardlistener in the class Knight and initialize it, so when the player presses keys like wasd, it will set the speed and play the animation(reset to zero when released)
	then,in this update function which will be executed sixty times per second, the computer check the speed and setposition every frame.
	almost every move goes like that
	*/
	auto visiblesize = Director::getInstance()->getVisibleSize();
	if (sprite->getPositionX() + MoveSpeedX<0 || sprite->getPositionX() + MoveSpeedX>visiblesize.width)
		MoveSpeedX = 0;
	if (sprite->getPositionY() + MoveSpeedY<0 || sprite->getPositionY() + MoveSpeedY>visiblesize.height)
		MoveSpeedY = 0;	

	//sprite->setPosition(sprite->getPositionX() + 1, sprite->getPositionY() + 1);
	sprite->setPosition(sprite->getPositionX() + MoveSpeedX, sprite->getPositionY() + MoveSpeedY);

	if (MoveSpeedX > 0)
	{
		sprite->setFlippedX(false);
	}
	else if (MoveSpeedX < 0)
	{
		sprite->setFlippedX(true);
	}

	WeaponFollow();
}

void Knight::WeaponFollow()
{
	if (MoveSpeedX < 0)
	{
		weapon[Holding].sprite->setPosition(sprite->getPositionX() - WeaponAndHeroDistance, sprite->getPositionY());
		weapon[Holding].sprite->setFlippedX(true);
	}
	else if (MoveSpeedX > 0)
	{
		weapon[Holding].sprite->setPosition(sprite->getPositionX() + WeaponAndHeroDistance, sprite->getPositionY());
		weapon[Holding].sprite->setFlippedX(false);
	}
	else
	{
		weapon[Holding].sprite->setPosition(sprite->getPositionX() + (sprite->isFlippedX()?-1:1)*WeaponAndHeroDistance, sprite->getPositionY());
	}
}


