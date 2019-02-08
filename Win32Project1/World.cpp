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

void map::ReadCollision(HDC coll)
{
	for (int x = 0; x <= screensizeX; x+=10)
	{
		for (int y = 0; y <= screensizeY; y+=10)
		{
			switch (GetPixel(coll, x + 4, y + 4))
			{
			case RGB(248, 0, 248):
				collision[x / 10][y / 10] = 1;
				break;
			case RGB(0, 255, 0):
				collision[x / 10][y / 10] = 2;
				break;
			default:
				collision[x / 10][y / 10] = 0;
				break;
			}
				
		}
	}
}
void map::UpdateUnitAI()
{
	for (int i = 0; i < Unit_Max_Count; i++)
	{
		if (pUnit[i])
		{
			if (pUnit[i]->getdead())
			{
				delete pUnit[i];
				pUnit[i] = NULL;
			}
			else
				pUnit[i]->UpdateAI();
		}
	}
}
void map::UpdateAnimation(HDC deshdc, HDC sourcehdc,HDC collhdc, int x, int y,int sizex, int sizey)
{
	SelectObject(sourcehdc, collbit);
	StretchBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x / 4, y / 4, screensizeX / 4, screensizeY / 4, SRCCOPY);

	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = screensizeX;
	bi.bmiHeader.biHeight = screensizeY;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	BYTE *pbBitmap = NULL;
	HBITMAP hBitmap = CreateDIBSection(collhdc, &bi, DIB_RGB_COLORS, (void**)&pbBitmap, NULL, 0);


	if (hBitmap)
	{
		SelectObject(collhdc, hBitmap);
		BitBlt(collhdc, 0, 0, screensizeX, screensizeY, deshdc, 0, 0, SRCCOPY);
		RGBQUAD *pRGB;
		LONG nPixels;
		pRGB = (RGBQUAD *)pbBitmap, nPixels = 0;

		for (int y = screensizeY - 1; y > 0; y--, pRGB++, nPixels++)
		{
			for (int x = 0; x < screensizeX - 1; x++, pRGB++, nPixels++)
			{
				ULONG* pSrc = (ULONG*)pRGB + 4;
				ULONG nRed = GetRValue(*pSrc);
				ULONG nGreen = GetGValue(*pSrc);
				ULONG nBlue = GetBValue(*pSrc);

					if (nRed == 248 && nGreen == 0 && nBlue == 248)
					{
						//pRGB->rgbRed = 0;
						//pRGB->rgbBlue = 0;
						collision[int(x)][int(y)] = 1;
					}
					else
					{
						collision[int(x)][int(y )] = 0;
					}
			}
		}

		DeleteObject(hBitmap);
	}
	
	
	//ReadCollision(collhdc);
	
	if (mapbit3 != NULL)
	{
		SelectObject(sourcehdc, mapbit3);
		StretchBlt(deshdc, 0, 0, screensizeX, 300, sourcehdc, x/20, 0, screensizeX/6, 93, SRCCOPY);
	}
	if (mapmask2 != NULL)
	{
		SelectObject(sourcehdc, mapmask2);
		StretchBlt(deshdc, 0, -20, screensizeX, screensizeY, sourcehdc, x/16, 0, screensizeX/4 , 75, SRCAND);
	}
	if (mapbit2 != NULL)
	{
		SelectObject(sourcehdc, mapbit2);
		StretchBlt(deshdc, 0, -20, screensizeX, screensizeY, sourcehdc, x/16, 0, screensizeX/4, 75, SRCPAINT);
	}
	if (mapmask != NULL)
	{
		SelectObject(sourcehdc, mapmask);
		//StretchBlt(deshdc, 500, 0, 500, screensizeY, sourcehdc, x / 4+125, y / 4, screensizeX / 8, screensizeY / 4, SRCAND);
		StretchBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x / 4, y / 4, screensizeX / 4, screensizeY / 4, SRCAND);
	}
	SelectObject(sourcehdc, mapbit);
	//StretchBlt(deshdc, 0, 0, 500, screensizeY, sourcehdc, x/4, y/4, screensizeX /8, screensizeY /4, SRCPAINT);
	StretchBlt(deshdc, 0, 0, screensizeX, screensizeY, sourcehdc, x / 4, y / 4, screensizeX / 4, screensizeY / 4, SRCPAINT);
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
HDC* map::getcolldc()
{
	return colldc;
}
