/*
* @file   StartScene.cpp
* @author fbc
* @date   2021/5/14
* @modified name date
*/

#include<iostream>
#include<string>
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include"StartScene.h"
#include"SafeScene.h"
#include"SetScene.h"

using namespace std;
USING_NS_CC; //equals to using namespace cocos2d

Scene* StartScene::CreateScene()
{
	return StartScene::create();
}

//print useful error message
//use static so that only this program can execute it
static void problemLoading(string filename)
{
	cerr << "Error while loading:" << filename << endl;
	cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n";
}

bool StartScene::init()
{
	if (!Scene::init())
		return false;//check super init

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//music_begin

	audioID = AudioEngine::play2d("music\\bkmusic1.mp3", true);
	AudioEngine::setVolume(audioID, 0.5);
	//label
	const int StartLabelFontSize = 45;
	auto StartLabel = Label::createWithTTF("click here to start", "fonts/Facon.ttf", StartLabelFontSize);
	if (StartLabel == nullptr)
		problemLoading("fonts/Facon.ttf");
	else
	{
		//StartLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	}

	//menu_start
	auto StartItem = MenuItemLabel::create(StartLabel,CC_CALLBACK_1(StartScene::menuPressToStart,this));
	//notice placeholders for "this"
	auto StartMenu = Menu::create(StartItem,NULL);
	StartMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
	this->addChild(StartMenu, 1);
	//menu_close
	auto closeItem = MenuItemImage::create("menu\\exit.png", "menu\\exit01.png", CC_CALLBACK_1(StartScene::menuCloseCallback, this));
	auto closemenu = Menu::create(closeItem, NULL);
	closemenu->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));
	this->addChild(closemenu, 1);
	//menu_set
	auto setItem = MenuItemImage::create("menu\\set.png", "menu\\set.png", CC_CALLBACK_1(StartScene::menuCloseCallbackSet, this));
	auto setmenu = Menu::create(setItem, NULL);
	setmenu->setPosition(Vec2(visibleSize.width - 300, visibleSize.height - 100));
	this->addChild(setmenu, 1);
	//background
	auto StartBackground = Sprite::create("Scene\\StartScene.png");
	if (StartBackground == nullptr)
		problemLoading("Scene\\StartScene.png");
	else
	{
		StartBackground->setScale(0.65);
		StartBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(StartBackground, 0);
	}
	return true;
}

void StartScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void StartScene::menuPressToStart(Ref* pSender)
{
	auto safescene = SafeScene::create();
	Director::getInstance()->pushScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
}
void StartScene::menuCloseCallbackSet(Ref* pSender)
{
	auto setscene = SetScene::create();
	setscene->audioID = this->audioID;

	Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene, Color3B(255, 255, 255)));
}
