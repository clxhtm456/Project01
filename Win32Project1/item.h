
#include "Unit.h"
#include "Player.h"
#pragma once
class item :public Unit
{
	int deactcount;
	HBITMAP Boxbit;
	HBITMAP Boxmask;
public:
	item(HINSTANCE hinst, map* m,Camera* c,int type,int x, int y) : Unit(hinst, m,c)
	{
			deactcount = 100;
			xPos = x;
			yPos = y;
	}
	void UpdateAI();
	void UpdateAnimation(HDC deshdc, HDC sourcehdc);
};