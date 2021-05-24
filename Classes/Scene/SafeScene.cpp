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

	auto visiblesize = Director::getInstance()->getWinSize();
	if (knight.sprite->getPositionX() + knight.MoveSpeedX<0 || knight.sprite->getPositionX() + knight.MoveSpeedX>visiblesize.width)
		knight.MoveSpeedX = 0;
	if (knight.sprite->getPositionY() + knight.MoveSpeedY<0 || knight.sprite->getPositionY() + knight.MoveSpeedY>visiblesize.height)
		knight.MoveSpeedY = 0;	
	

	//knight.sprite->setPosition(knight.sprite->getPositionX() + 1, knight.sprite->getPositionY() + 1);
	knight.sprite->setPosition(knight.sprite->getPositionX() + knight.MoveSpeedX, knight.sprite->getPositionY() + knight.MoveSpeedY);
	//knight.sprite->runAction(MoveBy::create(0.05, Vec2(knight.MoveSpeedX, knight.MoveSpeedY)));

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

	this->scheduleUpdate();
	return true;
}


void SafeScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}