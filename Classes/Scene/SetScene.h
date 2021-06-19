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
public:
	static Scene* CreateScene();
	void menuCloseCallbackEnd(Ref* pSender);

	virtual bool init();
	CREATE_FUNC(SetScene);
private:
	//StartScene startscene;
	float volume = 0.1;
	Menu* menu_music_on;
	Menu* menu_music_off;
	static int present ;
	int audioID;
	Slider* slider;
};

#endif


