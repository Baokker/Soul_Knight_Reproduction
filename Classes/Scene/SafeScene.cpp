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
	if (knight->Getweapon()->CheckifCanAttack())
	{
		if (knight->isMeleeing)
		{
			auto attackmelee = knight->AttackMelee();
		}
		else if (knight->isShooting)
		{
			if (knight->GetMP() <= 0)
			{
				if (knight->AttackMeleeWithGun().intersectsRect(enemy->getBoundingBox()))
					enemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
			
				if (knight->AttackMeleeWithGun().intersectsRect(meleeenemy->getBoundingBox()))
					meleeenemy->SetHP(enemy->GetHP() - dynamic_cast<Gun*>(knight->weapon[knight->Holding])->Getdamage());
			}
			else
			{
				auto bullet = Bullet::create();
				addChild(bullet, 3);
				knight->AttackwithGun(bullet);
			}
		}
	}
	
	//bar
	UpdateLoadingBar();

	//transfer
	auto visiblesize = Director::getInstance()->getVisibleSize();

	if (knight->getPositionY() > visiblesize.height - 100 && knight->getPositionX() > visiblesize.width / 2 - 50 && knight->getPositionX() < visiblesize.width / 2 + 50)
	{
		if (getChildByName("enter_game_reminder")==nullptr)
			addChild(FloatText::create("Click J to start game", Vec2(visiblesize.width / 2, visiblesize.height - 60), 3),3,"enter_game_reminder");
		if (knight->isGoingBattle)
		{
			auto battlescene = BattleScene::create();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, battlescene , Color3B(255, 255, 255)));
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

	//bar
	SetLoadingBar();

	//menu
	SetMenu();

	//reminder
	auto labelwasd = Label::createWithTTF("wasd for moving", "fonts/Facon.ttf", 20);
	labelwasd->setPosition(visibleSize.width / 2, 30);
	addChild(labelwasd);

	auto labelj = Label::createWithTTF("j for attack and operate", "fonts/Facon.ttf", 20);
	labelj->setPosition(visibleSize.width / 2, 60);
	addChild(labelj);

	auto labelk = Label::createWithTTF("k for switch weapon", "fonts/Facon.ttf", 20);
	labelk->setPosition(visibleSize.width / 2, 90);
	addChild(labelk);

	//knight
	knight = Knight::create();

	this->addChild(knight, 4);
	this->addChild(knight->weapon[0], 4);
	this->addChild(knight->weapon[1], 4);

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
	this->present = setscene->present;
	this->Soundeffect = setscene->Soundeffect;
	if (Soundeffect)
	{
		auto audiobutton = AudioEngine::play2d("music\\button.mp3", false);
		AudioEngine::setVolume(audiobutton, present / 100.0f);
	}
	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}
