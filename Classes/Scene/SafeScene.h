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
<<<<<<< HEAD
#include"Boxroom/Boxroom.h"
=======
#include"..\FloatText\FloatText.h"

>>>>>>> 0076bf1933eac1908f6446072b1c64920fd45843
#include<vector>
#include<string>
#include<iostream>

USING_NS_CC;
using namespace std;

class SafeScene :public cocos2d::Scene
{
	friend class SetScene;
public:
	static Scene* CreateScene();

	void update(float dt) override;

	virtual bool init();
		
	void menuCloseCallback(Ref* pSender);
	void menuCloseCallbackSet(Ref* pSender);
	CREATE_FUNC(SafeScene);//automatically call the create(),init(),and autorelease()

	~SafeScene();
private:
	Knight* knight = nullptr;
	GunEnemy* enemy = nullptr;
<<<<<<< HEAD
	Box* box = nullptr;

	ui::LoadingBar* BloodLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* ArmorLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* MPLoadingBar = ui::LoadingBar::create();

	Label* HPLabel;
	Label* armorLabel;
	Label* MPLabel;

=======
	MeleeEnemy* meleeenemy = nullptr;
>>>>>>> 0076bf1933eac1908f6446072b1c64920fd45843

	//useless now
	//int SelectedBulletNum = 0;
	//int MaxBulletNum = 200;
	//vector<Bullet*> bullets=vector<Bullet*>(MaxBulletNum);
};

#endif