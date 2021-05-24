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
//use static so that only this program can execute it
static void problemLoading(string filename)
{
	cerr << "Error while loading:" << filename << endl;
	cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n";
}

void SafeScene::update(float delta)
{
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

	//knight
	//in this file the movement of knight has nothing with its move function in the battle room
	knight.init();
	this->addChild(knight.sprite, 1);
	knight.setKnightKeyboardListener();
	this->scheduleUpdate();
	return true;
}


void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}