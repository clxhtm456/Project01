#include <math.h>
#include <Windows.h>
#include <iostream>
#include "options.h"
interface Unit;
#pragma once

using namespace std;
HBITMAP createMask(HDC hdcBitmap, int width, int height);
class map
{
	HBITMAP mapbit,mapmask,collbit,mapbit2,mapmask2,mapbit3;
	HINSTANCE hInst;
	bool debug2;
public:
	Unit *p[mapMaxsizeX][mapMaxsizeY];
	Unit *t[20];
	int collision[mapMaxsizeX/5][mapMaxsizeY/5];
	map(HINSTANCE hinst, bool debug = NULL)
	{
		hInst = hinst;
		for (int y = 0; y < mapMaxsizeY/5; y++)
		{
			for (int x = 0; x < mapMaxsizeX/5; x++)
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
	HBITMAP getcollision();
	void UpdateAnimation(HDC deshdc, HDC sourcehdc,HDC collhdc, int x, int y,int sizex, int sizey);
	void UpdateBitmap(int resource, int collresource, int resourcemask = NULL, int resource2 = NULL, int resourcemask2 = NULL, int resource3 = NULL);
};
bool isCollision(int ox, int oy, int dx, int dy, int size);
int quake(int x = 0);
void ReadImage(map* m, wchar_t* vv);
void WriteImage(map* m, int i, wchar_t* vv);
void WriteImage2(map* m, int i, wchar_t* vv);
void WriteVmap(map* m, wchar_t* vv);