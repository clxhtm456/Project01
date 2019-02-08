#include <windows.h>
#include <atlstr.h>
#include <tchar.h>
#pragma once

HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression, CPalette *pPal);
BOOL WriteDIB(LPTSTR szFileName, HANDLE hDIB);
HANDLE OpenDIB(HWND hWNd, RECT &rtRect);
COLORREF GetDIBPixel(HANDLE hDIB, int x, int y);
void CloseDIB(HANDLE hDIB);
COLORREF MyGetPixel(HWND hWnd, int x, int y);


