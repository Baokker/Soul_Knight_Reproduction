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
#include"..//Character/Knight.h"

USING_NS_CC;


class SafeScene :public cocos2d::Scene
{
public:
	static Scene* CreateScene();

	void update(float dt) override;

	virtual bool init();

	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(SafeScene);//automatically call the create(),init(),and autorelease()

private:
	Knight knight;


};

#endif