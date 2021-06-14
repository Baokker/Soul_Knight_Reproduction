/*
* @file   StartScene.h
* @author fbc
* @date   2021/5/14
* @modified name date
*/

/*
basic component should include:
a picture as start scene
a button for start
a menu for setting for bgm
*/

/*some flaws need to solve including:
* add a bgm
* a menu for control music(pause and replay is needed ,better if having a toolbar)
* (optional)the menu could also have an instruction or namely guide for the game
*/


#ifndef __STARTSCENE_H__//save time
#define __STARTSCENE_H__

#include"cocos2d.h"
#include"AudioEngine.h"

USING_NS_CC;

//simulate these codes in HelloWorldScene.h
class StartScene :public cocos2d::Scene
{
	friend class SetScene;
public:
	static Scene* CreateScene();
	int audioID;
	virtual bool init();
	
	void menuPressToStart(Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	void menuCloseCallbackSet(Ref* pSender);
	CREATE_FUNC(StartScene);//automatically call the create(),init(),and autorelease()
};

#endif