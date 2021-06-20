#pragma once
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "Actor\Character\Knight.h"
#include "BattleRoom.h"
#include "ui/CocosGUI.h"
#include "Hall.h"
#include "Const.h"
#include "cocos2d.h"
#include <queue>

USING_NS_CC;
using std::queue;
using std::vector;
using std::string;

class BattleScene : public Scene 
{
	friend class SafeScene;
	static constexpr int SIZEMTX = 5;
	static constexpr int MAXROOM = 8; // temporarily make it 

public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float delta) override;
	bool initwithOriginalKnightAndLevel(Knight* originalknight, int prelevel);

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);
	void menuCloseCallbackSet(cocos2d::Ref* pSender);

	void SetLoadingBar();
	void SetMenu();
	void SetMoneyLabel();
	void SetCheckpoint();

	void UpdateMoneyLabel();
	void UpdateLoadingBar();
	void updateAttack();
	void updateBullet(Bullet*, Enemy*);
	void Updatecheckpoint();
	string getSceneType();
	CREATE_FUNC(BattleScene);
	static BattleScene* createwithOriginalKnightAndLevel(Knight* originalknight, int prelevel);

private:
	int level = 0;
	void updateAll();
	void initRoom();
	void getNextRoom(int, int, BattleRoom*, queue<BattleRoom*>&);
	void randomGenerate(int, int);
	void setHallWithWidth(Hall*, const BattleRoom*, const BattleRoom*);
	void setHallWithHeight(Hall*, const BattleRoom*, const BattleRoom*);
	void connectRoom(BattleRoom*);
	int cntRoom = 0;
	Knight* knight = nullptr;
	Vector<Hall*> vecHall;
	Vector<Bullet*> vecBullet;
	vector<int> Type{ STATUE,BOX };
	string sceneType = "Forest";

	BattleRoom* beginRoom = nullptr;
	BattleRoom* endRoom = nullptr;
	BattleRoom* curRoom = nullptr;
	BattleRoom* battleRoom[SIZEMTX][SIZEMTX] = { nullptr };  // rooms

	ui::LoadingBar* BloodLoadingBar;
	ui::LoadingBar* ArmorLoadingBar;
	ui::LoadingBar* MPLoadingBar;

	Label* HPLabel;
	Label* armorLabel;
	Label* MPLabel;

	Label* CheckpointLabel;
	Label* MoneyLabel;
	//useless now
	//int SelectedBulletNum = 0;
	//int MaxBulletNum = 200;
	//vector<Bullet*> bullets = vector<Bullet*>(MaxBulletNum);//bullets
};

#endif
