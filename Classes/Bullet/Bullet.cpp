/*
* @file   Bullet.cpp
* @author fbc
* @date   2021/5/24
* @modified name date
*/

#include"Bullet.h"
#include"cocos2d.h"
#include"Const.h"

USING_NS_CC;

static void ProblemLoading(const char* filename)
{
	log("Error while loading:%s\n", filename);
}

bool Bullet::init()
{
	//sprite = Sprite::create("Bullet\\PistolBullet.png");
	//sprite->setPosition(weapon->sprite.getPosition());
	sprite = Sprite::create("Bullet/Bullet1.png");
	if (!sprite)
	{
		ProblemLoading("Bullet\\PistolBullet.png");
		return false;
	}

	auto Move = [this](float) {//float is necessary!!
		sprite->setPosition(sprite->getPositionX() + MoveSpeedX, sprite->getPositionY() + MoveSpeedY);
		return;
	};

	
	auto Disappear = [this](float) {
		auto visiblesize = Director::getInstance()->getVisibleSize();
		if (sprite->getPositionX() > visiblesize.width || sprite->getPositionY() > visiblesize.height)
		{
			sprite->setVisible(false);
			sprite->stopAllActions();
			MoveSpeedX = MoveSpeedY = 0;
		}
	};	

	sprite->schedule(Move, 1 / 60, "Move");
	sprite->schedule(Disappear, 1 / 60, "Disappear");

	return true;
}

//bool Bullet::initBulletwithWeapon(Weapon* weapon)
//{
//
//}



/*
* 
bool Bullet::Weaponinit(Weapon* weapon)
{

}
bool Bullet::Enemyinit(Enemy* enemy)
{
	sprite = Sprite::create("Bullet\\PistolBullet.png");
	return true;
}

void Bullet::update(float delta)
{
	sprite->setPosition(sprite->getPositionX() + MoveSpeedX, sprite->getPositionY() + MoveSpeedY);
}
*/



void Bullet::Move()
{


}
