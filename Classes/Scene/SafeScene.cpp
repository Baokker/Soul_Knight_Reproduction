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
	//boss
	if (!boss->GetisAlive()) {}
	else
	{
		boss->AImonitor(knight);
		//srand(time(NULL));
		if (boss->CheckifDie())
			boss->Die();
		else if (boss->GetisInBattle() && rand() % 3 < 1)//attack!
		//if it is a meleeenemy just change the code related to attack 
		{
			srand(time(0));
			switch (rand() % 3)
			{
			case 0:
				if (boss->AttackMelee().intersectsRect(knight->getBoundingBox()))
				{
					knight->deductHP(boss->GetWeapon()->Getdamage());
				}
				break;
			case 1:
				boss->Teleport(knight);
				break;
			case 2:
				auto poison = Poison::createAndBindwithKnight(boss, knight);
				addChild(poison, 3);
				break;
			}

		}
	}

	//knight
	knight->MoveinSafeScene();

	if (knight->isMeleeing)
	{
		auto attackmelee = knight->AttackMelee();
		if (attackmelee.intersectsRect(enemy->getBoundingBox()))
		{
			enemy->SetHP(enemy->GetHP() - knight->weapon[knight->Holding]->Getdamage());
		}
		else if (attackmelee.intersectsRect(meleeenemy->getBoundingBox()))
		{
			meleeenemy->SetHP(enemy->GetHP() - knight->weapon[knight->Holding]->Getdamage());
		}
		else if (attackmelee.intersectsRect(boss->getBoundingBox()))
		{
			boss->SetHP(enemy->GetHP() - knight->weapon[knight->Holding]->Getdamage());
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
	
	//bar
	UpdateLoadingBar();

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
			addChild(bullet, 5);
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
	if (knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		if (getChildByName("enter_game_reminder")==nullptr)
			addChild(FloatText::create("Click J to start game", Vec2(visiblesize.width / 2, visiblesize.height - 60), 3),3,"enter_game_reminder");
		if (knight->isGoingBattle)
		{
			auto battlescene = BattleScene::create();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, battlescene, Color3B(255, 255, 255)));
		}
	}

	if (knight->getBoundingBox().intersectsRect(spear->getBoundingBox()))
	{
		if (getChildByName("pick_up_weapon_reminder1") == nullptr)
			addChild(FloatText::create("Click J to pick it up", Vec2(spear->getPositionX(), spear->getPositionY() + 20), 3), 3, "pick_up_weapon_reminder1");
		if (knight->PickupWeapon(spear))
			swap(knight->weapon[knight->Holding], spear);
	}

	if (knight->getBoundingBox().intersectsRect(submachinegun->getBoundingBox()))
	{
		if (getChildByName("pick_up_weapon_reminder2") == nullptr)
			addChild(FloatText::create("Click J to pick it up", Vec2(submachinegun->getPositionX(), submachinegun->getPositionY() + 20), 3), 3, "pick_up_weapon_reminder2");
		if (knight->PickupWeapon(submachinegun))
			swap(knight->weapon[knight->Holding], submachinegun);
	}

	/*if (box->isboxwithknight(knight))
	{
		if (box->isopened == false && knight->j_press == true)
		{
			box->setVisible(false);
			box->isopened = true;
			box->props[box->proptype]->setVisible(true);
			knight->j_press = false;
		}
	}
	if (box->ispropswithknight(knight) && box->isopened == true && knight->j_press == true)
	{
		if (box->proptype == 0)
		{
			knight->SetHP(min(knight->GetHP() + 2, knight->GetMaxHP()));
			box->props[0]->setVisible(false);
		}
		else if (box->proptype == 1)
		{
			knight->SetMP(min(knight->GetMP() + 100, knight->GetMaxMP()));
			box->props[1]->setVisible(false);
		}
	}*/
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

	//bar
	SetLoadingBar();

	//menu
	SetMenu();

	//knight
	knight = Knight::create();

	this->addChild(knight, 4);
	this->addChild(knight->weapon[0], 4);
	this->addChild(knight->weapon[1], 4);

	//enemy
	srand(time(0));
	enemy = GunEnemy::create(SceneType[rand() % SceneType.size()]);
	meleeenemy = MeleeEnemy::create(SceneType[rand() % SceneType.size()]);

	this->addChild(enemy, 4);
	this->addChild(enemy->GetWeapon(), 4);

	this->addChild(meleeenemy, 4);
	this->addChild(meleeenemy->GetWeapon(), 4);

	////box
	//box = Box::create();
	//box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(box, 3);
	//this->addChild(box->props[box->proptype], 4);
	//box->props[box->proptype]->setVisible(false);

	//pick up weapon test
	spear = Spear::create();
	spear->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 3));
	addChild(spear, 4);

	submachinegun = SubmachineGun::create();
	submachinegun->setPosition(Vec2(visibleSize.width * 2 / 3, visibleSize.height / 3));
	addChild(submachinegun, 4);

	//boss
	boss = Boss::create();
	boss->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(boss, 4);
	addChild(boss->GetWeapon(), 4);

	//auto poison = Poison::createAndBindwithKnight(enemy, knight);
	//addChild(poison,3);

	this->scheduleUpdate();

	return true;
}

