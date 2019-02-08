#include "resource1.h"
#include "options.h"
#pragma once

class missile : public Unit
{
	Unit *master;
	Unit *enemy;
	int shotangle;
	double desX;
	double desY;
	int deactcount;
	int delaycount;
	int state;
	int statecount;
	POINT point[3];
	double anispeed;
	int tornadocount;
	int buffcount;
	bool act;
	BOOL activate;
	HBITMAP firebit;
	HBITMAP hBitmapMask;
	HDC hdcMask;
public:
	missile(Unit* U, HINSTANCE hinst,map* m, int type,int delay = 0,int angle = 0) : Unit(hinst,m){
		tornadocount = 0;
		buffcount = 0;
		state = type;
		acount = 0;
		ccount = 0;
		delaycount = delay;
		if (delaycount)
			act = false;
		else
			act = true;
		DMG = U->getDamage();
		sizex = 0;
		sizey = 0;
		master = U;
		activate = TRUE;
		shotangle = angle;
		DeleteObject(firebit);
		DeleteObject(hBitmapMask);
		DeleteDC(hdcMask);
		//World->p[getxPos()][getyPos()] = this;
		switch (type)
		{
		case 0:
			firebit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			break;
		case 1:
			firebit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			break;
		}
	}
	~missile()
	{
		DeleteObject(firebit);
		DeleteObject(hBitmapMask);
		DeleteDC(hdcMask);
		World->p[xpost][ypost] = NULL;
	}

	HBITMAP createMask(HDC hdcBitmap, int width, int height);
	BOOL getactivate();
	void UpdateAI();
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
};