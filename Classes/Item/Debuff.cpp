#include "Debuff.h"
/*
* @file   Debuff.cpp
* @author fbc
* @date   2021/6/17
* @modified name date
*/

bool Debuff::init()
{
	setGlobalZOrder(5);

	auto disappear = [this](float)
	{
		removeFromParentAndCleanup(true);
	};

	scheduleOnce(disappear, GetDuration(), "disappear");

	return true;
}

int Debuff::Getdamage()
{
	return damage;
}

void Debuff::Setdamage(int num)
{
	damage = num;
}

bool Debuff::BindwithKnight(Knight* knight)
{
	return true;
}

float Debuff::GetDuration()
{
	return Duration;
}

void Debuff::SetDuration(float time)
{
	Duration = time;
}

string Debuff::GetRemindWord()
{
	return RemindWord;
}

void Debuff::SetRemindWord(string words)
{
	RemindWord = words;
}

void Debuff::SetCurtime(int time)
{
	Curtime = time;
}

int Debuff::GetCurtime()
{
	return Curtime;
}