void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void SafeScene::SetLoadingBar()
{
	//Status bar
	auto StatusBackGround = Sprite::create("Character//StatusBackground.png");

	BloodLoadingBar = ui::LoadingBar::create("Character//StatusBlood.png");
	ArmorLoadingBar = ui::LoadingBar::create("Character//StatusArmor.png");
	MPLoadingBar = ui::LoadingBar::create("Character//StatusMP.png");

	BloodLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	ArmorLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	MPLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);

	StatusBackGround->setPosition(80, 680);
	BloodLoadingBar->setPosition(Vec2(89, 698));
	ArmorLoadingBar->setPosition(Vec2(89, 680));
	MPLoadingBar->setPosition(Vec2(89, 664));

	this->addChild(StatusBackGround, 100);
	this->addChild(BloodLoadingBar, 100);
	this->addChild(ArmorLoadingBar, 100);
	this->addChild(MPLoadingBar, 100);

	HPLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);
	armorLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);
	MPLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 15);

	HPLabel->setPosition(Vec2(89, 698));
	armorLabel->setPosition(Vec2(89, 680));
	MPLabel->setPosition(Vec2(89, 664));

	this->addChild(HPLabel, 100);
	this->addChild(armorLabel, 100);
	this->addChild(MPLabel, 100);
}

void SafeScene::UpdateLoadingBar()
{
	//Status update
	BloodLoadingBar->setPercent(this->knight->GetHP() * 100 / knight->MaxHP);
	ArmorLoadingBar->setPercent(this->knight->GetShield() * 100 / knight->MaxShield);
	MPLoadingBar->setPercent(float(this->knight->GetMP()) / float(knight->MaxMP) * 100);

	HPLabel->setString(Value(this->knight->HP).asString() + "/" + Value(this->knight->MaxHP).asString());
	armorLabel->setString(Value(this->knight->Shield).asString() + "/" + Value(this->knight->MaxShield).asString());
	MPLabel->setString(Value(this->knight->MP).asString() + "/" + Value(this->knight->MP).asString());
}

void SafeScene::SetMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//menu_exit
	auto closeItem = MenuItemImage::create("menu\\exit.png", "menu\\exit01.png", CC_CALLBACK_1(SafeScene::menuCloseCallback, this));
	closeItem->setScale(0.75);
	auto closemenu = Menu::create(closeItem, NULL);
	closemenu->setPosition(Vec2(visibleSize.width - 80, visibleSize.height - 100));
	this->addChild(closemenu, 1);

	//menu_set
	auto setItem = MenuItemImage::create("menu\\set.png", "menu\\set.png", CC_CALLBACK_1(SafeScene::menuCloseCallbackSet, this));
	setItem->setScale(0.75);
	auto setmenu = Menu::create(setItem, NULL);
	setmenu->setPosition(Vec2(visibleSize.width - 200, visibleSize.height - 100));
	this->addChild(setmenu, 1);
}

SafeScene::~SafeScene()
{
}

void SafeScene::menuCloseCallbackSet(Ref* pSender)
{
	auto setscene = SetScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}
