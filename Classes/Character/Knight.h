/*
* @file   Knight.h
* @author fbc
* @date   2021/5/15
* @modified name date
*/


USING_NS_CC;

#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include<cocos2d.h>
#include<Scene/SafeScene.h>
class Knight : public Node//reorginaze the arrangement of Knight
{
	friend class SafeScene;
	//the format should go like the following:
	public://mostly unwritten
		void attack();
		void move();
		
		/*
		* @author fbc
		* @date 2021/5/15
		* @function create a sprite of Knight
		*/
		virtual bool init();

	private:
		int MaxHP = 5;
		int HP = 5;
		int MaxMP = 200;
		int MP = 200;
		int MaxShield = 5;
		int Shield = 5;
		int money = 0;
		Sprite* sprite = nullptr;

};
#endif