#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <atlstr.h>
#include <tchar.h>
#include "resource1.h"
#include <time.h>
#include "Unit.h"
#include "World.h"
#include "Player.h"
#include "missile.h"
#include "Monster.h"
#include "Sound.h"
#include "Camera.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void Player_movement(Unit* U, BOOL* Key);
void Stage_Check(int stagenum,Unit* U,map* m);
void UI_Draw(HDC deshdc, HDC sourcehdc);
void Number_Draw(HDC deshdc, HDC sourcehdc, int Number, int x, int y, int size = 20);
static HBITMAP Number[13];
static HBITMAP UI[2];

HBITMAP __stdcall CreateBitmapByCreateDIBSection(HDC hdc, BYTE* pbhbitmap, int cx, int cy, int bpp = 0);
HINSTANCE hInst;
HWND hwnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	
	MSG msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Class");
	RegisterClass(&WndClass);
	srand(time(NULL));

	hwnd = CreateWindow(
		_T("Class"),
		_T("window"),
		WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		screensizeX,
		screensizeY,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	bool bDone = false;


	while (!bDone)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);
	}
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int gamestate;
	static int gamestage;
	static bool vmapdraw;
	static int test;
	HDC hdc,cdc, pdc,mdc,backMemDC;
	PAINTSTRUCT ps;
	static HBITMAP Cat, backgroundc,collisiondc
	,hBitmap, gameover,clear,clearmask;
	
	static BOOL keybuffer[256];
	static map *m = new map(hInst);
	static Camera *Cam1 = new Camera(m);
	static Player *p1 = new Player(hInst, m, Cam1, 190, 20, 35);
	
	FILE* VMAP = NULL;
	 
	switch (iMsg)
	{
	case WM_CREATE:
		gamestate = 0;
		gamestage = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMESTART));
		gameover = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMEOVER));
		Cat = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPENING));
		for (int i = 0; i < 13; i++)
			Number[i] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(UI_NUM_0+i));
		for(int i = 0; i < 2; i++)
			UI[i] = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(UI_SCORE+i));
		//SetTimer(hwnd, 1, 14, NULL);//60프레임
		break;
	case WM_TIMER:
		if (gamestate == 1)
		{
			
			/////유닛업데이트
			m->UpdateUnitAI();
			////키입력
			Player_movement(p1, keybuffer);


			if (keybuffer[VK_ESCAPE])
			{
				gamestate = 0;
				KillTimer(hwnd, 1);
			}
			///맵 갱신
			Stage_Check(gamestage, p1, m);
			//카메라이동
			Cam1->Camtransport(p1);
		}
		//InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'T':
			break;
		case 'C':
			p1->jump();
			break;
		case 'X':
			if (!keybuffer['X'])
				p1->fire_shot();
			break;
		}
		keybuffer[wParam] = TRUE;
		break;
	case WM_KEYUP:
		keybuffer[wParam] = FALSE;
		break;
	case WM_LBUTTONDOWN:
		vmapdraw = true;
		if (gamestate == 0)
		{
			if (LOWORD(lParam) >= 800 && LOWORD(lParam) <= 1000 && HIWORD(lParam) >= 300 && HIWORD(lParam) <= 400)
			{
				gamestate = 1;
				PlaygSound(2);
				PlayBGM(3);
				SetTimer(hwnd, 1, int(1000.0/FPS), NULL);
				m->UpdateBitmap(IDB_MAP1, IDB_MAP1_COLL, IDB_MAP1_MASK, IDB_MAP4, IDB_MAP4_MASK, IDB_MAP3);
			}
			if (LOWORD(lParam) >= 800 && LOWORD(lParam) <= 1000 && HIWORD(lParam) >= 400 && HIWORD(lParam) <= 500)
			{
				DeleteObject(Cat);
				delete p1;
				KillTimer(hwnd, 1);
				if (wDeviceID)
					mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
				PostQuitMessage(0);
			}
		}
		if (gamestate == 2 || gamestate == 3)
		{
				DeleteObject(Cat);
				KillTimer(hwnd, 1);
				if (wDeviceID)
					mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
				PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		if (gamestate == 0)
		{
			SelectObject(mdc, Cat);
			BitBlt(hdc, 0, 0, 1000, 700, mdc, 0, 0, SRCCOPY);
			//게임시작
			SelectObject(mdc, hBitmap);
			BitBlt(hdc, 800, 300, 200, 100, mdc, 0, 0, SRCCOPY);
			//게임종료
			SelectObject(mdc, gameover);
			BitBlt(hdc, 800, 400, 200, 100, mdc, 0, 0, SRCCOPY);
		}
		if (gamestate == 1)
		{
			pdc = CreateCompatibleDC(hdc);
			cdc = CreateCompatibleDC(hdc);
			backMemDC = CreateCompatibleDC(hdc);
			backgroundc = CreateCompatibleBitmap(hdc, screensizeX, screensizeY);
			collisiondc = CreateCompatibleBitmap(hdc, screensizeX, screensizeY);
			
			SelectObject(backMemDC, backgroundc);
			SelectObject(cdc, collisiondc);
			//카메라갱신
			Cam1->UpdateCam(backMemDC, pdc, cdc);
			//SelectObject(collhdc, hBitmap);

			UI_Draw(backMemDC, pdc);
			Number_Draw(backMemDC, pdc, p1->getbullet() == 0 ?1000: p1->getbullet(), 248, 68,30);
			//더블버퍼링
			BitBlt(hdc, 0, 0, screensizeX, screensizeY, backMemDC, 0, 0, SRCCOPY);

			
			//wsprintf(str, _T("%d"),p1->getbullet());
			//TextOut(hdc, 0, 0, str, _tcslen(str));
			//오브젝트제거
			DeleteDC(backMemDC);
			DeleteDC(pdc);
			DeleteObject(backgroundc);
			DeleteObject(collisiondc);
			DeleteDC(hdc);
			DeleteDC(cdc);
			EndPaint(hwnd, &ps);
		}
		if (gamestate == 2)
		{
			SelectObject(mdc, clearmask);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCAND);
			SelectObject(mdc, clear);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCPAINT);
		}
		if (gamestate == 3)
		{
			SelectObject(mdc, clearmask);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCAND);
			SelectObject(mdc, clear);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCPAINT);
		}
		DeleteDC(mdc);
		break;
	case WM_DESTROY:
		delete p1;
		DeleteObject(Cat);
		KillTimer(hwnd, 1);
		if (wDeviceID)
			mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_TEST_TEST:
			WCHAR str[100];
				wsprintf(str, _T("x = %d 입니다. p1y = %d입니다, \n"),
					p1->getxPos(), p1->getyPos());
			MessageBox(hwnd, str, _T("test"), MB_OK);
			break;
		case ID_TEST_VMAP:
			break;
		case ID_WEAPON:
			p1->setbullet(200);
			p1->setweapon(1);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void Player_movement(Unit* U, BOOL* Key)
{
	if (*(Key+VK_LEFT))
	{
		U->leftmove(Player_speed);
	}

	if (*(Key + VK_RIGHT))
	{
		U->rightmove(Player_speed);
	}
	if (*(Key + VK_UP))
	{
		U->looktop();
	}else if (*(Key + VK_DOWN))
	{
		U->crouching();
	}
}

