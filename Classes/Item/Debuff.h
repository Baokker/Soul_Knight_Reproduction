/*
* @file   Debuff.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __DEBUFF_H__
#define __DEBUFF_H__

#include"cocos2d.h"
#include"..\Actor\Character\Knight.h"
#include <Const.h>
#include"..\FloatText\FloatText.h"

USING_NS_CC;
using std::string;

class Debuff :public Sprite
{
	public:
		bool init();

		int Getdamage();
		void Setdamage(int num);

		bool BindwithKnight(Knight* knight);

		float GetDuration();
		void SetDuration(float time);

		string GetRemindWord();
		void SetRemindWord(string words);

		void SetCurtime(int time);
		int GetCurtime();

	private:
		float Duration = 2;
		int damage = 0;
		int Curtime = 0;
		string RemindWord;
};

#endif