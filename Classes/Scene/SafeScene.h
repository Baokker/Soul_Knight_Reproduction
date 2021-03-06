/*
* @file   SafeScene.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/

#ifndef __SAFESCENE_H__
#define __SAFESCENE_H__

#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"AudioEngine.h"
#include"Actor\Character\Knight.h"
#include"Actor\Enemy\Enemy.h"
#include"BattleScene.h"
#include"..\FloatText\FloatText.h"
#include"SetScene.h"
#include"Box/Box.h"
#include"Actor/Enemy/Boss.h"

#include<vector>
#include<string>
#include<iostream>

USING_NS_CC;
using namespace std;

class SafeScene :public cocos2d::Scene
{
	friend class BattleScene;

public:
	static Scene* CreateScene();

	void update(float dt) override;

	virtual bool init();
		
	void menuCloseCallback(Ref* pSender);
	void menuCloseCallbackSet(Ref* pSender);

	void SetLoadingBar();

	void UpdateLoadingBar();

	void SetMenu();

	CREATE_FUNC(SafeScene);//automatically call the create(),init(),and autorelease()

	~SafeScene();
private:
	Knight* knight = nullptr;
	GunEnemy* enemy = nullptr;
	MeleeEnemy* meleeenemy = nullptr;

	Box* box = nullptr;
	
	Weapon* spear = nullptr;
	Weapon* fishgun = nullptr;

	Boss* boss = nullptr;
	ui::LoadingBar* BloodLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* ArmorLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* MPLoadingBar = ui::LoadingBar::create();

	Label* HPLabel;
	Label* armorLabel;
	Label* MPLabel;

	int present;
	int Soundeffect;

	//useless now
	//int SelectedBulletNum = 0;
	//int MaxBulletNum = 200;
	//vector<Bullet*> bullets=vector<Bullet*>(MaxBulletNum);
};

#endif