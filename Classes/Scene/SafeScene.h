/*
* @file   SafeScene.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

/*
* some flaws:
* no interaction with characters
* lacking a menu for setting
* (optional) better if can choose character or have some chat with these roles
*/

#ifndef __SAFESCENE_H__
#define __SAFESCENE_H__

#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"AudioEngine.h"
#include"Actor\Character\Knight.h"
#include"Actor\Enemy\Enemy.h"
#include"BattleScene.h"

#include<vector>
#include<string>
#include<iostream>

USING_NS_CC;
using namespace std;

class SafeScene :public cocos2d::Scene
{
public:
	static Scene* CreateScene();

	void update(float dt) override;

	virtual bool init();
		
	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(SafeScene);//automatically call the create(),init(),and autorelease()

	~SafeScene();
private:
	Knight* knight = nullptr;
	GunEnemy* enemy = nullptr;

	//useless now
	//int SelectedBulletNum = 0;
	//int MaxBulletNum = 200;
	//vector<Bullet*> bullets=vector<Bullet*>(MaxBulletNum);
};

#endif