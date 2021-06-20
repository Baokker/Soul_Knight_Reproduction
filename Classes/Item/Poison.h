/*
* @file   Poison.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __POISON_H__
#define __POISON_H__

#include"Debuff.h"

class Poison :public Debuff
{
	public:
		bool init();
		bool BindwithKnight(Knight* knight);
		static Poison* createAndBindwithKnight(Knight* knight);
	private:
};

#endif