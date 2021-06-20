/*
* @file   Slowdown.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __SLOWDOWN_H__
#define __SLOWDOWN_H__

#include"Debuff.h"

class Slowdown :public Debuff
{
	public:
		bool init();
		bool BindwithKnight(Knight* knight);
		static Slowdown* createAndBindwithKnight(Knight* knight);
	private:
};

#endif