/*
* @file   SafeScene.cpp
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#include"SafeScene.h"
#include"SetScene.h"
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
	enemy->SetHP(enemy->GetHP() - 1);

	//knight
	knight->MoveinSafeScene();

	//Status update
	BloodLoadingBar->setPercent(this->knight->GetHP() * 100 / 5);
	ArmorLoadingBar->setPercent(this->knight->GetShield() * 100 / 5);
	MPLoadingBar->setPercent(float(this->knight->GetMP()) / 200.0f * 100);

	HPLabel->setString(Value(this->knight->HP).asString() + "/5");
	armorLabel->setString(Value(this->knight->Shield).asString() + "/5");
	MPLabel->setString(Value(this->knight->MP).asString() + "/200");
	//
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

	auto visiblesize = Director::getInstance()->getVisibleSize();
	if (knight->isGoingBattle && knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		auto battlescene = BattleScene::create();
		Director::getInstance()->pushScene(TransitionFade::create(0.5, battlescene, Color3B(255, 255, 255)));
	}
	//box
	
	if (box->isboxwithknight(knight))
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
	//knight
	knight = Knight::create();

	this->addChild(knight, 5);
	this->addChild(knight->weapon[knight->Holding], 5);
	//box
	box = Box::create();
	box->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(box, 3);
	this->addChild(box->props[box->proptype], 4);
	box->props[box->proptype]->setVisible(false);

	//menu_exit
	auto closeItem = MenuItemImage::create("menu\\exit.png", "menu\\exit01.png", CC_CALLBACK_1(SafeScene::menuCloseCallback, this));
	auto closemenu = Menu::create(closeItem, NULL);
	closemenu->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));
	this->addChild(closemenu, 1);

	//menu_set
	auto setItem = MenuItemImage::create("menu\\set.png", "menu\\set.png", CC_CALLBACK_1(SafeScene::menuCloseCallbackSet, this));
	auto setmenu = Menu::create(setItem, NULL);
	setmenu->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 100));
	this->addChild(setmenu, 1);

	//enemy
	enemy = GunEnemy::create();

	this->addChild(enemy, 2);
	this->addChild(enemy->GetWeapon(), 2);

	this->scheduleUpdate();

	return true;
}


void SafeScene::menuCloseCallbackSet(Ref* pSender)
{
	auto setscene = SetScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}


void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

SafeScene::~SafeScene()
{
}

