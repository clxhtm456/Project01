#include <Windows.h>
#include "Unit.h"
#include "missile.h"
#include "options.h"
#pragma once

#define monster_ani_speed 1
class Monster : public Unit
{
	int dividerTimer;
	int chaseTimer;
	int bloodfieldTimer;
	int roamingTimer;

	bool chase;
	bool aggresive;
	int anispeed;
	HBITMAP Bstandbit[19];
	HBITMAP Bstandmask[19];
	Unit* enemy;
	missile *b1[6];
public:
	Monster(Unit* U, HINSTANCE hinst,map* m,int x, int y) : Unit(hinst,m) 
	{
		enemy = U;
		chase = false;
		HP = boss_max_hp;
		DMG = boss_dmg;
		xPos = x;
		yPos = y;
		jumpcount = 10;
		chaseTimer = 10;
		bloodfieldTimer = 500;
		weight = 0;
		acount = 0;
		ccount = 0;
		statecount = 12;
		anispeed = 2;
	}
	~Monster()
	{
		for (int i = 0; i < 19; i++)
		{
			DeleteObject(Bstandmask[i]);
			DeleteObject(Bstandbit[i]);
		}
		World->p[xpost][ypost] = NULL;
	}
	void moving(double speed);
	void init(Unit* U, HINSTANCE hInst, map* m);
	void setstate(int i);
	void UpdateAI();
	void Chase(Unit* U);
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
	void UpdateBitmap();
};