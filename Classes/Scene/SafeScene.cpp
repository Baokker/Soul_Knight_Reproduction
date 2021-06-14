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
		for (auto enemy : vecEnemy)
		{
			if (knight->AttackMelee().intersectsRect(enemy->getBoundingBox()))
			{
				enemy->SetHP(enemy->GetHP() - dynamic_cast<Melee*>(knight->weapon[knight->Holding])->Getdamage());
			}
		}

		knight->isMeleeing = false;
	}
	else if (knight->isShooting)
	{
		if (knight->MP <= 0)
		{
			for (auto enemy : vecEnemy)
			{
				if (knight->AttackMeleeWithGun().intersectsRect(enemy->getBoundingBox()))
				{
					enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
				}
			}
		}
		else
		{
			auto bullet = Bullet::create();
			vecBullet.pushBack(bullet);
			addChild(bullet, 3);
			knight->AttackwithGun(bullet);
		}
		knight->isShooting = false;

	}
	for (auto bullet : vecBullet)
	{
		for (auto enemy : vecEnemy)
		{
			if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
			{
				enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
				bullet->setVisible(false);
				bullet->stopAllActions();
				bullet->MoveSpeedX = bullet->MoveSpeedY = 0;
				bullet->removeAllChildrenWithCleanup(true);
			}
		}
	}
	//enemy
	for (auto enemy : vecEnemy)
	{
		if (!enemy->GetisAlive()) {}
		else
		{
			if (enemy->CheckifDie())
				enemy->Die();
			else if (!enemy->isInBattle)
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
	for (int i = 0; i < 5; i++)
	{

		enemy = GunEnemy::create();
		vecEnemy.pushBack(enemy);
		this->addChild(enemy, 2);
		this->addChild(enemy->GetWeapon(), 2);
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
