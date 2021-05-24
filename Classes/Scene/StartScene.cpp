/*
* @file   StartScene.cpp
* @author fbc
* @date   2021/5/14
* @modified name date
*/

#include<iostream>
#include<string>
#include "ui/CocosGUI.h"
#include"StartScene.h"
#include"SafeScene.h"

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

	//label
	const int StartLabelFontSize = 45;
	auto StartLabel = Label::createWithTTF("click here to start", "fonts/Facon.ttf", StartLabelFontSize);
	if (StartLabel == nullptr)
		problemLoading("fonts/Facon.ttf");
	else
	{
		//StartLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	}

	//menu
	auto StartItem = MenuItemLabel::create(StartLabel,CC_CALLBACK_1(StartScene::menuPressToStart,this));
	//notice placeholders for "this"
	auto StartMenu = Menu::create(StartItem,NULL);
	StartMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));

	this->addChild(StartMenu, 1);

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
	auto safescene = SafeScene::CreateScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, safescene, Color3B(255, 255, 255)));
}