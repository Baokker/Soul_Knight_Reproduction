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
		if (knight->AttackMelee().intersectsRect(enemy->getBoundingBox()))
		{
			enemy->SetHP(enemy->GetHP() - dynamic_cast<Melee*>(knight->weapon[knight->Holding])->Getdamage());
		}

		knight->isMeleeing = false;
	}
	else if (knight->isShooting)
	{
		if (knight->MP <= 0)
		{
			if (knight->AttackMeleeWithGun().intersectsRect(enemy->getBoundingBox()))
			{
				enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
			}
			if (knight->AttackMeleeWithGun().intersectsRect(meleeenemy->getBoundingBox()))
			{
				meleeenemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
			}
		}
		else
		{
			auto bullet = Bullet::create();
			addChild(bullet, 3);
			knight->AttackwithGun(bullet);

		}
		knight->isShooting = false;

	}
	
	//enemy
	if (!enemy->GetisAlive()) {}
	else
	{
		enemy->AImonitor(knight);
		//srand(time(NULL));
		if (enemy->CheckifDie())
			enemy->Die();
		else if (enemy->GetisInBattle() && rand() % 10 < 1)//attack!
		//if it is a meleeenemy just change the code related to attack 
		{
			auto bullet = Bullet::create();
			addChild(bullet, 3);
			enemy->AttackwithGun(bullet);
		}
	}

	//meleeenemy
	if (!meleeenemy->GetisAlive()) {}
	else
	{
		meleeenemy->AImonitor(knight);
		//srand(time(NULL));
		if (meleeenemy->CheckifDie())
			meleeenemy->Die();
		else if (meleeenemy->GetisInBattle() && rand() % 10 < 1)//attack!
		//if it is a meleemeleeenemy just change the code related to attack 
		{
			auto meleerect = meleeenemy->AttackMelee();
			if (meleerect.intersectsRect(knight->getBoundingBox()))
				knight->DeductBlood(meleeenemy->GetWeapon()->Getdamage());
		}
	}

	auto visiblesize = Director::getInstance()->getVisibleSize();
	if (knight->isGoingBattle && knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		auto battlescene = BattleScene::create();
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
	this->addChild(knight->weapon[0], 1);
	this->addChild(knight->weapon[1], 1);

	//enemy
	enemy = GunEnemy::create();
	meleeenemy = MeleeEnemy::create();

	this->addChild(enemy, 2);
	this->addChild(enemy->GetWeapon(), 2);

	this->addChild(meleeenemy, 2);
	this->addChild(meleeenemy->GetWeapon(), 2);

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
