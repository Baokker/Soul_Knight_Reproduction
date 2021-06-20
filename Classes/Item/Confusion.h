/*
* @file   Confusion.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __CONFUSION_H__
#define __CONFUSION_H__

#include"Debuff.h"

class Confusion :public Debuff
{
	public:
		bool init();
		bool BindwithKnight(Knight* knight);
		static Confusion* createAndBindwithKnight(Knight* knight);
	private:
};

#endif