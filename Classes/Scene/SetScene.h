#ifndef __SETSCENE_H__
#define __SETSCENE_H__

#include"cocos2d.h"
#include"AudioEngine.h"
#include"StartScene.h"

#include<iostream>
#include<string>
#include "ui/CocosGUI.h"
#include"SafeScene.h"
using namespace std;
using namespace cocos2d::ui;

USING_NS_CC;

class SetScene :public Scene
{
	friend class StartScene;
	friend class BattleScene;
	friend class SafeScene;
	friend class Knight;
public:
	static Scene* CreateScene();
	void menuCloseCallbackEnd(Ref* pSender);

	virtual bool init();
	CREATE_FUNC(SetScene);

private:
	//StartScene startscene;

	Menu* menu_music_on;
	Menu* menu_music_off;

	Button* button1;
	Button* button2;
	Button* button3;
	Button* button4;

	static int present ;
	static bool Soundeffect;
	static bool buttonchange;

	int audioID;
	Slider* slider;
};

#endif