void Stage_Check(int stagenum,Unit* U, map* m)
{
	if (U->getxPos() >= 4280)
	{
		U->setxPos(20);
		stagenum++;
	}
	else if (U->getxPos() <= 10)
	{
		U->setxPos(4270);
		stagenum--;
	}
	else
		return;


	switch (stagenum)
	{
	case 1:
		m->UpdateBitmap(IDB_MAP1, IDB_MAP1_COLL, IDB_MAP1_MASK, IDB_MAP4, IDB_MAP4_MASK, IDB_MAP3);
		//M[0] = new Monster(U, hInst, m, 1000, 100);
		//M[1] = new Monster(U, hInst, m, 1700, 100);
		break;
	case 2:
		
		//ReadImage(m, _T("vmap2"));
		//M[0] = new Monster(U, hInst, m, 1700, 100);
		break;
	}
}
void UI_Draw(HDC deshdc, HDC sourcehdc)
{
	SelectObject(sourcehdc, UI[0]);
	TransparentBlt(deshdc, 0, 0, 252, 112, sourcehdc, 0, 0, 63, 28, RGB(248, 0, 248));
	SelectObject(sourcehdc, UI[1]);
	TransparentBlt(deshdc, 238, 0, 252, 72, sourcehdc, 0, 0, 62, 17, RGB(248, 0, 248));
}
void Number_Draw(HDC deshdc, HDC sourcehdc, int _Number, int x, int y,int size)
{
	int i = 0;
	if (_Number == 1000)
	{
		for (i = 0; i < 3; i++)
		{
			SelectObject(sourcehdc, Number[10+i]);
			TransparentBlt(deshdc, x + size * 3 - i*size, y - size, size, size, sourcehdc, 0, 0, 8, 8, RGB(248, 0, 248));
		}
		return;
	}
	while (_Number != 0||i == 0)
	{
		SelectObject(sourcehdc, Number[(_Number % 10)]);
		TransparentBlt(deshdc, x + size * 3 - i*size, y - size, size, size, sourcehdc, 0, 0, 8, 8, RGB(248, 0, 248));
		_Number /= 10;
		i++;
	}
}
HBITMAP __stdcall CreateBitmapByCreateDIBSection(HDC hdc,BYTE* pbhbitmap, int cx, int cy, int bpp)
{
	int i;
	unsigned int cbPalette;
	RGBQUAD *pPalette;
	HPALETTE hPal;
	PALETTEENTRY pe[256];

	// 비트맵 정보를 위한 헤더와 팔레트 공간. 팔레트 최대 사이즈(8비트인 경우)를 고려한다.
	byte pbi[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256] = { 0 };
	// 참고로 malloc 사용시
	//BITMAPINFO *pbi = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + cbPalette);
	//if(!pbi) return 0;
	//memset(pbi, 0, sizeof(BITMAPINFOHEADER)+cbPalette);
	// bpp가 0인 경우 hdc의 bpp로 설정한다.
	if (bpp == 0) {
		bpp = GetDeviceCaps(hdc, BITSPIXEL);
	}
	// 팔레트 사이즈 구하기
	cbPalette = (bpp > 8 ? 0 : 1 << bpp) * sizeof(RGBQUAD); // 8비트보다 크면 필요없다.
															// 이미지 사이즈
															//unsigned int cbImageSize=((((cx * bpp) + 31) & ~31) >> 3) * cy;
															// 헤더파일 입력
	((BITMAPINFOHEADER *)pbi)->biSize = sizeof(BITMAPINFOHEADER);
	((BITMAPINFOHEADER *)pbi)->biWidth = cx;
	((BITMAPINFOHEADER *)pbi)->biHeight = cy;
	((BITMAPINFOHEADER *)pbi)->biPlanes = 1;
	((BITMAPINFOHEADER *)pbi)->biBitCount = bpp;
	((BITMAPINFOHEADER *)pbi)->biCompression = BI_RGB;
	//((BITMAPINFOHEADER *)pbi)->biSizeImage = iImageSize;
	// 팔레트 설정
	pPalette = (RGBQUAD *)((byte *)pbi + sizeof(BITMAPINFOHEADER));
	switch (bpp)
	{
	case 1:
		// 흑백 팔레트
		memset(pPalette, 0, sizeof(RGBQUAD) * 2);
		pPalette[1].rgbBlue = 255;
		pPalette[1].rgbGreen = 255;
		pPalette[1].rgbRed = 255;
		break;
	case 4:
		// 16색(4비트) 팔레트
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
		GetPaletteEntries(hPal, 0, 16, pe);
		for (i = 0; i < 16; i++) {
			pPalette[i].rgbRed = pe[i].peRed;
			pPalette[i].rgbGreen = pe[i].peGreen;
			pPalette[i].rgbBlue = pe[i].peBlue;
			pPalette[i].rgbReserved = 0;
		}
		break;

	case 8:
		// 256색(8비트) 팔레트
		hPal = CreateHalftonePalette(hdc);
		GetPaletteEntries(hPal, 0, 256, pe);
		DeleteObject(hPal);
		for (i = 0; i < 256; i++) {
			pPalette[i].rgbRed = pe[i].peRed;
			pPalette[i].rgbGreen = pe[i].peGreen;
			pPalette[i].rgbBlue = pe[i].peBlue;
			pPalette[i].rgbReserved = 0;
		}
		break;
	}
	return CreateDIBSection(hdc, (BITMAPINFO *)pbi, DIB_RGB_COLORS, (void**)pbhbitmap, NULL, 0);
}