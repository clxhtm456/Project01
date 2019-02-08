#pragma once
#include <math.h>
#include <random>
#include "World.h"
#include "Unit.h"
#include "resource1.h"
#include <tchar.h>
#include <atlstr.h>
#include <stdlib.h>

void map::UpdateBitmap(int resource, int collresource, int resourcemask,int resource2,int resourcemask2, int resource3)
{
	DeleteObject(mapbit);
	DeleteObject(mapmask);
	DeleteObject(collbit);
	DeleteObject(mapbit2);
	DeleteObject(mapmask2);
	DeleteObject(mapbit3);
	mapbit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(resource));
	collbit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(collresource));
	if (resourcemask)
	{
		mapmask = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(resourcemask));
	}
	else
		mapmask = NULL;
	if (resource2)
	{
		mapbit2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(resource2));
	}
	else
		mapbit2 = NULL;
	if (resourcemask2)
	{
		mapmask2 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(resourcemask2));
	}
	else
		mapmask2 = NULL;
	if (resource3)
	{
		mapbit3 = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(resource3));
	}
	else
		mapbit3 = NULL;
}
void map::UpdateAnimation(HDC deshdc, HDC sourcehdc,HDC collhdc, int x, int y,int sizex, int sizey)
{
	if (mapbit3 != NULL)
	{
		SelectObject(sourcehdc, mapbit3);
		StretchBlt(deshdc, 0, 0, screensizeX, 300, sourcehdc, x/10, 0, screensizeX/3, 186, SRCPAINT);
	}
	if (mapmask2 != NULL)
	{
		SelectObject(sourcehdc, mapmask2);
		StretchBlt(deshdc, 0, -20, screensizeX, screensizeY, sourcehdc, x/8, 0, screensizeX/2 , 150, SRCAND);
	}
	if (mapbit2 != NULL)
	{
		SelectObject(sourcehdc, mapbit2);
		StretchBlt(deshdc, 0, -20, screensizeX, screensizeY, sourcehdc, x/8, 0, screensizeX/2, 150, SRCPAINT);
	}
	if (mapmask != NULL)
	{
		SelectObject(sourcehdc, mapmask);
		//BitBlt(deshdc, x, y, sizex, sizey, sourcehdc, quake(), 0, SRCAND);
		StretchBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x / 2, y / 2, screensizeX / 2, screensizeY / 2, SRCAND);
	}
	SelectObject(sourcehdc, mapbit);
	//TransparentBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x/2, 0, screensizeX / 2, screensizeY / 2, RGB(248,0,248));
	StretchBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x/2, y/2, screensizeX /2, screensizeY /2, SRCPAINT);
	
	//SelectObject(sourcehdc, collbit);
	//StretchBlt(deshdc, 0, 0, screensizeX /2, screensizeY, sourcehdc, x / 2, y, screensizeX / 4, screensizeY / 2, SRCPAINT);
	//TransparentBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x / 2, y / 2, screensizeX / 2, screensizeY / 2, SRCPAINT);
	//BitBlt(deshdc, x, y, sizex, sizey, sourcehdc, quake(), 0, SRCPAINT);

}
HBITMAP map::getcollision()
{
	return collbit;
}
bool isCollision(int ox, int oy, int dx, int dy, int size)
{
	if (sqrt((ox - dx)*(ox - dx) + (oy - dy)*(oy - dy)) <= size)
		return true;
	else
		return false;

}
int quake(int x)
{
	static int size = 0;
	size += x;
	if (size <= 1)
		size = 1;
	if (rand() % 2)
		return (int)(rand() % (size--));
	else
		return -1 * (int)(rand() % (size--));
}

void ReadImage(map* m, wchar_t* vv)
{
	FILE *fPtr;
	TCHAR buffer[mapMaxsizeX/5 + 1];
	TCHAR r2[5] = _T("");
	int y = 0;
#ifdef _UNICODE
	_tfopen_s(&fPtr, vv, _T("r,ccs=UNICODE"));
#else
	_tfopen_s(&fPtr, vv, _T("r"));
#endif
		while (_fgetts(buffer, mapMaxsizeX/5+2, fPtr))
		{
			buffer[_tcslen(buffer)-1] = NULL;
			for (int i = 0; i < mapMaxsizeX/5; i++)
			{
				r2[0] = buffer[i];
				m->collision[i][y]=_wtoi(r2);
			}
			y++;
			if (y > mapMaxsizeY/5)
				break;
		}
	fclose(fPtr);
}
// 결과 영상 저장
void WriteImage( map* m,int i,wchar_t* vv)
{
	FILE* ftr = NULL;
	TCHAR vmap[mapMaxsizeX/5+1];
	TCHAR jul[4];
	StrCpy(vmap, _T(""));
		for (int x = 0; x < mapMaxsizeX/5; x++)
		{
			StrCpy(jul, _T(""));
			_itow_s(m->collision[x][i], jul, 10);
			_tcscat_s(vmap, sizeof(vmap), jul);
		}
		_tcscat_s(vmap, sizeof(vmap), _T("\n"));

#ifdef _UNICODE
			_tfopen_s(&ftr, vv, _T("w,ccs=UNICODE"));
#else
			_tfopen_s(&ftr, vv, _T("w"));
#endif

	//_fwrite_nolock(vmap, sizeof(TCHAR), sizeof(TCHAR)/sizeof(vmap), ftr);
	fwrite(vmap, sizeof(TCHAR), _tcslen(vmap), ftr);
	fclose(ftr);
}

void WriteImage2(map* m, int i, wchar_t* vv)
{
	FILE* ftr = NULL;
	TCHAR vmap[mapMaxsizeX/5+1];
	TCHAR jul[4];
	StrCpy(vmap, _T(""));
	for (int x = 0; x < mapMaxsizeX/5; x++)
	{
		StrCpy(jul, _T(""));
		_itow_s(m->collision[x][i], jul, sizeof(jul));
		_tcscat_s(vmap, sizeof(vmap), jul);
	}
	_tcscat_s(vmap, sizeof(vmap), _T("\n"));

#ifdef _UNICODE
	_tfopen_s(&ftr, vv, _T("a,ccs=UNICODE"));
#else
	_tfopen_s(&ftr, vv, _T("a"));
#endif

	_fwrite_nolock(vmap, 2, _tcslen(vmap), ftr);
	//fwrite(vmap, sizeof(TCHAR), mapMaxsizeX, ftr);
	fclose(ftr);
}

void WriteVmap(map* m,wchar_t* vv)
{
	WriteImage(m,0,vv);
	for (int y = 1; y < mapMaxsizeY/5; y++)
	{
		WriteImage2(m, y,vv);
	}
}