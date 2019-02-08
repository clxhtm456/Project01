#include <math.h>
#include <iostream>
#include "options.h"

interface Unit;
#pragma once

using namespace std;
HBITMAP createMask(HDC hdcBitmap, int width, int height);
class map
{
	HDC* colldc;
	HBITMAP mapbit,mapmask,collbit,mapbit2,mapmask2,mapbit3;
	HINSTANCE hInst;
	BYTE* ScreenData = new BYTE[3 * screensizeX*screensizeY];
	bool debug2;
public:
	Unit* pUnit[Unit_Max_Count];
	int collision[screensizeX][screensizeY];
	map(HINSTANCE hinst, bool debug = NULL)
	{
		hInst = hinst;
		for (int y = 0; y < cmapsizeY; y++)
		{
			for (int x = 0; x < cmapsizeX; x++)
			{
				collision[x][y] = 0;
			}
		}
		debug2 = debug;
	}
	~map()
	{
		DeleteObject(mapbit);
		DeleteObject(mapmask);
		DeleteObject(collbit);
		DeleteObject(mapbit2);
		DeleteObject(mapmask2);
		DeleteObject(mapbit3);
	}
	HDC* getcolldc();
	void UpdateAnimation(HDC deshdc, HDC sourcehdc,HDC collhdc, int x, int y,int sizex, int sizey);
	void UpdateBitmap(int resource, int collresource, int resourcemask = NULL, int resource2 = NULL, int resourcemask2 = NULL, int resource3 = NULL);
	void ReadCollision(HDC coll);
	void UpdateUnitAI();
};

bool isCollision(int ox, int oy, int dx, int dy, int size);
int quake(int x = 0);
void ReadImage(map* m, wchar_t* vv);
void WriteImage(map* m, int i, wchar_t* vv);
void WriteImage2(map* m, int i, wchar_t* vv);
void WriteVmap(map* m, wchar_t* vv);

