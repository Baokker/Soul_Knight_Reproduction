#pragma once
/*
* @file   Const.h
* @author fbc
* @date   2021/5/23
* @modified name date
*/

#include<map>

using namespace std;

constexpr int FRAME_SIZE_X = 1280;
constexpr int FRAME_SIZE_Y = 720;

constexpr int WeaponAndHeroDistance = 40;

struct BulletInfo
{
	std::string Name;
	std::string Path;

	BulletInfo(std::string BulletName,std::string BulletPath)
	{
		Name = BulletName;
		Path = BulletPath;
	}
};

struct WeaponInfo
{
	std::string Name;
	std::string Path;

	WeaponInfo(string WeaponName, string WeaponPath)
	{
		Name = WeaponName;
		Path = WeaponPath;
	}
};

constexpr int isGun = -1;
constexpr int isMelee = -2;//½üÕ½ in chinese
constexpr int Pistol = 1;
//string PistolBulletPath = "Bullet\\PistolBullet.png";

constexpr int UP = 0;
constexpr int DOWN = 1;
constexpr int LEFT = 2;
constexpr int RIGHT = 3;//luanlaide




