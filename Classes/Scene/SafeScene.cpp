/*
* @file   SafeScene.cpp
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include<iostream>
#include<string>
#include<map>
#include "ui/CocosGUI.h"
#include"SafeScene.h"
#include"..//Character/knight.h"

using namespace std;
USING_NS_CC; //equals to using namespace cocos2d

//int SafeScene::MaxBulletNum = 100;
//vector<Bullet> SafeScene::bullets=vector<Bullet>(SafeScene::MaxBulletNum);//necessary

Scene* SafeScene::CreateScene()
{
	return SafeScene::create();
}

//print useful error message
//use static so that only this program can execute it
static void problemLoading(string filename)
{
	cerr << "Error while loading:" << filename << endl;
	cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n";
}

void SafeScene::update(float delta)
{
	knight.MoveinSafeScene();

	if (knight.isMeleeing)
	{
		knight.AttackMelee();
		knight.isMeleeing = false;
	}
	else if (knight.isShooting)
	{
		knight.AttackwithGun(bullets.at(SelectedBulletNum++));
		knight.isShooting = false;
	}

	if (enemy.isBindwithWeapon(enemyWeapon))
	{
		if (!enemy.isInBattle)
		{
			enemy.Wandering();
			enemy.WeaponFollow(enemyWeapon);
		}
		else
		{
			//battle
			if (enemy.isShoot != MaxBulletNum)
			{
				enemy.Shoot(enemyWeapon, bullets.at(SelectedBulletNum++));
				enemy.Wandering();
				enemy.WeaponFollow(enemyWeapon);
				//SelectedBulletNum++;
				enemy.isShoot++;
			}
			else
			{
				enemy.Wandering();
				enemy.WeaponFollow(enemyWeapon);
			}
		}
		//BulletsUpdate();
	}

	SelectedBulletNum = SelectedBulletNum %= MaxBulletNum;
}



bool SafeScene::init()
{
	if (!Scene::init())
		return false;//check super init

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//background
	auto SafeBackground = Sprite::create("Scene\\SafeScene.jpg");
	if (SafeBackground == nullptr)
		problemLoading("Scene\\SafeScene.jpg");
	else
	{
		SafeBackground->setScale(1.35);
		SafeBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(SafeBackground, 0);
	}


	this->addChild(&knight, 1);
	//knight
	//in this file the movement of knight has nothing with its move function in the battle room
	knight.init();

	this->addChild(knight.sprite, 1);
	this->addChild(knight.weapon[knight.Holding].sprite, 1);

	//Enemy enemy;
	enemy.init();
	//Weapon enemyWeapon;
	enemyWeapon.init();

	this->addChild(enemy.sprite, 0);
	this->addChild(enemyWeapon.sprite, 0);

	//bullet
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullets.at(i).init();
		this->addChild(bullets.at(i).sprite, 3);
		bullets.at(i).sprite->setVisible(false);
	}

	this->scheduleUpdate();
	return true;
}

void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void SafeScene::BulletsUpdate()//useless now
{
	if (bullets.size()==0)
		return;
	auto visiblesize = Director::getInstance()->getVisibleSize();

	for (int i=0; i!=bullets.size(); ++i)
	{
		bullets.at(i).sprite->setPosition(bullets.at(i).sprite->getPositionX() + bullets.at(i).MoveSpeedX, bullets.at(i).sprite->getPositionY() + bullets.at(i).MoveSpeedY);

		if (bullets.at(i).MoveSpeedX < 0)
		{
			bullets.at(i).sprite->setFlippedX(true);
		}
		else
		{
			bullets.at(i).sprite->setFlippedX(false);
		}

		if (bullets.at(i).sprite->getPositionX() > visiblesize.width)
		{
			freopen("output.txt", "a", stdout);
			log("bullet%d", int(i+1));
		}
	}

	//for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
	//{
	//	iter->sprite->setPosition(iter->sprite->getPositionX() + iter->MoveSpeedX, iter->sprite->getPositionY() + iter->MoveSpeedY);

	//	if (iter->MoveSpeedX < 0)
	//	{
	//		iter->sprite->setFlippedX(true);
	//	}
	//	else
	//	{
	//		iter->sprite->setFlippedX(false);
	//	}

	//	if (iter->sprite->getPositionX() + iter->MoveSpeedX >= Director::getInstance()->getVisibleSize().width|| iter->sprite->getPositionY() + iter->MoveSpeedY >= Director::getInstance()->getVisibleSize().height)
	//	{
	//		//removeChild(iter->sprite, true);
	//		//iter->sprite->removeFromParent();
	//		//iter->sprite->release();
	//		//if (bullets.size() != 0)
	//		//{
	//		//	iter=bullets.erase(iter);
	//		//	iter--;
	//		//}
	//		freopen("output.txt", "a", stdout);
	//		log("bullet%d", int(iter - bullets.begin()));
	//	}
	//}

}
