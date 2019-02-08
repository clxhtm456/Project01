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
	missile(Unit* U, HINSTANCE hinst,map* m,Camera* c, int type,int delay = 0,int angle = 0) : Unit(hinst,m,c){
		faction = U->getfaction();
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
		
		sizex = 0;
		sizey = 0;
		master = U;
		activate = TRUE;
		shotangle = angle;
		DeleteObject(firebit);
		DeleteObject(hBitmapMask);
		DeleteDC(hdcMask);
		switch (type)
		{
		case 0:
			firebit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(HANDGUN));
			DMG = 1;
			break;
		case 1:
			firebit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(MACHINEGUN));
			DMG = 1;
			break;
		}
		for (int i = 0; i < Unit_Max_Count; i++)
		{
			if (World->pUnit[i] == NULL)
			{
				World->pUnit[i] = this;
				break;
			}
		}
	}
	~missile()
	{
		DeleteObject(firebit);
		DeleteObject(hBitmapMask);
		DeleteDC(hdcMask);
		for (int i = 0; i < Unit_Max_Count; i++)
		{
			if (World->pUnit[i] == this)
			{
				World->pUnit[i] = NULL;
				break;
			}
		}
	}

	HBITMAP createMask(HDC hdcBitmap, int width, int height);
	BOOL getactivate();
	void UpdateAI();
	void UpdateAnimation(HDC deshdc, HDC sourcehdc, int x, int y);
};