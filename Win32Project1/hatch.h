
#include "Unit.h"
#include "missile.h"
#include "options.h"
#pragma once

class Hatch : public Unit
{
	HBITMAP Bstandbit[1];
	HBITMAP Bstandmask[1];
public:
	Hatch(Unit* U, HINSTANCE hinst, map* m, Camera* c, int x, int y) : Unit(hinst, m, c)
	{
		HP = 10;
		DMG = 0;
		xPos = x;
		yPos = y;
		weight = 0;
		acount = 0;
		ccount = 0;
		statecount = 12;
	}
	~Hatch()
	{
		for (int i = 0; i < 1; i++)
		{
			DeleteObject(Bstandmask[i]);
			DeleteObject(Bstandbit[i]);
		}
		//World->p[xpost][ypost] = NULL;
	}
	void moving(double speed);
	void init(Unit* U, HINSTANCE hInst, map* m);
	void setstate(int i);
	void UpdateAI();
	void Chase(Unit* U);
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
	void UpdateBitmap();
};