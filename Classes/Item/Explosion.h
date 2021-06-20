/*
* @file   Explosion.h
* @author fbc
* @date   2021/6/17
* @modified name date
*/

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include"Debuff.h"

class Explosion :public Debuff
{
	public:
		bool init();
		bool BindwithKnight(Knight* knight);
		static Explosion* createAndBindwithKnight(Knight* knight);
	private:
		int present;
		int Soundeffect;
};

#endif