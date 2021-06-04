/*
* @file   SafeScene.cpp
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include"SafeScene.h"

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
		//bullets.at(SelectedBulletNum)->removeFromParentAndCleanup(true);
		//bullets.at(SelectedBulletNum) = Bullet::create("Bullet/yellowbullet.png");
		auto bullet = Bullet::create();
		addChild(bullet, 3);
		knight->AttackwithGun(bullet);
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
		//bullets.at(SelectedBulletNum) = Bullet::create("Bullet/Bullet1.png");
		auto bullet = Bullet::create();
		addChild(bullet, 3);
		//addChild(bullets.at(SelectedBulletNum), 3);
		enemy->AttackwithGun(bullet);
		enemy->Wandering();
	}
	auto visiblesize = Director::getInstance()->getVisibleSize();
	if (knight->isGoingBattle && knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		auto battlescene = BattleScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, battlescene, Color3B(255, 255, 255)));
	}
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
	knight = Knight::create();

	this->addChild(knight, 1);
	this->addChild(knight->weapon[knight->Holding], 1);

	//enemy
	enemy = GunEnemy::create();

	this->addChild(enemy, 2);
	this->addChild(enemy->GetWeapon(), 2);

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
