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

Scene* SafeScene::CreateScene()
{
	return SafeScene::create();
}

//print useful error message
static void problemLoading(string filename)
{
	cerr << "Error while loading:" << filename << endl;
	cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n";
}

void SafeScene::update(float delta)
{
	//knight
	knight->MoveinSafeScene();

	if (knight->isMeleeing)
	{
		knight->AttackMelee();
		knight->isMeleeing = false;
	}
	else if (knight->isShooting)
	{
		bullets.at(SelectedBulletNum)->removeFromParentAndCleanup(true);
		bullets.at(SelectedBulletNum) = Bullet::create("Bullet/yellowbullet.png");
		addChild(bullets.at(SelectedBulletNum), 3);
		knight->AttackwithGun(bullets.at(SelectedBulletNum++));
		knight->isShooting = false;
	}
	
	//enemy
	if (!enemy->isInBattle)
	{
		enemy->Wandering();
	}
	else
	{
		//battle
		bullets.at(SelectedBulletNum)->removeFromParentAndCleanup(true);
		bullets.at(SelectedBulletNum) = Bullet::create("Bullet/Bullet1.png");
		addChild(bullets.at(SelectedBulletNum), 3);
		enemy->Shoot(bullets.at(SelectedBulletNum++));
		enemy->Wandering();
	}
	auto visiblesize = Director::getInstance()->getVisibleSize();
	if (knight->isGoingBattle && knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		auto battlescene = BattleScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, battlescene, Color3B(255, 255, 255)));
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
		SafeBackground->setScale(visibleSize.width / SafeBackground->getContentSize().width);
		SafeBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(SafeBackground, 0);
	}

	//knight
	knight = Knight::create("Character\\Knight.png");

	this->addChild(knight, 1);
	this->addChild(knight->weapon[knight->Holding], 1);

	//enemy
	enemy = Enemy::create("Enemy\\Alien\\enemy001.png");

	this->addChild(enemy, 2);
	this->addChild(enemy->weapon, 2);

	//bullet
	for (int i = 0; i < MaxBulletNum; i++)
	{
		bullets.at(i) = Bullet::create("Bullet/Bullet1.png");
		this->addChild(bullets.at(i), 3);
		bullets.at(i)->setVisible(false);
	}

	this->scheduleUpdate();

	return true;
}

void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

SafeScene::~SafeScene()
{
}
