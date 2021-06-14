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
					runAction(MoveAnimate);
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
					runAction(MoveAnimate);
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
					runAction(MoveAnimate);
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
					runAction(MoveAnimate);
					isMoving = true;
				}
				break;
			}
			//attack
			case EventKeyboard::KeyCode::KEY_J:
			case EventKeyboard::KeyCode::KEY_CAPITAL_J:
			{	
				if (weapon[Holding]->Type == isGun)
					isShooting = true;
				else if (weapon[Holding]->Type == isMelee)
					isMeleeing = true;
				isGoingBattle = true;
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
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_CAPITAL_A:
			{
				MoveSpeedX = 0;
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_CAPITAL_S:
			{
				MoveSpeedY = 0;
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_CAPITAL_D:
			{
				MoveSpeedX = 0;
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_J:
			case EventKeyboard::KeyCode::KEY_CAPITAL_J:
			{
				isGoingBattle = false;
				isShooting = false;
				break;
			}
		}
	};

	if (MoveSpeedX != 0 && MoveSpeedY != 0)
	{
		MoveSpeedX = MoveSpeedX / MoveSpeed * MoveSpeed/(sqrt(2));
		MoveSpeedY = MoveSpeedY / MoveSpeed * MoveSpeed/(sqrt(2));
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(KnightEventListenerKeyboard, this);//forget this sentence!!for it I stopped for a week!!
}

void Knight::AttackwithGun(Bullet *bullet)
{
	weapon[Holding]->Shoot(bullet);
}

void Knight::AttackMelee()
{
	weapon[Holding]->Attack();
}

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
	weapon[0] = Weapon::create("Weapon\\Pistol.png");
	weapon[0]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
}

bool Knight::init()
{
	//init
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//weapon
	initWeapon();

	//change the direction with the change of speed
	auto ChangeDirection = [this](float) {
		auto visiblesize = Director::getInstance()->getVisibleSize();
		if (getPositionX() + MoveSpeedX<0 || getPositionX() + MoveSpeedX>visiblesize.width)
			MoveSpeedX = 0;
		if (getPositionY() + MoveSpeedY<0 || getPositionY() + MoveSpeedY>visiblesize.height)
			MoveSpeedY = 0;
		if (MoveSpeedX > 0)
		{
			//knight
			setFlippedX(false);
			//weapon
			weapon[Holding]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
			weapon[Holding]->setFlippedX(false);
		}
		else if (MoveSpeedX < 0)
		{
			//knight
			setFlippedX(true);
			//weapon
			weapon[Holding]->setPosition(getPositionX() - WeaponAndHeroDistance, getPositionY());
			weapon[Holding]->setFlippedX(true);
		}
		else//weapon
		{
			weapon[Holding]->setPosition(getPositionX() + (isFlippedX() ? -1 : 1) * WeaponAndHeroDistance, getPositionY());
		}
	};

	schedule(ChangeDirection, FPS, "ChangeDirection");

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
	setPosition(getPositionX() + MoveSpeedX, getPositionY() + MoveSpeedY);

	//WeaponFollow();
	//it has been scheduled in the init()(the lambda function)
}

void Knight::WeaponFollow()
{
	if (MoveSpeedX < 0)
	{
		weapon[Holding]->setPosition(getPositionX() - WeaponAndHeroDistance, getPositionY());
		weapon[Holding]->setFlippedX(true);
	}
	else if (MoveSpeedX > 0)
	{
		weapon[Holding]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
		weapon[Holding]->setFlippedX(false);
	}
	else
	{
		weapon[Holding]->setPosition(getPositionX() + (isFlippedX()?-1:1)*WeaponAndHeroDistance, getPositionY());
	}
}


