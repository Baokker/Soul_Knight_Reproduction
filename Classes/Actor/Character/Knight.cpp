/*
* @file   Knight.cpp
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include "Knight.h"
#include"Scene/SafeScene.h"//for die situation

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
				SetMoveSpeedY(GetMoveSpeed());
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
				SetMoveSpeedX(-GetMoveSpeed());
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
				SetMoveSpeedY(-GetMoveSpeed());
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
				SetMoveSpeedX(GetMoveSpeed());
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
				SetMoveSpeedY(0);
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_CAPITAL_A:
			{
				SetMoveSpeedX(0);
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_S:
			case EventKeyboard::KeyCode::KEY_CAPITAL_S:
			{
				SetMoveSpeedY(0);
				stopAllActions();
				isMoving = false;
				break;
			}
			case EventKeyboard::KeyCode::KEY_D:
			case EventKeyboard::KeyCode::KEY_CAPITAL_D:
			{
				SetMoveSpeedX(0);
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

	if (GetMoveSpeedX() != 0 && GetMoveSpeedY() != 0)
	{
		SetMoveSpeedX(GetMoveSpeedX() / GetMoveSpeed() * GetMoveSpeed()/(sqrt(2)));
		SetMoveSpeedY(GetMoveSpeedY() / GetMoveSpeed() * GetMoveSpeed()/(sqrt(2)));
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(KnightEventListenerKeyboard, this);//forget this sentence!!for it I stopped for a week!!
}

void Knight::AttackwithGun(Bullet *bullet)
{
	dynamic_cast<Gun*>(weapon[Holding])->Shoot(bullet);
}

Rect Knight::AttackMelee()
{
	return dynamic_cast<Melee*>(weapon[Holding])->Attack();
}

Rect Knight::AttackMeleeWithGun()
{
	return dynamic_cast<Gun*>(weapon[Holding])->Attack();
}

bool Knight::CheckifDie(){return HP <= 0;}

bool Knight::CheckifMPenough()
{
	return MP >= 0;
}

void Knight::SetChangeDirection()
{
	//change the direction with the change of speed
	auto ChangeDirection = [this](float) {
		auto visiblesize = Director::getInstance()->getVisibleSize();
		if (getPositionX() + GetMoveSpeedX() < 0 || getPositionX() + GetMoveSpeedX() > visiblesize.width)
			SetMoveSpeedX(0);
		if (getPositionY() + GetMoveSpeedY() < 0 || getPositionY() + GetMoveSpeedY() > visiblesize.height)
			SetMoveSpeedY(0);
		if (GetMoveSpeedX() > 0)
		{
			//knight
			setFlippedX(false);
			//weapon
			weapon[0]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
			weapon[1]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
			weapon[0]->setFlippedX(false);
			weapon[1]->setFlippedX(false);
		}
		else if (GetMoveSpeedX() < 0)
		{
			//knight
			setFlippedX(true);
			//weapon
			weapon[0]->setPosition(getPositionX() - WeaponAndHeroDistance, getPositionY());
			weapon[1]->setPosition(getPositionX() - WeaponAndHeroDistance, getPositionY());
			weapon[0]->setFlippedX(true);
			weapon[1]->setFlippedX(true);
		}
		else//weapon
		{
			weapon[0]->setPosition(getPositionX() + (isFlippedX() ? -1 : 1) * WeaponAndHeroDistance, getPositionY());
			weapon[1]->setPosition(getPositionX() + (isFlippedX() ? -1 : 1) * WeaponAndHeroDistance, getPositionY());
		}
	};

	schedule(ChangeDirection, FPS, "ChangeDirection");
}

void Knight::SetAnimate()
{
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
}

void Knight::SetHP(int num)
{
	HP = num;
}

int Knight::GetHP()
{
	return HP;
}

void Knight::SetMaxHP(int num)
{
	MaxHP = num;
}

int Knight::GetMaxHP()
{
	return MaxHP;
}


void Knight::SwitchWeapon()//the scene should also update!
{
	if (isHavingOneWeapon)
		return;

	if (Holding == 0)
	{
		Holding = 1;
		weapon[0]->setVisible(false);
		weapon[1]->setVisible(true);
	}
	else if (Holding == 1)
	{
		Holding = 0;
		weapon[1]->setVisible(false);
		weapon[0]->setVisible(true);
	}	
}

void Knight::initWeapon()
{
	weapon[0] = Gun::create("Weapon\\Gun.png");
	weapon[0]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
	weapon[1] = Melee::create("Weapon\\Sword.png");
	dynamic_cast<Melee*>(weapon[1])->initAnimate();
	weapon[1]->setPosition(getPositionX() + WeaponAndHeroDistance, getPositionY());
	weapon[1]->setVisible(false);
	Holding = 0;
}

bool Knight::init()
{
	if (!Actor::init())
		return false;

	//init
	auto visibleSize = Director::getInstance()->getVisibleSize();
	setPosition(visibleSize.width / 2, visibleSize.height / 2);

	//weapon
	initWeapon();

	//change direction in every frame
	SetChangeDirection();

	//keyboard
	setKnightKeyboardListener();

	//animate
	SetAnimate();

	return true;
}

void Knight::DeductBlood(int num)
{
	if (Shield > num)
	{
		Shield -= num;
		return;
	}
	else
	{
		HP -= (num - Shield);
	}
}

void Knight::MoveinSafeScene()
{
	/*
	let fbc explain how to make the knight move. it has two parts:
	firstly,create a keyboardlistener in the class Knight and initialize it, so when the player presses keys like wasd, it will set the speed and play the animation(reset to zero when released)
	then,in this update function which will be executed sixty times per second, the computer check the speed and setposition every frame.
	almost every move goes like that
	*/
	setPosition(getPositionX() + GetMoveSpeedX(), getPositionY() + GetMoveSpeedY());

	//WeaponFollow();
	//it has been scheduled in the init()(the lambda function)
}

